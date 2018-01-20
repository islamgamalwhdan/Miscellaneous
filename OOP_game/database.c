#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "dbg.h"
#include "database.h"

#define FILENAME "C:\\Users\\ahmed\\Desktop\\C codes\\new_game\\data_base.dat"
#define EAT_ENTRY() while(getchar() != '\n') continue;

Connection *Creat_Connection(const char *filename )
{
    Connection *conn = calloc(1,sizeof(Connection)) ;
    //check_mem(conn) ;

    int i = 0;
    for( i = 0 ; i< MAX_DATA ; i++)
        conn->db.player[i].id = i+1 ;

    /// for update or read

        conn->filename = fopen(filename , "rb+") ;
        //check(db->filename  , "File open failed !") ;

        return conn ;
}

int Read_Database(Connection *conn)
{
    int rc ;
    if(conn)
    {
        if(conn->filename)
        {

            DataBase *db = &conn->db ;
            rc=fread(db,sizeof(DataBase),1,conn->filename);  // load database from file .
           /* if (rc != 1)
            {
                printf("Error load database from file\n") ;
                return -1 ;
            }*/

      }
    }
    return 1 ;
}

int Write_Database(Connection *conn)
{
  int rc ;
    if(conn)
    {
         if(conn->filename)
         {
              rewind(conn->filename) ;
              DataBase *db = &conn->db ;
              rc = fwrite(db,sizeof(DataBase),1,conn->filename) ;
              if (rc != 1)
              {
                printf("Error load database from file\n") ;
                return -1 ;
              }
              fflush(conn->filename) ;
         }
    }
    return 1 ;
}


void Store_Player_Database( int score )
{
    Connection *conn = Creat_Connection(FILENAME );
    player_t *player = conn->db.player ;

    Read_Database(conn) ;

    int player_num = conn->db.player_count ;

    printf("Your name : ") ;
    get_str(player[player_num].name , STRLEN) ;
    printf("Your e-mail : ") ;
    get_str(player[player_num].email , STRLEN) ;
    player[player_num].Set = 1 ;
    player[player_num].score = score ;
    conn->db.player_count++ ;
    Write_Database(conn) ;

    /* Display other players data */
    printf("Do you want to display previous players score ? (y/n) :") ;
    if(getchar() == 'y')
        {
            EAT_ENTRY() ; // Eat '\n' character entry from buffer entry .
            int i ;
            for(i = 0 ; i<MAX_DATA ; i++)
            if(player[i].Set)
                printf("Name : %s    email : %s      Score = %d\n" , player[i].name , player[i].email , player[i].score) ;
        }
      Destroy_Database(conn) ;
}

void Destroy_Database(Connection *conn)
{
    if(conn)
    {
        free(conn) ;
    }
}

char * get_str(char *str , int len)
{
    char *add = fgets(str , len , stdin) ;

    if(add)
    {
        char *find = strchr(str , '\n') ;
        if(find)
            *find = '\0' ;
        else
            while(getchar() !='\n') ;
    }

    return add ;
}
