#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

   /************************ Monster Object **************************************/
typedef enum
{
    NORTH , SOUTH , EAST , WEST
}Direction;

//typedef struct object_t * Object;

typedef struct
{
    /* object function pointers*/
    void (*destroy)(void *) ;
    void (*describe)(void * ) ;

    /* object Data */
    char * description ;
}object_t;

void   Describe_Object(void * ) ;
void   Destroy_Object(void * ) ;

void * Create_Object(  size_t , const char *) ;


#endif // OBJECT_H_INCLUDED
