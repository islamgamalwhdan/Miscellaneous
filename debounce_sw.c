/*
 * debounce_sw.c
 *
 * Created: 1/20/2018 12:34:11 AM
 *  Author: Islam
 */ 
#define F_CPU 8000000UL
#include <stdio.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"

#define SAMPLES_NUM 13
#define ENABLED  1
#define DISABLED 0
#define DEBUG ENABLED
typedef enum { PRESSED , RELEASED , DE_BOUNCING }SW_ST;

typedef struct
{
	uint16_t samples_mem ;
	SW_ST status ;
	uint8_t samples_count ;
}SWITCH;

SWITCH sw = {.status = DE_BOUNCING } ;
#define read_pin(PORT,PIN) (PORT & (1<< (PIN)))

void timer_init() ;

#if DEBUG == ENABLED
char debug_buff[51] ;
#endif

int main(void)
{
	DDRA = 0 ;
	DDRC = 0xFF ;
	PORTA = 0xFF ;
	DDRB = 0xFF ;
		
	timer_init() ;
	Uart_init(9600) ;
	uint8_t press_flag = 0 ;
	
    while(1)
    {
		
        if(sw.status == PRESSED && !press_flag)
		{
			#if DEBUG == ENABLED
			Uart_Transimit_String("Switch is pressed\n") ;
			press_flag = 1 ;
			PORTC++;
			sprintf(debug_buff,"PORTC = %d\n",PORTC);
			Uart_Transimit_String(debug_buff) ;  
			#endif
		}
		
		if(sw.status == RELEASED  && press_flag)
		{
			press_flag = 0 ;
			//PORTC = 0 ;
		}
		
	 PORTB++ ;
    }
}

void timer_init()
{
	OCR0 = 69 ;
	TCNT0 = 0 ;
	/* Pre-scale  = 64 , CTC-mode */
	TIMSK |= (1<<OCIE0) ; // enable timer 0 CTC interrupt 

	TCCR0 |= ( 1<<CS00 ) | ( 1<<CS01 ) | ( 0<<CS02 ) | ( 0<<WGM00  ) | ( 1<<WGM01 ) ;
	
	sei() ;
}

ISR(TIMER0_COMP_vect)
{
	#if DEBUG == ENABLED
	   //  Uart_Transimit_String("ISR entered\n") ;
	#endif
	/* 13 samples * 4.4ms = 57.2ms */
	sw.samples_mem = (sw.samples_mem <<1) | (read_pin(PINA,0)>1)| 0xE000 ;
	
	/*Switch is pressed */
	if(sw.samples_mem == 0xE000)
	{
		if(sw.samples_count++  == SAMPLES_NUM )
		{
			sw.samples_count =  0 ;
			sw.status = PRESSED ;
		}
	}
	
	/*Note that status will be 0xFFFF only when switch is released and with 13 identical samples (all 13 samples are high) */ 
	else if (sw.samples_mem  == 0xFFFF)
	{
	   sw.status = RELEASED ;	
	}
	
	else 
	{
		sw.status =DE_BOUNCING ;
	}
}
