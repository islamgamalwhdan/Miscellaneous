#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "main.h"
#include "database.h"

#define EAT_ENTRY() while(getchar() != '\n') continue;

//#define DEBUG
void finih_game( object_t** );


int main(void)
{
    Map game = NEW(Map, "Your Home") ;
    object_t *arr_obj[9] ={NULL} ;
    game->init = Init_Map ;
    game->init(game , arr_obj) ;

    printf("You Entered : ") ;
    game->start_location->room_obj.describe(game->start_location) ;

    srand(time(NULL)) ; // to get random number depend on the time ;

    printf("n>") ;
    char input ;
    int score = 5 ;

    while((input = getchar()) )
          {
            EAT_ENTRY() ; // Eat '\n' character entry from buffer entry .

            int damage = rand()%3 +1 ; // random number from 1-3 .
            int move = 0;
            int attack =0 ;

              switch(input)
                {
                   case 'n' :
                           move =game->Move(game , NORTH) ;
                           break ;

                   case 's' :
                           move =game->Move(game , SOUTH) ;
                           break ;

                   case 'e' :
                           move =game->Move(game , EAST) ;
                           break ;

                   case 'w' :
                           move =game->Move(game , WEST) ;
                           break ;

                   case 'a' :
                             attack = game->attack(game , damage) ;

                            break ;

                   case 'p' :
                             game->pick(game) ;
                             break ;

                   case 'l' :
                             game->put(game) ;
                             break ;

                   case 'h' :
                             /* Help how to use directions */
                            puts("Use <#> to exit the game .") ;
                            if(game->current_location->north)
                                puts("Use <n> to go NORTH");
                            if(game->current_location->south)
                                puts("Use <s> to go SOUTH");
                            if(game->current_location->east)
                                puts("Use <e> to go EAST");
                            if(game->current_location->west)
                                puts("Use <w> to go WEST ");
                                /* Help how to deal with weapon and monster */

                            if(game->current_location->weaponn)
                                puts("Use <p> to pick the weapon at that room") ;
                            if(game->current_location->home_owner->weaponn)
                                puts("You can go find the monster and use <a> to kill him ") ;
                             break ;

                   case '#':
                          goto exit_game ;
                          break ;

                   default :
                            puts("Wrong Entry you should enter \n<n> to go NORTH or") ;
                            puts("<s> to go SOUTH or");
                            puts("<e> to go EAST or") ;
                            puts("<w> to go WEST or") ;
                            puts("<p> to pick your weapon or") ;
                            puts("<l> to leave your weapon or") ;
                            puts("<a> to attack the monster or") ;
                            puts("<#> to Exit the game .") ;

                } // switch(input)
                if(attack == 1 || move== -1)
                    {
                                int score = 5 ;
                               // Store_Player_Database( score);
                                 printf("play again? (y/n)") ;
                                if(getchar() == 'y')
                                {
                                    EAT_ENTRY() ; // Eat '\n' character entry from buffer entry .
                                    finih_game( arr_obj) ;
                                    game = NEW(Map , "Your Home") ;
                                    game->init = Init_Map;
                                    game->init(game , arr_obj) ;

                                }
                                else
                                    break ;
                    }
                    printf("\nn>") ;

          }//while
          exit_game :

          finih_game( arr_obj) ;
     return 0 ;
}//main



