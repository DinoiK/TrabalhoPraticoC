#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "chess.h"
#include <stdbool.h>
#include <conio.h>
#include <math.h>

peca pecas1[16];//brancos
peca pecas2[16];//pretos

player jogadores[2];
bool turnoBranco = true;
bool winW,winB;

int random;
void writeRandom()
{
    printf("%d",random);
}

void writeCoordinatesOfPieces(FILE *savedData)
{
    for (int i = 0; i < 16; i++)
    {
        fprintf(&*savedData,"%c %d %c\n",pecas1[i].costume,pecas1[i].posX,pecas1[i].posY);
        // fprintf("%c %d %c",pieces1[i].costume,pieces1[i].posX,pieces1[i].posY);
        // fprintf("\n");
    }
    fprintf(&*savedData,"\n");
    for (int i = 0; i < 16; i++)
    {
        fprintf(&*savedData,"%c %d %c\n",pecas2[i].costume,pecas2[i].posX,pecas2[i].posY);
        // fprintf("%c %d %c",pieces2[i].costume,pieces2[i].posX,pieces2[i].posY);
        // fprintf("\n");
    }
    fprintf(&*savedData,"\n");
}

void writePlayerTurn(FILE *savedData)
{
    fprintf(&*savedData,"%d",turnoBranco);
}


void createPlayers(){
                            //CYCLE TO REQUEST FOR PLAYER'S NICKNAME AND STORE IT IN """THE PLAYERSLIST"""
     do                     //GRANTS PLAYERS DON'T PICK THE SAME NICKNAME
    {
        for (int i = 0; i < 2; i++)
        {
            do{
                printf("Jogador %d, digite seu nome:  ",(i + 1));
                gets(jogadores[i].nickname);     

                if(strlen(jogadores[i].nickname) > 12){
                    printf("Nome muito longo. \n");
                }
            }while(strlen(jogadores[i].nickname) > 12);
        }
        if (!strcmp(jogadores[0].nickname , jogadores[1].nickname))
        {
            printf("Nomes iguais, escolham outro. \n");
        }
              
    } while (!strcmp(jogadores[0].nickname , jogadores[1].nickname));      
}

//--------------------   FUNCTION TO INFORM THE PLAYERS OF WHO PLAYS FIRST/ IS WHITE  ------------------//
void checkGame()
{    
    bool encontrouReiB;
    bool encontrouReiP;
    for (int i = 0; i < sizeof pecas1/sizeof pecas1[0]; i++)
    {
        if(pecas1[i].costume == 'K')
        {
            encontrouReiB = true;
            break;
        }
    }
    for (int i = 0; i < sizeof pecas2/sizeof pecas2[0]; i++)
    {
        if(pecas2[i].costume == 'k')
        {
            encontrouReiP = true;
        }
    }
    
    if(encontrouReiB && !encontrouReiP)
    {
        winB = false;
        winW = true;
    }
    else if(!encontrouReiB && encontrouReiP)
    {
        winW = false;
        winB = true;
    }    
}

void setWhite(){

    srand(time(NULL));
    int random = rand();       //Gera valores aleaotórios -> If pair Player[0] stays player 0 ----> ELSE Player[0] becomes player[1]
    player temp[2];            //USER DOESN'T SEE THIS CHANGE HAPPENING, IT JUST ORGANIZES PLAYER ORDER

    if(random % 2 == 1){
       
       // player[0] becomes player[1] and vice versa -----> player[0] always starts, but which one it is is random
        temp[0] = jogadores[1];
        temp[1] = jogadores[0];
        for (int i = 0; i < 2; i++)
        {
            jogadores[i] = temp[i];
        }   
        printf("\n ");
        printf(jogadores[0].nickname);
        printf("  é o Branco e irá jogar em primeiro! \n \n ");
        printf(jogadores[1].nickname);
        printf(" é Preto e irá jogar em segundo! \n \n");       
    }
    else{ //ELSE ALL REMAINS THE SAME AND INITIAL PLAYER[0] STARTS
        printf(jogadores[0].nickname);
        printf("  é o Branco e irá jogar em primeiro \n \n ");
        printf(jogadores[1].nickname);
        printf(" é Preto e irá jogar em segundo! \n \n");  
    }
}

void criarTabuleiro()
{
    srand(time(0));
    random = rand()%2;
    //gera um tabuleiro aleatorio de peças brancas e pretas.
    //com letras maísuculas e minúsculas, respectivamente 
    // piece pieces1[16];
    // piece pieces2[16];
    char pecas[9] = {'p','r','n','b','q','k','b','n','r'};
    if(random == 0)
    {
        for (int i = 0, b = 'A'; i < 16; i++,b++)
        {
            if(i<=7)
            {
                pecas1[i].costume = toupper(pecas[i+1]);
                pecas1[i].posY = b; 
                pecas1[i].posX = 1;

                pecas2[i].costume = pecas[i+1];
                pecas2[i].posY = b; 
                pecas2[i].posX = 8;
            }else
            {
                pecas1[i].costume = toupper(pecas[0]);
                pecas1[i].posY = b-8;
                pecas1[i].posX = 2;

                pecas2[i].costume = pecas[0];
                pecas2[i].posY = b-8; 
                pecas2[i].posX = 7;
            }        
        }
    }else
    {
        for (int i = 0, b = 'A'; i < 16; i++,b++)
        {
            if(i<=7)
            {
                pecas1[i].costume = toupper(pecas[i+1]);
                pecas1[i].posY = b; 
                pecas1[i].posX = 8;

                pecas2[i].costume = pecas[i+1];
                pecas2[i].posY = b; 
                pecas2[i].posX = 1;
            }else
            {
                pecas1[i].costume = toupper(pecas[0]);
                pecas1[i].posY = b-8;
                pecas1[i].posX = 7;

                pecas2[i].costume = pecas[0];
                pecas2[i].posY = b-8; 
                pecas2[i].posX = 2;
            }        
        }
    }

    printf("   A");
    for (int i = 'B'; i <= 'H'; i++)
    {
        printf("  %c",i);
    }
    printf("\n");    
    if(random == 0)
    {
        //upper case top        
        for (int l = 0; l < 8; l++)//cria as linhas
        {
            printf("%d ", l+1);
            for (int c = 0; c < 8; c++)//cria as colunas
            {
                if(l == 0)
                {
                    printf("[%c]",pecas1[c].costume);
                }else if(l == 1)
                {
                    printf("[%c]",pecas1[c+8].costume);
                }else if(l == 6)
                {
                    printf("[%c]",pecas2[c+8].costume);
                }else if(l == 7)
                {
                    printf("[%c]",pecas2[c].costume);
                }else
                {
                    printf("[ ]");
                }
            }
            printf("\n");            
        }
    }else
    {

        for (int l = 0; l < 8; l++)//cria linhas
        {
            printf("%d ", l+1);
            for (int c = 0; c < 8; c++)//cria colunas
            {
                if(l == 0)
                {
                    printf("[%c]",pecas2[c].costume);
                }else if(l == 1)
                {
                    printf("[%c]",pecas2[c+8].costume);
                }else if(l == 6)
                {
                    printf("[%c]",pecas1[c+8].costume);
                }else if(l == 7)
                {
                    printf("[%c]",pecas1[c].costume);
                }else
                {
                    printf("[ ]");
                }
            }
            printf("\n");    
        }
    }
}

