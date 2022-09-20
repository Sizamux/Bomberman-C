 /*      Jogo -base Bomberman
 *      Autor:Luiz Carlos/ Social: Danniele Marini
 *      Obs: Criando engine similar a Bomberman
 *      Linguagem:C
*/
#define LEVEL1 25
#define LEVEL2 40
#define LEVEL3 50
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h> //Sleep
#include <conio2.h>

//Struct Pos para M
struct Pos2{
    int pX, pY, vida;
};

struct Pos2 mon[3];
char tabuleiro[13][16];
int pontuacao=0, delaymMon=0, qua=3, vit, levelCur=1;
int pXb, pYb, yBomba, xBomba; //Pos
int flagX, tempoX=0,flagB, tempoB=0, flagD=0; //Bomba e Explosão

//cor
void textcolor(int newcolor){
CONSOLE_SCREEN_BUFFER_INFO csbi;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
(csbi.wAttributes & 0xf0) | newcolor);
}

//go to x,y
void gotoxy(int x,int y){
   COORD c;
   c.X = x - 1;
   c.Y = y - 1;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

//----------------------------------------------------------------------//
void cantos(char letra, int X, int Y){//canto1
    int i;
    gotoxy(X,Y);
    printf("%c", letra);
}

void coluna(char letra, int C, int Ii, int If){//canto2
   int i;
   for(i=Ii;i<=If;i++){
       gotoxy(C,i);
       printf("%c", letra);
   }
}

void linha(char letra, int I, int Ci, int Cf){//canto3
    int c;
    for(c=Ci;c<=Cf;c++){
       gotoxy(c,I);
       printf("%c", letra);
   }
}

void todosCantos(){ //desenha todos cantos p/ fazer quadro
    textcolor (2);
    cantos(201, 1, 1);
    cantos(187, 80, 1);
    cantos(200, 1, 23);
    cantos(188, 80, 23);
    linha(205, 1, 2, 79);
    linha(205, 23, 2, 79);
    coluna(186, 1, 2, 22);
    coluna(186, 80, 2, 22);
}

void introducao(int X,int Y){ //printa cutscene introducao
    textcolor (2);
    gotoxy(X,Y);    printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+1);  printf("```````3434343@````-=@@=@@@@@@@@@@@=-`````````````````````````````````````````\n");
    gotoxy(X,Y+2);  printf("`````43``````-43`````-@--@@----@@-````````````````````````````@@@@@@``````````\n");
    gotoxy(X,Y+3);  printf("````43```-```````````````````-@@-`````````````````````@@```````````@@`````````\n");
    gotoxy(X,Y+4);  printf("````43``````-```````````````-@@-``````````````````````@@````````````@@````````\n");
    gotoxy(X,Y+5);  printf("`````43`-````````````````343@@-````````````````````````````````````@@`````````\n");
    gotoxy(X,Y+6);  printf("```````43@434343``````````-@@3434```````````````````````````````@@@@``````````\n");
    gotoxy(X,Y+7);  printf("`````````@-```@43```````-@@-```````-@=-```````````````````````````@@@`````````\n");
    gotoxy(X,Y+8);  printf("```````-```````@43``-```-@@-``````-@@-````````````````@@```````````@@`````````\n");
    gotoxy(X,Y+9);  printf("````@@````-```@@43````-@@-`````-@@@-``````````````````@@````````````@@````````\n");
    gotoxy(X,Y+10); printf("`````@@@@@``@@43````-=@@@@@@@@@@@@-``````````````````````````@@````@@`````````\n");
    gotoxy(X,Y+11); printf("``````````````````````````````````````````````````````````````@@@@@@``````````\n");
    gotoxy(X,Y+12); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+13); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+14); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+15); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+16); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+17); printf("```Criador:````''`````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+18); printf("```LUIZ`CARLOS - Aka DANNIELE MARINI``````````````````````````````````````````\n");
    gotoxy(X,Y+19); printf("````````'`````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+20); printf("``````````````````````````````````````````````````````````````````````````````\n");
    Sleep(400);
    gotoxy(X,Y);    printf("  888888ba                      dP                                            \n");
    gotoxy(X,Y+1);  printf("  88    `8b                     88                                            \n");
    gotoxy(X,Y+2);  printf(" a88aaaa8P' .d8888b. 88d8b.d8b. 88d888b. .d8888b. 88d888b.                    \n");
    gotoxy(X,Y+3);  printf("  88   `8b. 88'  `88 88'`88'`88 88'  `88 88ooood8 88'  `88                    \n");
    gotoxy(X,Y+4);  printf("  88    .88 88.  .88 88  88  88 88.  .88 88.  ... 88                          \n");
    gotoxy(X,Y+5);  printf("  88888888P `88888P' dP  dP  dP 88Y8888' `88888P' dP                          \n");
    gotoxy(X,Y+6);  printf("                                                                              \n");
    gotoxy(X,Y+7);  printf("                                                                              \n");
    gotoxy(X,Y+8);  printf("                                                                              \n");
    gotoxy(X,Y+9);  printf("                                                                              \n");
    gotoxy(X,Y+10); printf("                                                                              \n");
    gotoxy(X,Y+11); printf("                                                                              \n");
    gotoxy(X,Y+12); printf("                                                                              \n");
    gotoxy(X,Y+13); printf("                                                                              \n");
    gotoxy(X,Y+14); printf("                                                                              \n");
    gotoxy(X,Y+15); printf("                                                                              \n");
    gotoxy(X,Y+16); printf("                                                                              \n");
    gotoxy(X,Y+17); printf("   Criador:                                                                   \n");
    gotoxy(X,Y+18); printf("   LUIZ CARLOS - Aka DANNIELE MARINI                                          \n");
    gotoxy(X,Y+19); printf("                                                                              \n");
    gotoxy(X,Y+20); printf("                                                                              \n");
    Sleep(600);
    gotoxy(X,Y);    printf(" 888888ba                      dP                                             \n");
    gotoxy(X,Y+1);  printf(" 88    `8b                     88                                             \n");
    gotoxy(X,Y+2);  printf("a88aaaa8P' .d8888b. 88d8b.d8b. 88d888b. .d8888b. 88d888b.                     \n");
    gotoxy(X,Y+3);  printf(" 88   `8b. 88'  `88 88'`88'`88 88'  `88 88ooood8 88'  `88                     \n");
    gotoxy(X,Y+4);  printf(" 88    .88 88.  .88 88  88  88 88.  .88 88.  ... 88                           \n");
    gotoxy(X,Y+5);  printf(" 88888888P `88888P' dP  dP  dP 88Y8888' `88888P' dP                           \n");
    gotoxy(X,Y+6);  printf("                                                                              \n");
    gotoxy(X,Y+7);  printf("                                         8888ba.88ba                          \n");
    gotoxy(X,Y+8);  printf("                                         88  `8b  `8b                         \n");
    gotoxy(X,Y+9);  printf("                                         88   88   88 .d8888b. 88d888b.       \n");
    gotoxy(X,Y+10); printf("                                         88   88   88 88'  `88 88'  `88       \n");
    gotoxy(X,Y+11); printf("                                         88   88   88 88.  .88 88    88       \n");
    gotoxy(X,Y+12); printf("                                         dP   dP   dP `88888P8 dP    dP       \n");
    gotoxy(X,Y+13); printf("                                                                              \n");
    gotoxy(X,Y+14); printf("                                                                              \n");
    gotoxy(X,Y+15); printf("                                                                              \n");
    gotoxy(X,Y+16); printf("                                                                              \n");
    gotoxy(X,Y+17); printf("                                                                              \n");
    gotoxy(X,Y+18); printf("   LUIZ CARLOS - Aka DANNIELE MARINI                                          \n");
    gotoxy(X,Y+19); printf("                                                                              \n");
    gotoxy(X,Y+20); printf("                                                                              \n");
    Sleep(1000);
    gotoxy(X,Y);    printf("  888888ba                      dP                                            \n");
    gotoxy(X,Y+1);  printf("  88    `8b                     88                                            \n");
    gotoxy(X,Y+2);  printf(" a88aaaa8P' .d8888b. 88d8b.d8b. 88d888b. .d8888b. 88d888b.                    \n");
    gotoxy(X,Y+3);  printf("  88   `8b. 88'  `88 88'`88'`88 88'  `88 88ooood8 88'  `88                    \n");
    gotoxy(X,Y+4);  printf("  88    .88 88.  .88 88  88  88 88.  .88 88.  ... 88                          \n");
    gotoxy(X,Y+5);  printf("  88888888P `88888P' dP  dP  dP 88Y8888' `88888P' dP                          \n");
    gotoxy(X,Y+6);  printf("                                                                              \n");
    gotoxy(X,Y+7);  printf("                                         8888ba.88ba                          \n");
    gotoxy(X,Y+8);  printf("                                         88  `8b  `8b                         \n");
    gotoxy(X,Y+9);  printf("                                         88   88   88 .d8888b. 88d888b.       \n");
    gotoxy(X,Y+10); printf("                                         88   88   88 88'  `88 88'  `88       \n");
    gotoxy(X,Y+11); printf("                                         88   88   88 88.  .88 88    88       \n");
    gotoxy(X,Y+12); printf("                                         dP   dP   dP `88888P8 dP    dP       \n");
    gotoxy(X,Y+13); printf("                                                                              \n");
    gotoxy(X,Y+14); printf("                                                                              \n");
    gotoxy(X,Y+15); printf("                                                                              \n");
    gotoxy(X,Y+16); printf("                                                                              \n");
    gotoxy(X,Y+17); printf("                                                                              \n");
    gotoxy(X,Y+18); printf("                                                                              \n");
    gotoxy(X,Y+19); printf("                                                                              \n");
    gotoxy(X,Y+20); printf("                                                                              \n");
    Sleep(400);
    gotoxy(X,Y);    printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+1);  printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+2);  printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+3);  printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+4);  printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+5);  printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+6);  printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+7);  printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+8);  printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+9);  printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+10); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+11); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+12); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+13); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+14); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+15); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+16); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+17); printf("```Criador:``````''```````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+18); printf("```LUIZ CARLOS - Aka DANNIELE MARINI `````````````````````````````````````````\n");
    gotoxy(X,Y+19); printf("```'''''``````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+20); printf("``````````````````````````````````````````````````````````````````````````````\n");
    Sleep(100);
    gotoxy(X,Y);    printf("   888888ba                      dP                                           \n");
    gotoxy(X,Y+1);  printf("   88    `8b                     88                                           \n");
    gotoxy(X,Y+2);  printf("  a88aaaa8P' .d8888b. 88d8b.d8b. 88d888b. .d8888b. 88d888b.                   \n");
    gotoxy(X,Y+3);  printf("   88   `8b. 88'  `88 88'`88'`88 88'  `88 88ooood8 88'  `88                   \n");
    gotoxy(X,Y+4);  printf("   88    .88 88.  .88 88  88  88 88.  .88 88.  ... 88                         \n");
    gotoxy(X,Y+5);  printf("   88888888P `88888P' dP  dP  dP 88Y8888' `88888P' dP                         \n");
    gotoxy(X,Y+6);  printf("                                                                              \n");
    gotoxy(X,Y+7);  printf("                                         8888ba.88ba                          \n");
    gotoxy(X,Y+8);  printf("                                         88  `8b  `8b                         \n");
    gotoxy(X,Y+9);  printf("                                         88   88   88 .d8888b. 88d888b.       \n");
    gotoxy(X,Y+10); printf("                                         88   88   88 88'  `88 88'  `88       \n");
    gotoxy(X,Y+11); printf("                                         88   88   88 88.  .88 88    88       \n");
    gotoxy(X,Y+12); printf("                                         dP   dP   dP `88888P8 dP    dP       \n");
    gotoxy(X,Y+13); printf("                                                                              \n");
    gotoxy(X,Y+14); printf("                                                                              \n");
    gotoxy(X,Y+15); printf("                                                                              \n");
    gotoxy(X,Y+16); printf("                                                                              \n");
    gotoxy(X,Y+17); printf("                                                                              \n");
    gotoxy(X,Y+18); printf("                                                                              \n");
    gotoxy(X,Y+19); printf("                                                                              \n");
    gotoxy(X,Y+20); printf("                                                                              \n");
    Sleep(1000);

    gotoxy(X,Y);    printf("                           +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+1);  printf("       ###                 |B|o|m|b|e|r|  |M|a|n|                             \n");
    gotoxy(X,Y+2);  printf("      #///#                +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+3);  printf("     #######                                                                  \n");
    gotoxy(X,Y+4);  printf("    #       #                                                                 \n");
    gotoxy(X,Y+5);  printf("   #  ...... #                                                                \n");
    gotoxy(X,Y+6);  printf("   # .|....|.#                                                                \n");
    gotoxy(X,Y+7);  printf("   # .|....|.#                                                                \n");
    gotoxy(X,Y+8);  printf("   # .|....|.#                                                                \n");
    gotoxy(X,Y+9);  printf("    #       #                                                                 \n");
    gotoxy(X,Y+10); printf("   # ####### #                                                                \n");
    gotoxy(X,Y+11); printf("  # #       # #                                                               \n");
    gotoxy(X,Y+12); printf(" #  #xxX@Xxx#  #                                                              \n");
    gotoxy(X,Y+13); printf("#//#         #//#                                                             \n");
    gotoxy(X,Y+14); printf(" ###############                                                              \n");
    gotoxy(X,Y+15); printf("   #////##///#                                                                \n");
    gotoxy(X,Y+16); printf("  #/////##/////#                                                              \n");
    gotoxy(X,Y+17); printf("   ############                                                               \n");
    gotoxy(X,Y+18); printf("                                                                              \n");
    gotoxy(X,Y+19); printf("                                                                              \n");
    gotoxy(X,Y+20); printf("                                                                              \n");
    Sleep(500);
}

void menu(int X,int Y){ //printa menu
    gotoxy(X,Y);    printf("                           +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+1);  printf("       ###                 |B|o|m|b|e|r|  |M|a|n|                             \n");
    gotoxy(X,Y+2);  printf("      #///#                +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+3);  printf("     #######                                                                  \n");
    gotoxy(X,Y+4);  printf("    #       #                 +-+-+-+-+-+-+-+-+                               \n");
    gotoxy(X,Y+5);  printf("   #  ...... #                | Bem Vindo!!!! |                               \n");
    gotoxy(X,Y+6);  printf("   # .|....|.#                +               +                               \n");
    gotoxy(X,Y+7);  printf("   # .|....|.#                | Precione:     |                               \n");
    gotoxy(X,Y+8);  printf("   # .|....|.#                +               +                               \n");
    gotoxy(X,Y+9);  printf("    #       #                 | 1)- Novo Jogo |                               \n");
    gotoxy(X,Y+10); printf("   # ####### #                + 2)- Recorde   +                               \n");
    gotoxy(X,Y+11); printf("  # #       # #               |               |                               \n");
    gotoxy(X,Y+12); printf(" #  #xxX@Xxx#  #              +               +                               \n");
    gotoxy(X,Y+13); printf("#//#         #//#             |               |                               \n");
    gotoxy(X,Y+14); printf(" ###############              +               +                               \n");
    gotoxy(X,Y+15); printf("   #////##///#                |               |                               \n");
    gotoxy(X,Y+16); printf("  #/////##/////#              +               +                               \n");
    gotoxy(X,Y+17); printf("   ############               | e)- Sair      |                               \n");
    gotoxy(X,Y+18); printf("                              +-+-+-+-+-+-+-+-+                               \n");
    gotoxy(X,Y+19); printf("                                                                              \n");
    gotoxy(X,Y+20); printf("                                                                              \n");
}

void preparado(int X, int Y){ //cutscene 321 go
    textcolor (7);
    gotoxy(X,Y);    printf("```````````````````````````+-+-+-+-+-+-+-+`+-+-+``````````````````````````````\n");
    gotoxy(X,Y+1);  printf("``````````````````````````3|P|R|E|P|A|R|E|-|S|E|3`````````````````````````````\n");
    gotoxy(X,Y+2);  printf("```````````````````````````+-+-+-+-+-+-+-+`+-+-+``````````````````````````````\n");
    gotoxy(X,Y+3);  printf("```````````````````````````````````33333``````````````````````````````````````\n");
    gotoxy(X,Y+4);  printf("````````````````````````````33``````333``````33```````````````````````````````\n");
    gotoxy(X,Y+5);  printf("````````````````````````````33``````333``````33```````````````````````````````\n");
    gotoxy(X,Y+6);  printf("````````````````````````````33``````333``````33```````````````````````````````\n");
    gotoxy(X,Y+7);  printf("````````````````````````````33``````333``````33```````````````````````````````\n");
    gotoxy(X,Y+8);  printf("````````````````````````````33``````333``````33```````````````````````````````\n");
    gotoxy(X,Y+9);  printf("````````````````````````````33``````333``````33```````````````````````````````\n");
    gotoxy(X,Y+10); printf("````````````````````````````33``````333``````33```````````````````````````````\n");
    gotoxy(X,Y+11); printf("````````````````````````````33``````333``````33```````````````````````````````\n");
    gotoxy(X,Y+12); printf("````````````````````````````33``````333``````33```````````````````````````````\n");
    gotoxy(X,Y+13); printf("````````````````````````````33``````333``````33```````````````````````````````\n");
    gotoxy(X,Y+14); printf("```````````````````````````````````33333``````````````````````````````````````\n");
    gotoxy(X,Y+15); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+16); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+17); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+18); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+19); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+20); printf("``````````````````````````````````````````````````````````````````````````````\n");
    Sleep(500);
    gotoxy(X,Y);    printf("```````````````````````````+-+-+-+-+-+-+-+`+-+-+``````````````````````````````\n");
    gotoxy(X,Y+1);  printf("``````````````````````````2|P|R|E|P|A|R|E|-|S|E|2`````````````````````````````\n");
    gotoxy(X,Y+2);  printf("```````````````````````````+-+-+-+-+-+-+-+`+-+-+``````````````````````````````\n");
    gotoxy(X,Y+3);  printf("```````````````````````222```2222```222```2222```222``````````````````````````\n");
    gotoxy(X,Y+4);  printf("``````````````````````````````22```````````22`````````````````````````````````\n");
    gotoxy(X,Y+5);  printf("``````````````````````````````22```````````22`````````````````````````````````\n");
    gotoxy(X,Y+6);  printf("``````````````````````````````22```````````22`````````````````````````````````\n");
    gotoxy(X,Y+7);  printf("``````````````````````````````22```````````22`````````````````````````````````\n");
    gotoxy(X,Y+8);  printf("``````````````````````````````22```````````22`````````````````````````````````\n");
    gotoxy(X,Y+9);  printf("``````````````````````````````22```````````22`````````````````````````````````\n");
    gotoxy(X,Y+10); printf("``````````````````````````````22```````````22`````````````````````````````````\n");
    gotoxy(X,Y+11); printf("``````````````````````````````22```````````22`````````````````````````````````\n");
    gotoxy(X,Y+12); printf("``````````````````````````````22```````````22`````````````````````````````````\n");
    gotoxy(X,Y+13); printf("```````````````````````222```2222```222```2222```222``````````````````````````\n");
    gotoxy(X,Y+14); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+15); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+16); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+17); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+18); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+19); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+20); printf("``````````````````````````````````````````````````````````````````````````````\n");
    Sleep(500);
    gotoxy(X,Y);    printf("```````````````````````````+-+-+-+-+-+-+-+`+-+-+``````````````````````````````\n");
    gotoxy(X,Y+1);  printf("``````````````````````````1|P|R|E|P|A|R|E|-|S|E|1`````````````````````````````\n");
    gotoxy(X,Y+2);  printf("```````````````````````````+-+-+-+-+-+-+-+`+-+-+``````````````````````````````\n");
    gotoxy(X,Y+3);  printf("``````````````````````````````````1111111`````````````````````````````````````\n");
    gotoxy(X,Y+4);  printf("````````````````````````````````````111```````````````````````````````````````\n");
    gotoxy(X,Y+5);  printf("``````````````````````````````````1`111`1`````````````````````````````````````\n");
    gotoxy(X,Y+6);  printf("````````````````````````````````````111```````````````````````````````````````\n");
    gotoxy(X,Y+7);  printf("````````````````````````````````````111```````````````````````````````````````\n");
    gotoxy(X,Y+8);  printf("````````````````````````````````````111```````````````````````````````````````\n");
    gotoxy(X,Y+9);  printf("````````````````````````````````````111```````````````````````````````````````\n");
    gotoxy(X,Y+10); printf("````````````````````````````````````111```````````````````````````````````````\n");
    gotoxy(X,Y+11); printf("``````````````````````````````````1`111`1`````````````````````````````````````\n");
    gotoxy(X,Y+12); printf("````````````````````````````````````111```````````````````````````````````````\n");
    gotoxy(X,Y+13); printf("``````````````````````````````````1111111`````````````````````````````````````\n");
    gotoxy(X,Y+14); printf("````````````````````````````````1`````````1```````````````````````````````````\n");
    gotoxy(X,Y+15); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+16); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+17); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+18); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+19); printf("``````````````````````````````````````````````````````````````````````````````\n");
    gotoxy(X,Y+20); printf("``````````````````````````````````````````````````````````````````````````````\n");
    Sleep(500);
    gotoxy(X,Y);    printf("                           +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+1);  printf("       ###                 |B|o|m|b|e|r|  |M|a|n|                             \n");
    gotoxy(X,Y+2);  printf("      #///#                +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+3);  printf("     #######                                                                  \n");
    gotoxy(X,Y+4);  printf("    #       #                                                                 \n");
    gotoxy(X,Y+5);  printf("   #  ...... #                                                                \n");
    gotoxy(X,Y+6);  printf("   # .|....|.#                                                                \n");
    gotoxy(X,Y+7);  printf("   # .|....|.#                                                                \n");
    gotoxy(X,Y+8);  printf("   # .|....|.#                       GO!                                      \n");
    gotoxy(X,Y+9);  printf("    #       #                                                                 \n");
    gotoxy(X,Y+10); printf("   # ####### #                                                                \n");
    gotoxy(X,Y+11); printf("  # #       # #                                                               \n");
    gotoxy(X,Y+12); printf(" #  #xxX@Xxx#  #                                                              \n");
    gotoxy(X,Y+13); printf("#//#         #//#                                                             \n");
    gotoxy(X,Y+14); printf(" ###############                                                              \n");
    gotoxy(X,Y+15); printf("   #////##///#                                                                \n");
    gotoxy(X,Y+16); printf("  #/////##/////#                                                              \n");
    gotoxy(X,Y+17); printf("   ############                                                               \n");
    gotoxy(X,Y+18); printf("                                                                              \n");
    gotoxy(X,Y+19); printf("                                                                              \n");
    gotoxy(X,Y+20); printf("                                                                              \n");
    Sleep(200);
}

void lvlTela(int X,int Y){//printa lvl da tela
    textcolor (10);
    gotoxy(X,Y);    printf("                           +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+1);  printf("       ###                 |B|o|m|b|e|r|  |M|a|n|                             \n");
    gotoxy(X,Y+2);  printf("      #///#                +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+3);  printf("     #######                                                                  \n");
    gotoxy(X,Y+4);  printf("    #       #                                                                 \n");
    gotoxy(X,Y+5);  printf("   #  ...... #                                                                \n");
    gotoxy(X,Y+6);  printf("   # .|....|.#                                                                \n");
    gotoxy(X,Y+7);  printf("   # .|....|.#                                                                \n");
    gotoxy(X,Y+8);  printf("   # .|....|.#                       LVL - %d                                  \n",levelCur);
    gotoxy(X,Y+9);  printf("    #       #                                                                 \n");
    gotoxy(X,Y+10); printf("   # ####### #                                                                \n");
    gotoxy(X,Y+11); printf("  # #       # #                                                               \n");
    gotoxy(X,Y+12); printf(" #  #xxX@Xxx#  #                                                              \n");
    gotoxy(X,Y+13); printf("#//#         #//#                                                             \n");
    gotoxy(X,Y+14); printf(" ###############                                                              \n");
    gotoxy(X,Y+15); printf("   #////##///#                                                                \n");
    gotoxy(X,Y+16); printf("  #/////##/////#                                                              \n");
    gotoxy(X,Y+17); printf("   ############                                                               \n");
    gotoxy(X,Y+18); printf("                                                                              \n");
    gotoxy(X,Y+19); printf("                                                                              \n");
    gotoxy(X,Y+20); printf("                                                                              \n");
    Sleep(500);
}

void vitoria(int X,int Y){//printa vitoria
    textcolor (11);
    gotoxy(X,Y);    printf("                           +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+1);  printf("                           |B|o|m|b|e|r|  |M|a|n|                             \n");
    gotoxy(X,Y+2);  printf("                           +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+3);  printf("                                                                              \n");
    gotoxy(X,Y+4);  printf("                                                                              \n");
    gotoxy(X,Y+5);  printf("                               +-+-+-+-+-+-+-+                                \n");
    gotoxy(X,Y+6);  printf("                               |V|I|T|O|R|I|A|                                \n");
    gotoxy(X,Y+7);  printf("                               +-+-+-+-+-+-+-+                                \n");
    gotoxy(X,Y+8);  printf("                                                                              \n");
    gotoxy(X,Y+9);  printf("                                                                              \n");
    gotoxy(X,Y+10); printf("                                                                              \n");
    gotoxy(X,Y+11); printf("                                                                              \n");
    gotoxy(X,Y+12); printf("                                                                              \n");
    gotoxy(X,Y+13); printf("                                                                              \n");
    gotoxy(X,Y+14); printf("                                                                              \n");
    gotoxy(X,Y+15); printf("                                                                              \n");
    gotoxy(X,Y+16); printf("                                                                              \n");
    gotoxy(X,Y+17); printf("                                                                              \n");
    gotoxy(X,Y+18); printf("                                                                              \n");
    gotoxy(X,Y+19); printf("                                                                              \n");
    gotoxy(X,Y+20); printf("                                                                              \n");
    Sleep(3000);
}

void derrota(int X,int Y){//printa derrota
    textcolor (13);
    gotoxy(X,Y);    printf("                           +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+1);  printf("                           |B|o|m|b|e|r|  |M|a|n|                             \n");
    gotoxy(X,Y+2);  printf("                           +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+3);  printf("                                                                              \n");
    gotoxy(X,Y+4);  printf("                                                                              \n");
    gotoxy(X,Y+5);  printf("                               +-+-+-+-+-+-+-+                                \n");
    gotoxy(X,Y+6);  printf("                               |D|E|R|R|O|T|A|                                \n");
    gotoxy(X,Y+7);  printf("                               +-+-+-+-+-+-+-+                                \n");
    gotoxy(X,Y+8);  printf("                                                                              \n");
    gotoxy(X,Y+9);  printf("                                                                              \n");
    gotoxy(X,Y+10); printf("                                                                              \n");
    gotoxy(X,Y+11); printf("                                                                              \n");
    gotoxy(X,Y+12); printf("                                                                              \n");
    gotoxy(X,Y+13); printf("                                                                              \n");
    gotoxy(X,Y+14); printf("                                                                              \n");
    gotoxy(X,Y+15); printf("                                                                              \n");
    gotoxy(X,Y+16); printf("                                                                              \n");
    gotoxy(X,Y+17); printf("                                                                              \n");
    gotoxy(X,Y+18); printf("                                                                              \n");
    gotoxy(X,Y+19); printf("                                                                              \n");
    gotoxy(X,Y+20); printf("                                                                              \n");
    Sleep(3000);
}

void dRecord(int X,int Y,int cRec,char* nomeRecod,int* record){//printa Record
    gotoxy(X,Y);    printf("                           +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+1);  printf("                           |B|o|m|b|e|r|  |M|a|n|                             \n");
    gotoxy(X,Y+2);  printf("                           +-+-+-+-+-+-+  +-+-+-+                             \n");
    gotoxy(X,Y+3);  printf("                               +-+-+-+-+-+-+                                  \n");
    gotoxy(X,Y+4);  printf("                               |R|E|C|O|R|D|                                  \n");
    gotoxy(X,Y+5);  printf("                               +-+-+-+-+-+-+                                  \n");
    gotoxy(X,Y+6);  printf("                           Nome             Pontuacao                         \n");
    gotoxy(X,Y+7);  printf("                            %c                 %d                  \n",nomeRecod[cRec],record[cRec]);
    gotoxy(X,Y+8);  printf("                            %c                 %d                  \n",nomeRecod[cRec-1],record[cRec-1]);
    gotoxy(X,Y+9);  printf("                            %c                 %d                  \n",nomeRecod[cRec-2],record[cRec-2]);
    gotoxy(X,Y+10); printf("                            %c                 %d                  \n",nomeRecod[cRec-3],record[cRec-3]);
    gotoxy(X,Y+11); printf("                            %c                 %d                  \n",nomeRecod[cRec-4],record[cRec-4]);
    gotoxy(X,Y+12); printf("                            %c                 %d                  \n",nomeRecod[cRec-5],record[cRec-5]);
    gotoxy(X,Y+13); printf("                            %c                 %d                  \n",nomeRecod[cRec-6],record[cRec-6]);
    gotoxy(X,Y+14); printf("                            %c                 %d                  \n",nomeRecod[cRec-7],record[cRec-7]);
    gotoxy(X,Y+15); printf("                            %c                 %d                  \n",nomeRecod[cRec-8],record[cRec-8]);
    gotoxy(X,Y+16); printf("                            %c                 %d                  \n",nomeRecod[cRec-9],record[cRec-9]);
    gotoxy(X,Y+17); printf("                                                                              \n");
    gotoxy(X,Y+18); printf("                                                                              \n");
    gotoxy(X,Y+19); printf("                                                                              \n");
    gotoxy(X,Y+20); printf("                                                                              \n");
    Sleep(3000);
}

//---------------------------------------------------------------------//

//copy mapa
void copymap(char copianome[13][16],char nome[13][16]){
    int x, y;
    textcolor (4);
    for(x=0 ; x<13 ; x++){
         for(y=0 ; y<16 ; y++){
            copianome[x][y] = nome[x][y];
        }
    }
}

//Randomizar Caixas
void randomizarCaixa(int qntd){
    int Ry,Rx, x;
    for(x=1;x<=qntd; ){
        Rx = rand()%15;
        Ry = rand()%13;
        if (tabuleiro[Ry][Rx] == ' '){
            if (Ry!=3 || Rx != 3){
            tabuleiro[Ry][Rx] = 'c';
            x++;
            }
        }
    }
    tabuleiro[2][1] = ' ';
    tabuleiro[1][2] = ' ';
}

//Mecanica Morte
void mecanicaDeath(int Y,int X){
    int x;
    for(x=1;x<=qua;x++){
        if(((mon[x-1].pX == pXb) && (mon[x-1].pY == pYb) && (mon[x-1].vida > 0)) || tabuleiro[Y][X]=='x'){
            flagD=1;//Perde
            vit=100;//para sair do loop de level
        }
    }
}

//Randomizar Monstros
void randomizarMonstros(){
    int Ry,Rx, x;
    for(x=1;x<=qua; ){
        Rx = rand()%15;
        Ry = rand()%13;
        if (tabuleiro[Ry][Rx] == ' ' && Rx >4 && Ry >4){
            tabuleiro[Ry][Rx] = 'M';
            mon[x-1].pX = Rx;
            mon[x-1].pY = Ry;
            mon[x-1].vida =1;
            x++;
        }
    }
}


//Gerador de mapa(nivel, mapa)
void gerMapa(char mapa[13][16]){
    char runMap[13][16]=
        {{'p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','w'},
         {'p','b',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','p','w'},
         {'p',' ','p',' ','p',' ','p',' ','p',' ','p',' ','p',' ','p','w'},
         {'p',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','p','w'},
         {'p',' ','p',' ','p',' ','p',' ','p',' ','p',' ','p',' ','p','w'},
         {'p',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','p','w'},
         {'p',' ','p',' ','p',' ','p',' ','p',' ','p',' ','p',' ','p','w'},
         {'p',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','p','w'},
         {'p',' ','p',' ','p',' ','p',' ','p',' ','p',' ','p',' ','p','w'},
         {'p',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','p','w'},
         {'p',' ','p',' ','p',' ','p',' ','p',' ','p',' ','p',' ','p','w'},
         {'p',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','p','w'},
         {'p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','w'}};
    pXb = 1;
    pYb = 1;
    //gotoxy(2,1); printf("x=%d y=%d",pXb, pYb);//t2
    copymap(tabuleiro,runMap);
    //gotoxy(2,2); printf("x=%d y=%d",pXb, pYb);//t1
}


//Visualizar mapaprintf(mapa,cordenadaX,cordenadaY)
void verMapaPr(char map[13][16],int x,int y){
    int l,c;
    for(l=0;l<13;l++,y++){
        gotoxy(x,y);
        for(c=0;c<15;c++){
                if (map[l][c] == 'b')
                    textcolor (11);
                  else
                    if (map[l][c] == 'c')
                        textcolor (8);
                    else
                    if (map[l][c] == 'M')
                        textcolor (7);
                    else
                    if (map[l][c] == 'x')
                        textcolor (12);
                    else
                    if (map[l][c] == 'h')
                        textcolor (14);
                    else
                        textcolor (2);
                printf("%c", map[l][c]);

        }
    }
}


//mecanica e movimentacao {teclas a = 97 w = 119 s = 116 d = 100 space = 32)
void mecanica(char map[13][16], int tempo){
    int x,y;
    int mov = ' ';
    mov = getch();
    switch(mov){
        case 100:{//direita
            gotoxy(36,19); printf(" direita ");
            if (tabuleiro[pYb][pXb+1]==' ' || tabuleiro[pYb][pXb+1]=='M'){
                if(tabuleiro[pYb][pXb]=='b') //Para nao apagar a BOMBA
                    tabuleiro[pYb][pXb]=' ';
                pXb += 1;
                tabuleiro[pYb][pXb]='b';
                //gotoxy(6,6); printf("moveu %c pxb=%d pyb=%d",tabuleiro[pYb][pXb], pXb, pYb);//teste
            }
            break;}
        case 119:{//cima
            gotoxy(36,19); printf("  cima  ");
            if (tabuleiro[pYb-1][pXb]==' ' || tabuleiro[pYb-1][pXb]=='M'){
                if(tabuleiro[pYb][pXb]=='b')
                    tabuleiro[pYb][pXb]=' ';
                pYb -= 1;
                tabuleiro[pYb][pXb]='b';
                //gotoxy(6,6); printf("moveu %c pxb=%d pyb=%d",tabuleiro[pYb][pXb], pXb, pYb);//teste
            }
            break;}
        case 97:{//esquerda
            gotoxy(36,19); printf(" esquerda ");
            if (tabuleiro[pYb][pXb-1]==' ' || tabuleiro[pYb][pXb-1]=='M'){
                if(tabuleiro[pYb][pXb]=='b')
                    tabuleiro[pYb][pXb]=' ';
                pXb -= 1;
                tabuleiro[pYb][pXb]='b';
                //gotoxy(6,6); printf("moveu %c pxb=%d pyb=%d",tabuleiro[pYb][pXb], pXb, pYb);//teste
            }
            break;}
        case 115:{//baixo
            gotoxy(36,19); printf("  baixo  ");
            if (tabuleiro[pYb+1][pXb]==' '|| tabuleiro[pYb+1][pXb]=='M'){
                if(tabuleiro[pYb][pXb]=='b')
                    tabuleiro[pYb][pXb]=' ';
                pYb += 1;
                tabuleiro[pYb][pXb]='b';
                //gotoxy(6,6); printf("moveu %c pxb=%d pyb=%d",tabuleiro[pYb][pXb], pXb, pYb);//teste
            }
            break;}
        case 32:{//bomba
            gotoxy(36,19); printf("  BoMbA  "); //Bomba fica embaixo do bomberman, substitui h no mapa mas printa F, ao se mover printa b
            if (tabuleiro[pYb][pXb]=='b' && flagB ==0){
                tabuleiro[pYb][pXb]='h';
                flagB = 1;
                tempoB=0;
                yBomba=pYb;
                xBomba=pXb;
                //gotoxy(6,6); printf("Bomba %c pxb=%d pyb=%d",tabuleiro[pYb][pXb], pXb, pYb);//teste
            }
            break;}
        default:{
            break;}
    }
}

//Vitoria e morte dos monstros
void vitMmor(){
    int x;
    if (vit == qua){
        flagD=1;
    }
    for(x=1;x<=qua;){
        if (mon[x-1].vida > 0){
            if (tabuleiro[mon[x-1].pY][mon[x-1].pX]== 'x'){
                mon[x-1].vida = 0;
                vit += 1;
                pontuacao += 5000;
            }
        }
    x++;
    }
}

//Mecanica Movimentacao do monstro
void mecanicaMon(){
    int x,esc;
    for(x=1;x<=qua;){
        if (mon[x-1].vida >= 0){
            if (tabuleiro[mon[x-1].pY][mon[x-1].pX]== 'x')
                mon[x-1].vida = 0;
        }
        if (mon[x-1].vida > 0){
            if (pXb > mon[x-1].pX){
                if (tabuleiro[mon[x-1].pY][mon[x-1].pX+1]==' ' || tabuleiro[mon[x-1].pY][mon[x-1].pX+1]=='b'){
                    tabuleiro[mon[x-1].pY][mon[x-1].pX]=' ';
                    mon[x-1].pX += 1;
                    tabuleiro[mon[x-1].pY][mon[x-1].pX]='M';
                }
            }else{
                if (pXb < mon[x-1].pX){
                    if (tabuleiro[mon[x-1].pY][mon[x-1].pX-1]==' ' || tabuleiro[mon[x-1].pY][mon[x-1].pX-1]=='b'){
                        tabuleiro[mon[x-1].pY][mon[x-1].pX]=' ';
                        mon[x-1].pX -= 1;
                        tabuleiro[mon[x-1].pY][mon[x-1].pX]='M';
                    }
                }else{
                    if (pYb < mon[x-1].pY){
                            if (tabuleiro[mon[x-1].pY-1][mon[x-1].pX]==' ' || tabuleiro[mon[x-1].pY-1][mon[x-1].pX]=='b'){
                                tabuleiro[mon[x-1].pY][mon[x-1].pX]=' ';
                                mon[x-1].pY -= 1;
                                tabuleiro[mon[x-1].pY][mon[x-1].pX]='M';
                            }
                    }else{
                        if (pYb > mon[x-1].pY){
                            if (tabuleiro[mon[x-1].pY+1][mon[x-1].pX]==' ' || tabuleiro[mon[x-1].pY+1][mon[x-1].pX]=='b'){
                                tabuleiro[mon[x-1].pY][mon[x-1].pX]=' ';
                                mon[x-1].pY += 1;
                                tabuleiro[mon[x-1].pY][mon[x-1].pX]='M';
                            }
                        }else{//cima aleatorio
                                if (tabuleiro[mon[x-1].pY+1][mon[x-1].pX]==' '){
                                    tabuleiro[mon[x-1].pY][mon[x-1].pX]=' ';
                                    mon[x-1].pY += 1;
                                    tabuleiro[mon[x-1].pY][mon[x-1].pX]='M';
                                }else{//baixo aleatorio
                                    if (tabuleiro[mon[x-1].pY-1][mon[x-1].pX]==' '){
                                        tabuleiro[mon[x-1].pY][mon[x-1].pX]=' ';
                                        mon[x-1].pY -= 1;
                                        tabuleiro[mon[x-1].pY][mon[x-1].pX]='M';
                                    }
                                }
                        }
                    }
                }
            }
        }
    x++;
    }

}

//Bomba explosao
void bombamecanica(){
    int y, x;
    if(flagB == 1){                                 //bomba-Explosao
        tempoB++;
        if(tempoB == 100){
            tabuleiro[yBomba][xBomba]='x';
            if(tabuleiro[yBomba][xBomba+1] != 'p')
                tabuleiro[yBomba][xBomba+1]='x';
            if(tabuleiro[yBomba][xBomba-1] != 'p')
                tabuleiro[yBomba][xBomba-1]='x';
            if(tabuleiro[yBomba+1][xBomba] != 'p')
                tabuleiro[yBomba+1][xBomba]='x';
            if(tabuleiro[yBomba-1][xBomba] != 'p')
                tabuleiro[yBomba-1][xBomba]='x';
            flagB = 0;
            tempoB= 0;
            flagX= 1;
        }
    }
    if(flagX == 1){
        tempoX++;
        if(tempoX == 30){
            for(x=0 ; x<13 ; x++){
                for(y=0 ; y<16 ; y++){
                    if (tabuleiro[x][y] == 'x'){
                        tabuleiro[x][y] = ' ';
                        flagX=0;
                        tempoX=0;
                    }
                }
            }
        }
    }
}

//Main
void main(){
    int perso,c=0, quadro=0, sairflag =0, record[15],nomeRecod[15][15],cRec=0;
    char escolha;
    todosCantos();
    introducao(2,2);
    do{
        menu(2,2);
        scanf("%c", &escolha);
        todosCantos();
        switch(escolha){
            case '1':{//Novo Jogo
                if (levelCur==1){
                    lvlTela(2,2);
                    preparado(2,2);
                    gerMapa(tabuleiro);
                    randomizarCaixa(LEVEL1);
                    qua = 3;
                    vit =0;//condição de vitoria
                    randomizarMonstros();
                    //gotoxy(2,3); printf("x=%d y=%d",pXb, pYb);
                    //verMapaPr(tabuleiro,33 ,6);
                    do{
                        pontuacao = pontuacao - 10;
                        verMapaPr(tabuleiro,33 ,7);
                        if(kbhit()){
                            mecanica(tabuleiro,quadro);
                        }
                        vitMmor();
                        if (delaymMon>=30){
                            mecanicaMon();
                            delaymMon=0;
                        }
                        delaymMon += 1;
                        mecanicaDeath(pYb,pXb);
                        //gotoxy(2,18); printf("quadro= %d tempoB = %d tempoX = %d,/n flagB = %d, flagD = %d, flagX = %d,/n DelayMon= %d  ", quadro, tempoB, tempoX, flagB, flagD, flagX, delaymMon); //Teste de quadro e tempo da bomba
                        //gotoxy(1,5); printf("mon[0].pX= %d mon[0].pY= %d \nmon[1].pX= %d mon[1].pY= %d\nmon[2].pX= %d mon[2].pY= %d",mon[0].pX,mon[0].pY,mon[1].pX,mon[1].pY,mon[2].pX,mon[2].pY);
                        //gotoxy(48,19); printf("y=%d x=%d quadro=",pYb,pXb);
                        //gotoxy(48,19); printf("qua=%d vit=%d",qua,vit);
                        bombamecanica();
                        if (vit==qua){
                            levelCur=2;
                            pontuacao += 15000;
                        }
                    }while(flagD!=1);
                }
                if (levelCur==2)    //limpar variaveis
                    tempoX=0;
                    tempoB=0;
                    flagD=0;
                    flagX=0;
                if (levelCur==2){
                    lvlTela(2,2);
                    preparado(2,2);
                    gerMapa(tabuleiro);
                    randomizarCaixa(LEVEL2);
                    qua = 5;
                    vit =0;//condição de vitoria
                    randomizarMonstros();
                    do{
                        pontuacao = pontuacao - 20;
                        verMapaPr(tabuleiro,33 ,7);
                        if(kbhit()){
                            mecanica(tabuleiro,quadro);
                        }
                        vitMmor();
                        if (delaymMon>=50){
                            mecanicaMon();
                            delaymMon=0;
                        }
                        delaymMon += 1;
                        mecanicaDeath(pYb,pXb);
                        bombamecanica();
                        if (vit==qua){
                            levelCur=3;
                            pontuacao += 15000;
                        }
                    }while(flagD!=1);
                }
                if(vit==qua){
                    vitoria(2,2);//cutscene
                }
                if(vit!=qua){
                    derrota(2,2);//cutscene
                }
            scanf("%s", &nomeRecod[cRec]);
            record[cRec] = pontuacao;
            cRec += 1;
            break;
            }
            case '2':{//recorde
            dRecord(2,2,cRec,nomeRecod,record);
            break;
            }
            case 'e':{//Sair
                sairflag=1;
            break;
            }
        }
    }while(sairflag!=1);

}



//nota.3 - Editando movimento do monstro
//nota.2 - Criação do monstro e struct do monstro
//nota.1 - Criação da mecanica, mapa e movimento. ultima edição: Bomba
