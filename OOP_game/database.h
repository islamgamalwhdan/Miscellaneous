#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#define MAX_DATA 512
#define STRLEN   101

typedef struct
{
    char name[STRLEN] ;
    char email[STRLEN] ;
    int  score ;
    int id ;
    int Set ;
} player_t ;

typedef struct
{
    player_t  player[MAX_DATA] ;
    int player_count ;
}DataBase ;

typedef struct
{
    DataBase db ;
    FILE *filename ;

}Connection ;

Connection *Creat_Connection(const char * ) ;
void Destroy_Database(Connection *) ;
int Read_Database(Connection *) ;
int Write_Database(Connection *) ;
void Store_Player_Database( int) ;
char * get_str(char * , int );
#endif // DATABASE_H_INCLUDED
