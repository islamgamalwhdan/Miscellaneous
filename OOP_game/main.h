#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "object.h"

#define NEW(O,M) Create_Object(sizeof(struct O##_t) , M)
typedef struct Monster_t * Monster ;

struct Monster_t
{
    object_t mons_obj ;
    int (*init)(void *) ;
    int (*attack)(void * , int) ;
    int hit_points ;
};

int Init_Monster(void *  ) ;
int Attack_Monster(void * , int) ;
/*************************************************/

typedef struct Weapon_t * Weapon ;
struct Weapon_t
{
    object_t weapon ;
};

/****************************************************/

typedef struct You_t * You ;

struct You_t
{
    object_t owner ;
    Weapon weaponn ;
    int (*init)(void *) ;
};

int Init_You(void *) ;

/***********************************************/

typedef struct Room_t * Room ;

struct Room_t
{
    object_t room_obj ;

    int (*init)(void *) ;
    int (*attack)(void * , int) ;
    void *(*Move) (void * , Direction) ;
    int (*pick)(void *) ;
    int (*put)(void *) ;

    Monster bad_guy ;
    Weapon weaponn ;
    You home_owner ;
    struct Room_t * north ;
    struct Room_t * south ;
    struct Room_t * east  ;
    struct Room_t * west ;
};

int Init_Room(void *  ) ;
int Attack_Room(void * , int) ;
void *Move_Room(void * , Direction) ;
int Pick_Room(void *self) ;
int Put_Room(void *sel) ;
/*****************************************************/

typedef struct Map_t *Map ;

struct Map_t
{
    object_t map_obj
           ;
    int (*init)(void * , object_t **) ;
    int (*attack)(void * , int) ;
    int (*Move) (void * , Direction) ;
    int (*pick)(void *) ;
    int (*put)(void *) ;

    Weapon weaponn ;
    Room start_location   ;
    Room current_location ;

};

int Init_Map(void *  , object_t ** ) ;
int Attack_Map(void * , int) ;
int Move_Map(void * , Direction) ;
int Pick_Map(void *self) ;
int Put_Map (void *sel) ;

#endif // MAIN_H_INCLUDED
