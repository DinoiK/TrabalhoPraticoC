#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "chess.h"
#include "fileio.h"


//Nome do jogador 
typedef struct
{
    char nickname[15];
}player;

player players[2];    

  
  // NICKNAMES   
void createPlayers(){
                            
     do                     //Certifica que os Jogadores não usam o mesmo nome.
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
            printf("Os Nomes são iguais. Por favor escolha outro nome! \n");
        }
              
    } while (!strcmp(players[0].nickname , players[1].nickname));      
}


//First Player func

void setWhite(player players[2]){

    srand(time(NULL));
    int random = rand();      
    player temp[2];            

    if(random % 2 == 1){
      
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
    else{ 
        printf(players[0].nickname);
        printf(" é branco e vai jogar primeiro! \n \n ");
        printf(players[1].nickname);
        printf(" é preto e vai jogar em segundo! \n \n");  
    }
}





































  
