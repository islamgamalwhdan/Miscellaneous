#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "object.h"

void ExitError(char *) ;
/************************ Functions Definitions ************************************/

void   Describe_Object(void *self)
{
       object_t *obj = self ;
       if(obj)
           printf("%s.\n", obj->description) ;
}

void   Destroy_Object(void *self )
{
       object_t *obj = self ;

       if(obj)
       {
           if(obj->description)
               free(obj->description) ;
           free(obj) ;
       }
}

void * Create_Object(  size_t Size , const char *descr)
{
    object_t *obj = malloc( Size )  ;
    if(!obj)
        ExitError("Memory allocation failed") ;



    obj->describe = Describe_Object ;

    obj->destroy = Destroy_Object ;

    obj->description = strdup(descr) ;


    return obj ;
}



void ExitError(char *msg)
{
    if(errno)
        perror(msg) ;
    else
        printf("Error : %s\n" , msg) ;
}