/****************************************** Functions definition ***********************************/

 int Init_Map(void * self , object_t **arr_obj )
{
    int objects_count =0 ;
    Map game = self ;
      objects_count++ ;

    game->attack = Attack_Map;
    game->Move = Move_Map ;
    game->pick = Pick_Map ;
    game->put = Put_Map ;

    /* Create 4 Rooms */
    objects_count += 4 ;
    Room hall    =   NEW(Room , "The hall") ;
    Room arena   =   NEW(Room , "The arean");
    Room kitchen =   NEW(Room , "The kitchen") ;
    Room bedroom =   NEW(Room , "The bed room") ;


    /* Initialization rooms */

    hall->init    = Init_Room ;
    arena->init   = Init_Room ;
    kitchen->init = Init_Room ;
    bedroom->init = Init_Room ;

    hall->init(hall)       ;
    arena->init(arena)     ;
    kitchen->init(kitchen) ;
    bedroom->init(bedroom) ;

    /*Drawing the map */

    hall->north = arena ;
    arena->south = hall ;
    arena->east = kitchen ;
    kitchen->west = arena ;
    arena->west = bedroom ;
    bedroom->east = arena ;

    /* Put the Monster at the bedroom */

    Monster mons = NEW(Monster, "The horrible Monster") ;
    objects_count++ ;
    mons->init = Init_Monster ;
    mons->init(mons) ;
    bedroom->bad_guy = mons ;

    /* Put the knife at the kitchen */
    Weapon knife_ = NEW(Weapon , "The knife") ;
    objects_count++;
    kitchen->weaponn = knife_ ;

    /* Finally put the home owner at hall */

    You home_ower = NEW(You , "The home owner") ;
    objects_count++ ;
    home_ower->init = Init_You ;
    home_ower->init(home_ower) ;
    hall->home_owner = home_ower ;

    /* start from the hall and make it current location */
    game->start_location = hall ;
    game->current_location = hall ;

    /* store objects address in array to free it later */

    arr_obj[0] =(object_t *) game ;
    arr_obj[1] =(object_t *) hall ;
    arr_obj[2] = (object_t *)arena ;
    arr_obj[3] = (object_t *)kitchen ;
    arr_obj[4] = (object_t *)bedroom ;
    arr_obj[5] =(object_t *) mons ;
    arr_obj[6] = (object_t *)knife_ ;
    arr_obj[7] = (object_t *)home_ower ;
    arr_obj[8] = NULL ; // to terminate during free.

    /*object_t **arr = malloc((objects_count+1) * sizeof(object_t *)) ;

    arr[0] =(object_t *) game ;
    arr[1] =(object_t *) hall ;
    arr[2] = (object_t *)arena ;
    arr[3] = (object_t *)kitchen ;
    arr[4] = (object_t *)bedroom ;
    arr[5] =(object_t *) mons ;
    arr[6] = (object_t *)knife_ ;
    arr[7] = (object_t *)home_ower ;
    arr[8] = NULL ; // to terminate during free.
    *arr_obj = arr ;*/

    return 1 ;
}

int Attack_Map(void *self , int damage)
{
    Map game = self ;
    Room cur_loc = game->current_location ;

    return cur_loc->attack(cur_loc , damage) ;

}

int Move_Map(void *self , Direction dir)
{
    Map game = self ;
    Room next_room = NULL ;
    Room current_loc = game->current_location ;

    next_room = current_loc->Move(current_loc , dir);

    if(!next_room)
    {
        puts("Cannot Go to that direction !! \n") ;
        next_room = current_loc ;
    }
    //game->weaponn = next_room->weaponn ;

    Weapon knife_ = next_room->weaponn ;
    Monster monster_ = next_room->bad_guy ;
    Weapon your_knife = next_room->home_owner->weaponn;

    if(monster_)
    {

            puts("OOOH MY GOD !!! THE MONSTER ARE HERE\n");
            if(your_knife)
                puts("use <a> to attack ...ATTACK .. ATTACK NOW ") ;
            else
            {
                puts("FUCK FUCK .. don't have weapon.. Monster killed you\nYou Lose\n") ;
                return -1 ;
            }

    }

    if(knife_)
        {
             puts("The knife is here  press <p> to pick it now . !!\n") ;
        }
    game->current_location = next_room ;
    //if(game->current_location == )

    return 1 ;
}

int Init_Room(void *self)
{
    Room room_ = self ;

    room_->attack = Attack_Room ;
    room_->Move   = Move_Room   ;
    room_->pick   = Pick_Room   ;
    room_->put    = Put_Room    ;

    room_->bad_guy = NULL ;
    room_->weaponn = NULL ;
    room_->home_owner = NULL ;
    room_->north = room_->south = room_->east  = room_->west = NULL ;


    return 1 ;
}

int Attack_Room(void *self , int damage)
{
    Room cur_loc = self ;
    Monster bad_man = cur_loc->bad_guy ;

    if(!bad_man)
    {
        puts("HAHAHAHA .. Are you blind man ?!!! ... Monster aren't here") ;
        return 0 ;
    }

    return bad_man->attack(bad_man , damage ) ;

}

