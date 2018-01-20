#include <stdio.h>
#include <stdint.h>

typedef uint32_t U32 ;
//#define LITTLE_ENDIAN
#define BIG_ENDIAN

#ifdef LITTLE_ENDIAN
   #define receive_data(data) ( (U32)data&0xffffffffUL )
   #define send_data(data)    ( (U32)data&0xffffffffUL )

#else //BIG_ENDIAN
   #define receive_data(data) littleTobig(data)
   #define send_data(data)    littleTobig(data)
#endif // BYTE_ORDER

/* Function Prototype */

U32 littleTobig(U32 data) ;

int
main( )
{
    U32 recv_var = 0xDDCCBBAA ;

    U32 x = receive_data(recv_var) ;

    U32 For_send_var = 0x11223344 ;
    U32 y = send_data(For_send_var) ;
}

inline U32 littleTobig(U32 data)
{
    uint8_t *b =(uint8_t*) &data ;

    return ( b[3] | (b[2]<<8) | (b[1]<<16) | b[0]<<24 ) ;
}
