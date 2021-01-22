#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "chess.h"
#include "fileio.h"


//------------- Individual Player Struct - Defines PlayerName  ------------------//
typedef struct
{
    char nickname[15];
}player;

player players[2];     // Cria um array onde os 2 Players ficarão guardados e manipulados.

  
  //------------------------  FUNCTION TO SET NICKNAMES   ---------------------------//

void createPlayers(){
                            // Ciclo para pedir aos Jogadores pelo nome e guardar em """THE PLAYERSLIST"""
     do                     //Jogadores não podem usar o mesmo nome.
    {
        for (int i = 0; i < 2; i++)
        {
            do{
                printf("Nome do Jogador %d:  ",(i + 1));
                gets(players[i].nickname);     

                if(strlen(players[i].nickname) > 15){
                    printf("O nome do jogador é muito grande, máximo são 15. Por favor escolha outro! \n");
                }
            }while(strlen(players[i].nickname) > 15);
        }
        if (!strcmp(players[0].nickname , players[1].nickname))
        {
            printf("Os Nomes são iguais. por favor escolha outro nome! \n");
        }
              
    } while (!strcmp(players[0].nickname , players[1].nickname));      
}


//--------------------   FUNCTION TO INFORM THE PLAYERS OF WHO PLAYS FIRST/ IS WHITE  ------------------//


void setWhite(player players[2]){

    srand(time(NULL));
    int random = rand();       //Generates random value -> If pair Player[0] stays player 0 ----> ELSE Player[0] becomes player[1]
    player temp[2];            //USER DOESN'T SEE THIS CHANGE HAPPENING, IT JUST ORGANIZES PLAYER ORDER

    if(random % 2 == 1){
       
       // player[0] becomes player[1] and vice versa -----> player[0] always starts, but which one it is is random
        temp[0] = players[1];
        temp[1] = players[0];
        for (int i = 0; i < 2; i++)
        {
            players[i] = temp[i];
        }   
        printf("\n ");
        printf(players[0].nickname);
        printf(" é branco e vai jogar primeiro! \n \n ");
        printf(players[1].nickname);
        printf(" é preto e vai jogar em segundo! \n \n");       
    }
    else{ //ELSE ALL REMAINS THE SAME AND INITIAL PLAYER[0] STARTS
        printf(players[0].nickname);
        printf(" é branco e vai jogar primeiro! \n \n ");
        printf(players[1].nickname);
        printf(" é preto e vai jogar em segundo! \n \n");  
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         GAMEPLAY                                                               //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* void gameCourse(){

    do
    {
        makePlay(players[0]);
        reCreateTable();
        makePlay(players[1]);
        reCreateTable();

         // -----OR----- //
        makePlayWhite();
        reCreateTable();
        makePlayBlack();
        reCreateTable();

    } while (!gameEnded());
    
}

void makePlay(player player){

    //POINT A -----> ALLOW PLAYER TO CHOOSE AN X AND Y COORDENATE TO MOVE A PIECE 

    //POINT B -----> SHOW PLAYER THE POSSIBLE POSITION WHERE THE PIECE CAN GO  

    //POINT C -----> TAKE PLAYER INPUT ABOUT WHERE TO MOVE THE PIECE OR ALLOW HIM TO GO BACK TO POINT A

    //POINT D -----> ASK FOR COMFIRMATION ABOUT THE MOVE OR GO BACK TO POINT C

    //POINT E -----> FINALIZE MOVE AND UPDATE TABLE (INSIDE OR OUTSIDE THIS FUNCTION TBD) AND LEAVE FUNCTION
}




 */









































//_________________TEST____________________//



//char player [2] [12];
/* void createPlayers(){
  
     do
    {
        for (int i = 0; i < 2; i++)
        {
            printf("Player %d's Nickname ",(i + 1));
            scanf("%s",&player[i]);     
        }
        if (!strcmp(player[0] , player[1]))
        {
            printf("Players Nicknames can't be the same. Please choose new ones! \n");
        }
              
    } while (!strcmp(player[0] , player[1]));       
} */

 

/* void setWhite(char player[] ){

    srand(time(0));
    int random = rand()%2;
    char temp[2];

    if(random = 1){
       
       // player[0] becomes player[1] and vice versa -----> player[0] always starts, but which one it is is random
        temp[0] = player[1];
        temp[1] = player[0];
        for (int i = 0; i < 2; i++)
        {
            player[i] = temp[i];
        }   
        printf("%s",player[0]);
        printf(" is White and will start the game");       
    }
    

    
} */

  