void * Move_Room(void *self , Direction dir)
{
    Room cur_loc = self ;
    Room next_room = NULL ;

    switch(dir)
    {
              case NORTH:
                          if(cur_loc->north)
                          {
                              next_room = cur_loc->north ;
                              puts("you go North to :") ;
                              next_room->room_obj.describe(next_room) ;
                          } break ;

              case SOUTH :
                          if(cur_loc->south)
                          {
                              next_room = cur_loc->south ;
                              puts("you go South to :") ;
                              next_room->room_obj.describe(next_room) ;
                          } break ;

             case EAST :
                          if(cur_loc->east)
                          {
                              next_room = cur_loc->east ;
                              puts("you go East to :") ;
                              next_room->room_obj.describe(next_room) ;
                          } break ;

             case WEST :
                          if(cur_loc->west)
                          {
                              next_room = cur_loc->west ;
                              puts("you go West to :") ;
                              next_room->room_obj.describe(next_room) ;
                          } break ;

             default :
                       puts("Wrong Entry or not available direction in the game") ;
    }

  if(next_room)
  {
      next_room->home_owner = cur_loc->home_owner ;
      cur_loc->home_owner = NULL ;
  }

    return next_room ;
}

int Init_Monster(void *self)
{
    Monster bad_guy = self ;

    bad_guy->attack = Attack_Monster ;

    bad_guy->hit_points = 10 ;  // set max hit point to kill monster to 10 point .

    return 1 ;
}

int Init_You(void *self)
{
    assert(self != NULL) ;
    You home_owner = self ;

    home_owner->weaponn = NULL ;

    return 1 ;
}

int Attack_Monster(void *self , int damage)
{
    assert(self != NULL) ;
    Monster bad_man = self ;

    bad_man->hit_points -= damage ;

    if(bad_man->hit_points > 0)
    {
        puts("ATTACK .. ATTACK .. Monster is still alive!!\n") ;
        return 0;
    }
    else
    {
        puts("Good jop Bro .. you killed the monster \nYou won\n") ;
        return 1 ;
    }
}


int Pick_Map(void *self)
{
    assert(self != NULL) ;
    Map game = self ;
    Room curr_loc = game->current_location ;

    curr_loc->pick(curr_loc) ;

    return 1 ;
}

int Pick_Room(void *self)
{
    assert(self != NULL) ;
    Room curr_loc = self ;
    Weapon room_knife = curr_loc ->weaponn ;
    You home_owner = curr_loc->home_owner ;


   if(home_owner->weaponn)
    {
        puts("WAKE UP .. the knife with you\n") ;
        return 0 ;
    }

    else if(room_knife)   // is the knife here?
    {
       home_owner->weaponn = room_knife ;
       curr_loc->weaponn = NULL ;
       puts("Now Go And find the Monster then Kill him with the knife..Good Luck!\n");
       return 1 ;
    }

    else
    {
        puts("HAHAHAHA .. Are you blind man ?!!! ... There is no weapon to pick search for it in another room\n") ;
        return 0 ;
    }

}

int Put_Map(void *self)
{
    assert( self != NULL) ;
    Map game = self ;
    Room curr_loc = game->current_location ;

    curr_loc->put(curr_loc) ;

    return 1 ;
}

int Put_Room(void *self)
{
    assert( self!= NULL);

    Room curr_loc = self ;
    Weapon your_weapon = curr_loc->home_owner->weaponn ;

    if(your_weapon)
    {
        puts("you leave your");
        your_weapon->weapon.describe(your_weapon) ;
        curr_loc->weaponn = your_weapon ;
        curr_loc->home_owner->weaponn  = NULL ;
        return 1 ;
    }
    else
    {
        puts("Wake Up .. You don't have any weapon") ;
        return 0 ;
    }

}

void finih_game( object_t **arr_obj)
{
    int i ;
    for(i=0 ; arr_obj[i] ; i++)
        (arr_obj[i])->destroy(arr_obj[i]) ;
}