void reCreateTable()
{
    bool encontrarPeca;
    system("cls");
    printf("   A");
    for (int i = 'B'; i <= 'H'; i++)
    {
        printf("  %c",i);
    }
    printf("\n");
    
    for (int l = 1; l <= 8; l++)
    {
        printf("%d ", l);
        for (int c = 65; c <= 72; c++)
        {
            for(int p = 0; p < 16; p++)
            {
                if(pecas1[p].posX == l && pecas1[p].posY == c)
                {
                    printf("[%c]",pecas1[p].costume);
                    encontrarPeca = true;
                    break;
                }else if(pecas2[p].posX == l && pecas2[p].posY == c)
                {
                    printf("[%c]",pecas2[p].costume);
                    encontrarPeca = true;
                    break;                    
                }              
            }
            if(encontrarPeca == false)
            {
                printf("[ ]");
            }
            encontrarPeca = false;                                    
        }
        printf("\n");
    }    
}

void movePiece()
{
    int index = 0;
    int posX = 0;//select piece line
    char posY = 0;//select piece column
    char pecaEscolhida = ' ';
    char resposta = 0;
    peca pecaSelecionada;
    bool escolha = false;
    //select piece
    //receive coordinates from the table and verify if exists in the table
    if(turnoBranco == true)
    {
        printf("<< %s turn >>\n",jogadores[0].nickname);
    }else
    {
        printf("<< %s turn >>\n",jogadores[1].nickname);
    }
        
    while(pecaEscolhida == ' ' && escolha == false)
    {
        //choose a line form the table
        do
        {
            printf("Selecionas peça\n");
            printf("linha da peça: ");
            scanf("%d",&posX);
            if(posX <= 0 || posX > 8)//if the choice is outside of the table, teel the player that he is out of bounds
            {
                printf("Fora do tabuleiro\nEscreva um número válido dentro do tabuleiro!\n");
            }
        }while(posX <= 0 || posX > 8);

        do
        {
            printf("Coluna da peça: ");
            scanf(" %c",&posY);
            posY = toupper(posY);
            if(posY < 'A' || posY > 'H')//if the choice is outside of the table, teel the player that he is out of bounds
            {
                printf("Fora do tabuleiro\nEscreva uma coluna válida dentro do tabuleiro!\n\n");
            }
        }while(posY < 'A' || posY > 'H');
        
        for (int i = 0; i < 16; i++)
        {
            if(pecas1[i].posX == posX && pecas1[i].posY == posY)
            {
                pecaEscolhida = pecas1[i].costume;
                // selectedPiece.costume = pieces1[i].costume;
                // selectedPiece.posX = posX;
                // selectedPiece.posY = posY;
                break;
            }else if(pecas2[i].posX == posX && pecas2[i].posY == posY)
            {
                pecaEscolhida = pecas2[i].costume;
                // selectedPiece.costume = pieces2[i].costume;
                // selectedPiece.posX = posX;
                // selectedPiece.posY = posY;
                break;
            }
        }
        if(pecaEscolhida == ' ')//if player selects a blank space
        {
            printf("Espaço em branco, escolha um espaço válido");
            pecaEscolhida = ' ';
            posX = 0;
            posY=0;
            continue;
        }else if(turnoBranco == true && pecaEscolhida != toupper(pecaEscolhida))//if player selects a piece form the opponent
        {
            printf("Peça do oponete escolhida! Escolha uma peça sua!\n");
            pecaEscolhida = ' ';
            posX = 0;
            posY=0;
            continue;
        }else if(turnoBranco == false && pecaEscolhida == toupper(pecaEscolhida))//if player selects a piece form the opponent
        {
            printf("Peça do oponete escolhida! Escolha uma peça sua!\n");
            pecaEscolhida = ' ';
            posX = 0;
            posY=0;
            continue;
        }
        
        do{
            printf("Selecionou a peça %c(%d,%c)\nvocê quer trocar?(Y/N)?",pecaEscolhida,posX,posY);
            scanf(" %c",&resposta);
            resposta = toupper(resposta);
            if(resposta == 'Y')
            {
                escolha = false;
                pecaEscolhida = ' ';
                posX = 0;
                posY = 0;
                continue;
            }else if(resposta == 'N')
            {
                escolha = true;
                pecaSelecionada.costume = pecaEscolhida;
                pecaSelecionada.posX = posX;
                pecaSelecionada.posY = posY;                
            }
        }while(resposta != 'Y' && resposta != 'N');

    }
    for (int i = 0; i < 16; i++)
    {
        if(turnoBranco == true)
        {
            if(pecaSelecionada.costume == pecas1[i].costume && pecaSelecionada.posX == pecas1[i].posX && pecaSelecionada.posY == pecas1[i].posY)
            {
                index = i;  
                break;
            }
        }else if(turnoBranco == false)
        {
            if(pecaSelecionada.costume == pecas2[i].costume && pecaSelecionada.posX == pecas2[i].posX && pecaSelecionada.posY == pecas2[i].posY)
            {
                index = i;    
                break;
            }
        }                
    }
    printf("Peça selecionada é (%d) %c(%d,%c)\n",index,pecaSelecionada.costume,pecaSelecionada.posX,pecaSelecionada.posY);
    
    //show possible coordinates
    posX = 0;//select new line to move
    posY = 0;//select new column to move
    
        if(pecaSelecionada.costume == 'p' || pecaSelecionada.costume == 'P')//movement of pawn
        {
            //-> move forawrd only once
            //write available spaces
            int posicoesAtaqueDisponivel[4] ={0};
            int posicoesDisponiveis[2] = {0};
            int indicadorInimigo1 = 0,indicadorInimigo2 = 0;
            if(random == 0 && turnoBranco == true)
            {
                posicoesDisponiveis[0] = pecaSelecionada.posX + 1;
                posicoesDisponiveis[1] = pecaSelecionada.posY;
                if(pecaSelecionada.posY != 'A' && pecaSelecionada.posY !='H')
                {
                    posicoesAtaqueDisponivel[0] = pecaSelecionada.posX + 1;
                    posicoesAtaqueDisponivel[1] = pecaSelecionada.posY + 1;
                    posicoesAtaqueDisponivel[2] = pecaSelecionada.posX + 1;
                    posicoesAtaqueDisponivel[3] = pecaSelecionada.posY - 1;
                }
                else if(pecaSelecionada.posY == 'A')
                {
                    posicoesAtaqueDisponivel[0] = pecaSelecionada.posX + 1;
                    posicoesAtaqueDisponivel[1] = pecaSelecionada.posY + 1;
                    posicoesAtaqueDisponivel[2] = pecaSelecionada.posX + 1;
                    posicoesAtaqueDisponivel[3] = pecaSelecionada.posY + 1;
                }
                else if(pecaSelecionada.posY == 'H')
                {
                    posicoesAtaqueDisponivel[0] = pecaSelecionada.posX + 1;
                    posicoesAtaqueDisponivel[1] = pecaSelecionada.posY - 1;
                    posicoesAtaqueDisponivel[2] = pecaSelecionada.posX + 1;
                    posicoesAtaqueDisponivel[3] = pecaSelecionada.posY - 1;
                }
            }
            else if(random == 0 && turnoBranco == false)
            {
                posicoesDisponiveis[0] = pecaSelecionada.posX - 1;
                posicoesDisponiveis[1] = pecaSelecionada.posY;
                if(pecaSelecionada.posY != 'A' && pecaSelecionada.posY !='H')
                {
                    posicoesAtaqueDisponivel[0] = pecaSelecionada.posX - 1;
                    posicoesAtaqueDisponivel[1] = pecaSelecionada.posY + 1;
                    posicoesAtaqueDisponivel[2] = pecaSelecionada.posX - 1;
                    posicoesAtaqueDisponivel[3] = pecaSelecionada.posY - 1;
                }
                else if(pecaSelecionada.posY == 'A')
                {
                    posicoesAtaqueDisponivel[0] = pecaSelecionada.posX - 1;
                    posicoesAtaqueDisponivel[1] = pecaSelecionada.posY + 1;
                    posicoesAtaqueDisponivel[2] = pecaSelecionada.posX - 1;
                    posicoesAtaqueDisponivel[3] = pecaSelecionada.posY + 1;
                }
                else if(pecaSelecionada.posY == 'H')
                {
                    posicoesAtaqueDisponivel[0] = pecaSelecionada.posX - 1;
                    posicoesAtaqueDisponivel[1] = pecaSelecionada.posY - 1;
                    posicoesAtaqueDisponivel[2] = pecaSelecionada.posX - 1;
                    posicoesAtaqueDisponivel[3] = pecaSelecionada.posY - 1;
                }
            }
            else if(random == 1 && turnoBranco == true)
            {
                posicoesDisponiveis[0] = pecaSelecionada.posX - 1;
                posicoesDisponiveis[1] = pecaSelecionada.posY;
                if(pecaSelecionada.posY != 'A' && pecaSelecionada.posY !='H')
                {
                    posicoesAtaqueDisponivel[0] = pecaSelecionada.posX - 1;
                    posicoesAtaqueDisponivel[1] = pecaSelecionada.posY + 1;
                    posicoesAtaqueDisponivel[2] = pecaSelecionada.posX - 1;
                    posicoesAtaqueDisponivel[3] = pecaSelecionada.posY - 1;
                }
                else if(pecaSelecionada.posY == 'A')
                {
                    posicoesAtaqueDisponivel[0] = pecaSelecionada.posX - 1;
                    posicoesAtaqueDisponivel[1] = pecaSelecionada.posY + 1;
                    posicoesAtaqueDisponivel[2] = pecaSelecionada.posX - 1;
                    posicoesAtaqueDisponivel[3] = pecaSelecionada.posY + 1;
                }
                else if(pecaSelecionada.posY == 'H')
                {
                    posicoesAtaqueDisponivel[0] = pecaSelecionada.posX - 1;
                    posicoesAtaqueDisponivel[1] = pecaSelecionada.posY - 1;
                    posicoesAtaqueDisponivel[2] = pecaSelecionada.posX - 1;
                    posicoesAtaqueDisponivel[3] = pecaSelecionada.posY - 1;
                }
            }
            else if(random == 1 && turnoBranco == false)
            {
                posicoesDisponiveis[0] = pecaSelecionada.posX + 1;
                posicoesDisponiveis[1] = pecaSelecionada.posY;

                if(pecaSelecionada.posY != 'A' && pecaSelecionada.posY !='H')
                {
                    posicoesAtaqueDisponivel[0] = pecaSelecionada.posX + 1;
                    posicoesAtaqueDisponivel[1] = pecaSelecionada.posY + 1;
                    posicoesAtaqueDisponivel[2] = pecaSelecionada.posX + 1;
                    posicoesAtaqueDisponivel[3] = pecaSelecionada.posY - 1;
                }
                else if(pecaSelecionada.posY == 'A')
                {
                    posicoesAtaqueDisponivel[0] = pecaSelecionada.posX + 1;
                    posicoesAtaqueDisponivel[1] = pecaSelecionada.posY + 1;
                    posicoesAtaqueDisponivel[2] = pecaSelecionada.posX + 1;
                    posicoesAtaqueDisponivel[3] = pecaSelecionada.posY + 1;
                }
                else if(pecaSelecionada.posY == 'H')
                {
                    posicoesAtaqueDisponivel[0] = pecaSelecionada.posX + 1;
                    posicoesAtaqueDisponivel[1] = pecaSelecionada.posY - 1;
                    posicoesAtaqueDisponivel[2] = pecaSelecionada.posX + 1;
                    posicoesAtaqueDisponivel[3] = pecaSelecionada.posY - 1;
                }
            }
            
            //printf("-> %d %c\n",availablePositions[0],availablePositions[1]);
            if(turnoBranco == true)
            {
                bool encontro1,encontro2;//found eatable pieces;
                bool encontro3 = false;//found forward enemy or ally piece 

                for(int i = 0; i < sizeof pecas2/sizeof pecas2[0];i++)
                {

                    if((pecas2[i].posX == posicoesDisponiveis[0] && pecas2[i].posY == posicoesDisponiveis[1]) || (pecas1[i].posX == posicoesDisponiveis[0] && pecas1[i].posY == posicoesDisponiveis[1]))
                    {
                        encontro3 = true;
                        posicoesDisponiveis[0] = 0;
                        posicoesDisponiveis[1] = 0;
                    }

                    if(pecas2[i].posX == posicoesAtaqueDisponivel[0] && pecas2[i].posY == posicoesAtaqueDisponivel[1])
                    {
                        printf("-> %d %c\n",posicoesAtaqueDisponivel[0],posicoesAtaqueDisponivel[1]);
                        indicadorInimigo1 = i;
                        encontro1 = true;
                    }

                    if(pecas2[i].posX == posicoesAtaqueDisponivel[2] && pecas2[i].posY == posicoesAtaqueDisponivel[3])
                    {
                        printf("-> %d %c\n",posicoesAtaqueDisponivel[2],posicoesAtaqueDisponivel[3]);
                        indicadorInimigo2 = i;
                        encontro2 = true;
                    }
                }

                if(encontro1 == false)
                {
                    posicoesAtaqueDisponivel[0] = 0;
                    posicoesAtaqueDisponivel[1] = 0;
                }
                if(encontro2 == false)
                {
                    posicoesAtaqueDisponivel[2] = 0;
                    posicoesAtaqueDisponivel[3] = 0;
                }
                if(encontro3 == false)
                {
                    printf("-> %d %c\n",posicoesDisponiveis[0],posicoesDisponiveis[1]);
                }

            }
            else if(turnoBranco ==false)
            {
                bool encontro1,encontro2;//found eatable enemy piece
                bool encontro3 = false;//found forward enemy or ally piece
                for(int i = 0; i< sizeof pecas1/sizeof pecas1[0];i++)
                {      
                    if((pecas1[i].posX == posicoesDisponiveis[0] && pecas1[i].posY == posicoesDisponiveis[1]) || (pecas2[i].posX == posicoesDisponiveis[0] && pecas2[i].posY == posicoesDisponiveis[1]))
                    {
                        encontro3 = true;
                        posicoesDisponiveis[0] = 0;
                        posicoesDisponiveis[1] = 0;
                    }

                    if(pecas1[i].posX == posicoesAtaqueDisponivel[0] && pecas1[i].posY == posicoesAtaqueDisponivel[1])
                    {
                        printf("-> %d %c\n",posicoesAtaqueDisponivel[0],posicoesAtaqueDisponivel[1]);
                        indicadorInimigo1 = i;
                        encontro1 = true;
                    }

                    if(pecas1[i].posX == posicoesAtaqueDisponivel[2] && pecas1[i].posY == posicoesAtaqueDisponivel[3])
                    {
                        printf("-> %d %c\n",posicoesAtaqueDisponivel[2],posicoesAtaqueDisponivel[3]);
                        indicadorInimigo2 = i;
                        encontro2 = true;
                    }                    
                }
                if(encontro1 == false)
                {
                    posicoesAtaqueDisponivel[0] = 0;
                    posicoesAtaqueDisponivel[1] = 0;
                }
                if(encontro2 == false)
                {
                    posicoesAtaqueDisponivel[2] = 0;
                    posicoesAtaqueDisponivel[3] = 0;
                } 
                if(encontro3 == false)
                {
                    printf("-> %d %c\n",posicoesDisponiveis[0],posicoesDisponiveis[1]);
                }
            }
            

            //get position inputed by player
            if(!(posicoesDisponiveis[0] == 0 && posicoesDisponiveis[1] == 0) || !(posicoesAtaqueDisponivel[0] == 0 && posicoesAtaqueDisponivel[1] == 0) || !(posicoesAtaqueDisponivel[2] == 0 && posicoesAtaqueDisponivel[3] == 0))
            {
                bool checkPosX= false;
                bool checkPosY= false;
                do
                {
                    printf("Selecione a linha");
                    scanf("%d",&posX);
                    for (int i = 0; i < sizeof posicoesDisponiveis /sizeof posicoesDisponiveis[0]; i+=2)
                    {
                        if(posX == posicoesDisponiveis[i])
                        {
                            checkPosX = true;
                            break;
                        }                    
                    }     

                    for (int i = 0; i < sizeof posicoesAtaqueDisponivel /sizeof posicoesAtaqueDisponivel[0]; i+=2)
                    {
                        if(posX == posicoesAtaqueDisponivel[i])
                        {
                            checkPosX = true;
                            break;
                        }                    
                    }

                    if(checkPosX == false)//if the choice is outside of the table, teel the player that he is out of bounds
                    {
                        printf("Linha não disponível para o movimento!\n");
                    }
                }while(checkPosX == false);

                do
                {
                    printf("Selecione a coluna:");
                    scanf(" %c",&posY);
                    posY = toupper(posY);
                    
                    for (int i = 1; i < sizeof posicoesDisponiveis /sizeof posicoesDisponiveis[0]; i+=2)
                    {
                        if(posY == posicoesDisponiveis[i])
                        {
                            checkPosY = true;
                            break;
                        }                    
                    }

                    for (int i = 1; i < sizeof posicoesAtaqueDisponivel /sizeof posicoesAtaqueDisponivel[0]; i+=2)
                    {
                        if(posY == posicoesAtaqueDisponivel[i])
                        {
                            checkPosY = true;
                            break;
                        }                    
                    } 
                    if(checkPosY == false)//if the choice is outside of the table, teel the player that he is out of bounds
                    {
                        printf("Colona não dispoível para movimento!\n");
                    }
                }while(checkPosY == false);

                if(turnoBranco == true)
                {
                    if((posX == pecas2[indicadorInimigo1].posX && posY == pecas2[indicadorInimigo1].posY))
                    {
                        pecas2[indicadorInimigo1].posX = 0;
                        pecas2[indicadorInimigo1].posY = 0;

                    }

                    if((posX == pecas2[indicadorInimigo2].posX && posY == pecas2[indicadorInimigo2].posY))
                    {
                        pecas2[indicadorInimigo2].posX = 0;
                        pecas2[indicadorInimigo2].posY = 0;
                    }
                    
                    pecas1[index].posX = posX;
                    pecas1[index].posY = posY;
                }
                else
                {
                    if((posX == pecas1[indicadorInimigo1].posX && posY == pecas1[indicadorInimigo1].posY))
                    {
                        pecas1[indicadorInimigo1].posX = 0;
                        pecas1[indicadorInimigo1].posY = 0;
                    }

                    if((posX == pecas1[indicadorInimigo2].posX && posY == pecas1[indicadorInimigo2].posY))
                    {
                        pecas1[indicadorInimigo2].posX = 0;
                        pecas1[indicadorInimigo2].posY = 0;
                    }

                    pecas2[index].posX = posX;
                    pecas2[index].posY = posY;
                }                                
            }
        }
        else if(pecaSelecionada.costume == 'r' || pecaSelecionada.costume == 'R')//movement rook
        {
            int diferencaCima = pecaSelecionada.posX - 1;
            int diferencaDireita = 'H' - pecaSelecionada.posY;
            int diferencaBaixo = 8 - pecaSelecionada.posX;
            int diferencaEsquerda = pecaSelecionada.posY - 'A';
            //int availablePositions[14][2] = {0};
            
            int posicaoDisponivelCima[7][2] = {0};
            int posicaoDisponivelBaixo[7][2] = {0};
            int posicaoDisponivelDireita[7][2] = {0};
            int posicaoDisponivelEsquerda[7][2] = {0};
            //int counter = 0;

            bool encontroPeca = false;

            // printf("%d",diferenceTop);    
            for(int i = 0; i<diferencaCima;i++)//positions on top of tower
            {
                for(int p = 0;p < 16;p++)
                {
                    if(turnoBranco == true)
                    {
                        if(pecas1[p].posX == pecaSelecionada.posX-(i+1) && pecas1[p].posY == pecaSelecionada.posY)
                        {
                            encontroPeca = true;
                            posicaoDisponivelCima[i][0] = 0;
                            posicaoDisponivelCima[i][1] = 0;
                            // counter++;
                            break;
                        }
                        else if(encontroPeca == false)
                        {
                            posicaoDisponivelCima[i][0] = pecaSelecionada.posX-(i+1);
                            posicaoDisponivelCima[i][1] = pecaSelecionada.posY;
                            //counter++;
                        }
                    }else if(turnoBranco == false)
                    {
                        if(pecas2[p].posX == pecaSelecionada.posX-(i+1) && pecas2[p].posY == pecaSelecionada.posY)
                        {
                            encontroPeca = true;
                            posicaoDisponivelCima[i][0] = 0;
                            posicaoDisponivelCima[i][1] = 0;
                            // counter++;
                            break;
                        }
                        else if(encontroPeca == false)
                        {
                            posicaoDisponivelCima[i][0] = pecaSelecionada.posX-(i+1);
                            posicaoDisponivelCima[i][1] = pecaSelecionada.posY;
                            //counter++;
                        }
                    }                    
                }
            }

            //printf("%d\n",counter);
            encontroPeca = false;            
            for(int i = 0; i<diferencaBaixo;i++)//positions on bottom of tower
            {
                for(int p = 0;p < 16;p++)
                {
                    if(turnoBranco == true)
                    {
                        if(pecas1[p].posX == pecaSelecionada.posX+(i+1) && pecas1[p].posY == pecaSelecionada.posY)
                        {
                            encontroPeca = true;
                            posicaoDisponivelBaixo[i][0] = 0;
                            posicaoDisponivelBaixo[i][1] = 0;
                            //counter++;
                            break;
                        }
                        else if(encontroPeca == false)
                        {
                            posicaoDisponivelBaixo[i][0] = pecaSelecionada.posX+(i+1);
                            posicaoDisponivelBaixo[i][1] = pecaSelecionada.posY;
                            //counter++;
                        }
                    }else if(turnoBranco == false)
                    {
                        if(pecas2[p].posX == pecaSelecionada.posX+(i+1) && pecas2[p].posY == pecaSelecionada.posY)
                        {
                            encontroPeca = true;
                            posicaoDisponivelBaixo[i][0] = 0;
                            posicaoDisponivelBaixo[i][1] = 0;
                            //counter++;
                            break;
                        }
                        else if(encontroPeca == false)
                        {
                            posicaoDisponivelBaixo[i][0] = pecaSelecionada.posX+(i+1);
                            posicaoDisponivelBaixo[i][1] = pecaSelecionada.posY;
                            //counter++;
                        }
                    }        
                }
            }
            // printf("%d\n",counter);
            //foundPiece = false;
            for(int i = 0; i<diferencaDireita;i++)//positions on bottom of tower
            {
                for(int p = 0;p < 16;p++)
                {
                    if(turnoBranco == true)
                    {
                        if(pecas1[p].posX == pecaSelecionada.posX && pecas1[p].posY == pecaSelecionada.posY+(i+1))
                        {
                            encontroPeca = true;
                            posicaoDisponivelDireita[i][0] = 0;
                            posicaoDisponivelDireita[i][1] = 0;
                            // counter++;
                            break;
                        }
                        else if(encontroPeca == false)
                        {
                            posicaoDisponivelDireita[i][0] = pecaSelecionada.posX;
                            posicaoDisponivelDireita[i][1] = pecaSelecionada.posY+(i+1);
                            // counter++;
                        }
                    }else if(turnoBranco == false)
                    {
                        printf("Passei aqui1!\n");
                        if(pecas2[p].posX == pecaSelecionada.posX && pecas2[p].posY == pecaSelecionada.posY+(i+1))
                        {
                            printf("Passei aqui2!\n");
                            encontroPeca = true;
                            posicaoDisponivelDireita[i][0] = 0;
                            posicaoDisponivelDireita[i][1] = 0;
                            // counter++;
                            break;
                        }
                        else if(encontroPeca == false)
                        {
                            printf("Passei aqui3!\n");
                            posicaoDisponivelDireita[i][0] = pecaSelecionada.posX;
                            posicaoDisponivelDireita[i][1] = pecaSelecionada.posY+(i+1);
                            // counter++;
                        }
                    }        
                }
            }
            encontroPeca = false;
            for(int i = 0; i<diferencaEsquerda;i++)//positions on bottom of tower
            {
                for(int p = 0;p < 16;p++)
                {
                    if(turnoBranco == true)
                    {
                        if(pecas1[p].posX == pecaSelecionada.posX && pecas1[p].posY == pecaSelecionada.posY-(i+1))
                        {
                            encontroPeca = true;
                            posicaoDisponivelEsquerda[i][0] = 0;
                            posicaoDisponivelEsquerda[i][1] = 0;
                            // counter++;
                            break;
                        }
                        else if(encontroPeca == false)
                        {
                            posicaoDisponivelEsquerda[i][0] = pecaSelecionada.posX;
                            posicaoDisponivelEsquerda[i][1] = pecaSelecionada.posY-(i+1);
                            // counter++;
                        }
                    }else if(turnoBranco == false)
                    {
                        if(pecas2[p].posX == pecaSelecionada.posX && pecas2[p].posY == pecaSelecionada.posY-(i+1))
                        {
                            encontroPeca = true;
                            posicaoDisponivelEsquerda[i][0] = 0;
                            posicaoDisponivelEsquerda[i][1] = 0;
                            // counter++;
                            break;
                        }
                        else if(encontroPeca == false)
                        {
                            posicaoDisponivelEsquerda[i][0] = pecaSelecionada.posX;
                            posicaoDisponivelEsquerda[i][1] = pecaSelecionada.posY-(i+1);
                            // counter++;
                        }
                    }        
                }
            }

            bool encontroPosicao = false;

            for(int i = 0;i<7;i++)
            {
                if(posicaoDisponivelCima[i][0] != 0 && posicaoDisponivelCima[i][1] != 0)
                {
                    printf("-> %d %c\n",posicaoDisponivelCima[i][0],posicaoDisponivelCima[i][1]);
                    encontroPosicao = true;
                }
            }

            for(int i = 0;i<7;i++)
            {
                if(posicaoDisponivelBaixo[i][0] != 0 && posicaoDisponivelBaixo[i][1] != 0)
                {
                    printf("-> %d %c\n",posicaoDisponivelBaixo[i][0],posicaoDisponivelBaixo[i][1]);
                    encontroPosicao = true;
                }
            }

            for(int i = 0;i<7;i++)
            {
                if(posicaoDisponivelEsquerda[i][0] != 0 && posicaoDisponivelEsquerda[i][1] != 0)
                {
                    printf("-> %d %c\n",posicaoDisponivelEsquerda[i][0],posicaoDisponivelEsquerda[i][1]);
                    encontroPosicao = true;
                }
            }

            for(int i = 0;i<7;i++)
            {
                if(posicaoDisponivelDireita[i][0] != 0 && posicaoDisponivelDireita[i][1] != 0)
                {
                    printf("-> %d %c\n",posicaoDisponivelDireita[i][0],posicaoDisponivelDireita[i][1]);
                    encontroPosicao = true;
                }
            }

            bool checkPosX = false;
            bool checkPosY = false;
            if(encontroPosicao)
            {
                do
                {
                    printf("Selecione a linha: ");
                    scanf("%d",&posX);
                    for(int l = 0; l < 14;l++)
                    {
                        if((posX == posicaoDisponivelCima[l][0] || posX == posicaoDisponivelBaixo[l][0] || posX == posicaoDisponivelEsquerda[l][0] || posX == posicaoDisponivelDireita[l][0]) && posX != 0)
                        {
                            checkPosX = true;
                            break;
                        }
                    }
                    if(checkPosX == false)
                    {
                        printf("Linha não disponivel para movimento\n");
                    }
                    
                } while (checkPosX == false);
                
                do
                {
                    printf("Selecione a coluna: ");
                    scanf(" %c",&posY);
                    posY = toupper(posY);
                    for(int l = 0; l < 14;l++)
                    {
                        if((posY == posicaoDisponivelCima[l][1] || posY == posicaoDisponivelBaixo[l][1] || posY == posicaoDisponivelEsquerda[l][1] || posY == posicaoDisponivelDireita[l][1]) && posY != 0)
                        {
                            checkPosY = true;
                            break;
                        }                    
                    }
                    if(checkPosY == false)
                    {
                        printf("Coluna não disponivel para movimento\n");
                    }
                    
                } while (checkPosY == false);

                if(turnoBranco == true)
                {
                    pecas1[index].posX = posX;
                    pecas1[index].posY = posY;

                }else
                {
                    pecas2[index].posX = posX;
                    pecas2[index].posY = posY;
                }
            }            
        }
        else if(pecaSelecionada.costume == 'n' || pecaSelecionada.costume == 'N')//movement of knight
        {
            //-> move in L chape 
            int posicoesDisponiveis[8][2] = {0};
            bool checkPosX = false;
            bool checkPosY = false;
            posicoesDisponiveis[0][0] = pecaSelecionada.posX+2;
            posicoesDisponiveis[1][0] = pecaSelecionada.posX+2;
            posicoesDisponiveis[0][1] = pecaSelecionada.posY-1;
            posicoesDisponiveis[1][1] = pecaSelecionada.posY+1;

            posicoesDisponiveis[2][0] = pecaSelecionada.posX+1;
            posicoesDisponiveis[3][0] = pecaSelecionada.posX-1;
            posicoesDisponiveis[2][1] = pecaSelecionada.posY+2;
            posicoesDisponiveis[3][1] = pecaSelecionada.posY+2;

            posicoesDisponiveis[4][0] = pecaSelecionada.posX-2;
            posicoesDisponiveis[5][0] = pecaSelecionada.posX-2;
            posicoesDisponiveis[4][1] = pecaSelecionada.posY-1;
            posicoesDisponiveis[5][1] = pecaSelecionada.posY+1;

            posicoesDisponiveis[6][0] = pecaSelecionada.posX-1;
            posicoesDisponiveis[7][0] = pecaSelecionada.posX+1;
            posicoesDisponiveis[6][1] = pecaSelecionada.posY-2;
            posicoesDisponiveis[7][1] = pecaSelecionada.posY-2;
          


            for(int i = 0; i < 8 ; i++)
            {
                if(posicoesDisponiveis[i][0] < 1 || posicoesDisponiveis[i][0] > 8)
                {
                    posicoesDisponiveis[i][0] = 0;
                    posicoesDisponiveis[i][1] = 0;
                }

                if(posicoesDisponiveis[i][1] < 'A' || posicoesDisponiveis[i][1] > 'H')
                {
                    posicoesDisponiveis[i][0] = 0;
                    posicoesDisponiveis[i][1] = 0;
                }
            }

            if(turnoBranco == true)
            {
                for(int p = 0; p < 16 ; p++)
                {
                    for(int pos = 0; pos < 8 ; pos++)
                    {
                        if(pecas1[p].posX == posicoesDisponiveis[pos][0] && pecas1[p].posY == posicoesDisponiveis[pos][1])
                        {
                            posicoesDisponiveis[pos][0] = 0;
                            posicoesDisponiveis[pos][1] = 0;
                        }
                    }
                }
            }
            else if(turnoBranco == false)
            {
                for(int p = 0; p < 16 ; p++)
                {
                    for(int pos = 0; pos < 8 ; pos++)
                    {
                        if(pecas2[p].posX == posicoesDisponiveis[pos][0] && pecas2[p].posY == posicoesDisponiveis[pos][1])
                        {
                            posicoesDisponiveis[pos][0] = 0;
                            posicoesDisponiveis[pos][1] = 0;
                        }
                    }
                }
            }

            bool posicoesExistentes = false;
            for(int i = 0;i<8;i++)
            {
                if(posicoesDisponiveis[i][0] != 0 && posicoesDisponiveis[i][1] != 0)
                {
                    printf("-> %d %c\n",posicoesDisponiveis[i][0],posicoesDisponiveis[i][1]);
                    posicoesExistentes = true;
                }
            }

            if(posicoesExistentes == true)
            {
                do
                {
                    printf("Selecione a linha: ");
                    scanf("%d",&posX);
                    for(int pos = 0; pos < 8 ; pos++)
                    {
                        if(posicoesDisponiveis[pos][0] == posX)
                        {
                            checkPosX = true;
                            break;
                        }else
                        {
                            checkPosX = false;
                        }                    
                    }
                    if(checkPosX == false)
                    {
                        printf("Linha não dispoível para movimento!");
                    }

                } while (checkPosX == false);
                
                do
                {
                    printf("Selecione a coluna: ");
                    scanf(" %c",&posY);
                    posY = toupper(posY);
                    for(int pos = 0; pos < 8 ; pos++)
                    {
                        if(posicoesDisponiveis[pos][1] == posY)
                        {
                            checkPosY = true;
                            break;
                        }else
                        {
                            checkPosY = false;
                        }                    
                    }
                    if(checkPosY == false)
                    {
                        printf("Coluna não dispoível para o movimento!");
                    }
                } while (checkPosY == false);

                if(turnoBranco == true)
                {
                    for(int i = 0; i<16;i++)
                    {
                        if(posX == pecas2[i].posX && posY == pecas2[i].posY)
                        {
                            pecas2[i].posX = 0;
                            pecas2[i].posY = 0;
                            break;
                        }
                    }
                    pecas1[index].posX = posX;
                    pecas1[index].posY = posY;

                }
                else if(turnoBranco == false)
                {
                    for(int i = 0; i<16;i++)
                    {
                        if(posX == pecas1[i].posX && posY == pecas1[i].posY)
                        {
                            pecas1[i].posX = 0;
                            pecas1[i].posY = 0;
                            break;
                        }
                    }
                    pecas2[index].posX = posX;
                    pecas2[index].posY = posY;                
                }
            }            
        }
        else if(pecaSelecionada.costume == 'b' || pecaSelecionada.costume == 'B')//movivento do bispo
        {
            //-> diagonal
        }
        else if(pecaSelecionada.costume == 'q' || pecaSelecionada.costume == 'Q')//movimento da Rainha
        {
            //-> em todas as direções o quanto quiseres
        }
        else if(pecaSelecionada.costume == 'k' || pecaSelecionada.costume == 'K')//Movimento do Rei
        {
            //-> em todas as direções apenas um tile.
            int posicoesDisponiveis[8][2] = {0};
            bool checkPosX = false;
            bool checkPosY = false;
            posicoesDisponiveis[0][0] = pecaSelecionada.posX+1;
            posicoesDisponiveis[0][1] = pecaSelecionada.posY;
            posicoesDisponiveis[1][0] = pecaSelecionada.posX+1;
            posicoesDisponiveis[1][1] = pecaSelecionada.posY+1;
            posicoesDisponiveis[2][0] = pecaSelecionada.posX+1;
            posicoesDisponiveis[2][1] = pecaSelecionada.posY-1;

            posicoesDisponiveis[3][0] = pecaSelecionada.posX-1;
            posicoesDisponiveis[3][1] = pecaSelecionada.posY;
            posicoesDisponiveis[4][0] = pecaSelecionada.posX-1;
            posicoesDisponiveis[4][1] = pecaSelecionada.posY+1;
            posicoesDisponiveis[5][0] = pecaSelecionada.posX-1;
            posicoesDisponiveis[5][1] = pecaSelecionada.posY-1;

            posicoesDisponiveis[6][0] = pecaSelecionada.posX;
            posicoesDisponiveis[6][1] = pecaSelecionada.posY-1;

            posicoesDisponiveis[7][0] = pecaSelecionada.posX;
            posicoesDisponiveis[7][1] = pecaSelecionada.posY+1;

            for(int i = 0; i < 8 ; i++)
            {
                if(posicoesDisponiveis[i][0] < 1 || posicoesDisponiveis[i][0] > 8)
                {
                    posicoesDisponiveis[i][0] = 0;
                    posicoesDisponiveis[i][1] = 0;
                }

                if(posicoesDisponiveis[i][1] < 'A' || posicoesDisponiveis[i][1] > 'H')
                {
                    posicoesDisponiveis[i][0] = 0;
                    posicoesDisponiveis[i][1] = 0;
                }
            }

            if(turnoBranco == true)
            {
                for(int p = 0; p < 16 ; p++)
                {
                    for(int pos = 0; pos < 8 ; pos++)
                    {
                        if(pecas1[p].posX == posicoesDisponiveis[pos][0] && pecas1[p].posY == posicoesDisponiveis[pos][1])
                        {
                            posicoesDisponiveis[pos][0] = 0;
                            posicoesDisponiveis[pos][1] = 0;
                        }
                    }
                }
            }
            else if(turnoBranco == false)
            {
                for(int p = 0; p < 16 ; p++)
                {
                    for(int pos = 0; pos < 8 ; pos++)
                    {
                        if(pecas2[p].posX == posicoesDisponiveis[pos][0] && pecas2[p].posY == posicoesDisponiveis[pos][1])
                        {
                            posicoesDisponiveis[pos][0] = 0;
                            posicoesDisponiveis[pos][1] = 0;
                        }
                    }
                }
            }
            bool existPositions = false;
            for(int i = 0;i<8;i++)
            {
                if(posicoesDisponiveis[i][0] != 0 && posicoesDisponiveis[i][1] != 0)
                {
                    printf("-> %d %c\n",posicoesDisponiveis[i][0],posicoesDisponiveis[i][1]);
                    existPositions = true;
                }
            }

            if(existPositions == true)
            {
                do
                {
                    printf("Selecione a linha: ");
                    scanf("%d",&posX);
                    for(int pos = 0; pos < 8 ; pos++)
                    {
                        if(posicoesDisponiveis[pos][0] == posX)
                        {
                            checkPosX = true;
                            break;
                        }else
                        {
                            checkPosX = false;
                        }                    
                    }
                    if(checkPosX == false)
                    {
                        printf("Linha não disponivel para movimento\n");
                    }

                } while (checkPosX == false);
                
                do
                {
                    printf("Selecione a coluna: ");
                    scanf(" %c",&posY);
                    posY = toupper(posY);
                    for(int pos = 0; pos < 8 ; pos++)
                    {
                        if(posicoesDisponiveis[pos][1] == posY)
                        {
                            checkPosY = true;
                            break;
                        }else
                        {
                            checkPosY = false;
                        }                    
                    }
                    if(checkPosY == false)
                    {
                        printf("Coluna não disponivel para movimento\n");
                    }
                } while (checkPosY == false);

                if(turnoBranco == true)
                {
                    for(int i = 0; i<16;i++)
                    {
                        if(posX == pecas2[i].posX && posY == pecas2[i].posY)
                        {
                            pecas2[i].posX = 0;
                            pecas2[i].posY = 0;
                        }
                    }
                    pecas1[index].posX = posX;
                    pecas1[index].posY = posY;

                }
                else if(turnoBranco == false)
                {
                    for(int i = 0; i<16;i++)
                    {
                        if(posX == pecas1[i].posX && posY == pecas1[i].posY)
                        {
                            pecas1[i].posX = 0;
                            pecas1[i].posY = 0;
                            break;
                        }
                    }
                    pecas2[index].posX = posX;
                    pecas2[index].posY = posY;                
                }
            }          
        }
        
        reCreateTable();
        turnoBranco = !turnoBranco;    
}    


    
