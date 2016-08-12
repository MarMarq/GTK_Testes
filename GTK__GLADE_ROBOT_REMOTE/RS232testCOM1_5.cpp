
#include "rs232W_fn01.h"
#include "file_manip01.h"
#include "RoboPC_Lnk01.h"
#include "rs232_cfg01.h"

#include <curses.h>

#define PAR1 1
#define PAR2 2
#define PAR3 3
#define PAR4 4
#define PAR5 5
#define PAR6 6
#define PAR7 7
#define PAR8 8
#define PAR9 9

/*
#define COLOR_BLACK   0
# define COLOR_RED    1
# define COLOR_GREEN  2
# define COLOR_BLUE   4
#define COLOR_CYAN    (COLOR_BLUE | COLOR_GREEN)
#define COLOR_MAGENTA (COLOR_RED | COLOR_BLUE)
#define COLOR_YELLOW  (COLOR_RED | COLOR_GREEN)
#define COLOR_WHITE   7
*/
bool   InterageRS232();
bool   VisualizaRecepcaoR2S32();
void sobre();

using namespace std;

int main () {

  int op,op2;
  vector <string> RS232Conf;
  string buffSUCESSO;
  string buffPORTA;
  string buffDATABITS;
  string buffSTOPBIT;
  string buffPAR;
  string buffTAXA;
  string buffTIMEOUT;
  string str;
  str="RS232.conf";



while(op)
{
        RS232Conf=LeRS232Conf( str );
     if (RS232Conf[6]=="false")
     printw(   "\nVerifique o arquivo RS232.conf e reinicie a PORTA novamente.\n\n" );

buffPORTA    =RS232Conf[0];
buffDATABITS =RS232Conf[1];
buffSTOPBIT  =RS232Conf[2];
buffPAR      =RS232Conf[3];
buffTAXA     =RS232Conf[4];
buffTIMEOUT  =RS232Conf[5];

        initscr();			/* Start curses mode 		*/
        resize_term(75 , 100);

        raw();				/* Line buffering disabled	*/
        keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
        noecho();			/* Don't echo() while we do getch */
        start_color();                  /* Start color                  */
        attron(A_BOLD);
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_WHITE, COLOR_BLACK);
        init_pair(5, COLOR_RED, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);

  attroff(COLOR_PAIR(5));
  attron(COLOR_PAIR(1));
  clear();
  printw( "Configuracoes atuais" );
  printw( "\n\nPORTA:............................%s",   buffPORTA.c_str()       );
  printw( "\nBits de DADOS:....................%s",     buffDATABITS.c_str()    );
  printw( "\nConfiguracao de PARADA:...........%s",     buffSTOPBIT.c_str()     );
  printw( "\nConfiguracao de PARIDADE:.........%s",     buffPAR.c_str()         );
  printw( "\nTAXA de TRANSMISSAO (BaudRate):...%s",     buffTAXA.c_str()        );
  printw( "\nTIMEOUT:..........................%s",     buffTIMEOUT.c_str()     );

  printw( "\n\n|----------------------------------------------| " );
  printw(   "\n| -- Comunica RS232 ---- Versao 1.0 (rev03) -- |" );
  printw(   "\n|----------------------------------------------|" );
  printw(   "\n| Digite a opcao abaixo:                       |" );
  printw(   "\n|----------------------------------------------|" );
  printw(   "\n| Interagir/Realizar testes via RS232 ---[1]   |" );
  printw(   "\n| Configurar/Rever Interface RS232 ------[2]   |" );
  printw(   "\n| Abrir um Link de DADOS PC <-> ROBO ----[3]   |" );
  printw(   "\n| Sobre este Programa -------------------[4]   |" );
  printw(   "\n| Sair do Programa ----------------------[5]   |" );
  printw(   "\n|----------------------------------------------|" );
  attroff(COLOR_PAIR(1));
  op=getch();

  switch (op){
  case '1':
  attron(COLOR_PAIR(5));
  printw( "\nVoce TECLOU [1]\n" );
  attron(A_REVERSE);
  printw( "\nFUNCAO EM FASE DE TESTE!!" );
  printw( "\n<PRESSIONE QUALQUER TECLA PARA CONTINUAR>");
  attroff(A_REVERSE);
  InterageRS232();
  break;

  case '2':
  printw( "\nVoce TECLOU [2]\n" );
  attron(COLOR_PAIR(5));
  attron(A_REVERSE);
  printw( "\nFUNCAO AINDA EM IMPLEMENTACAO!!");
  printw( "\n<PRESSIONE QUALQUER TECLA PARA CONTINUAR>");
  attroff(A_REVERSE);
  attroff(COLOR_PAIR(5));
  attron(COLOR_PAIR(1));
      getch();
  RS232Conf=RS232UserConfig(RS232Conf);
  break;

  case '3':
  printw( "\nVoce TECLOU [3]\n" );
  attron(COLOR_PAIR(5));
  attron(A_REVERSE);
  printw( "\nFUNCAO EM FASE DE TESTE!!" );
  printw( "\n<PRESSIONE QUALQUER TECLA PARA CONTINUAR>");
  attroff(A_REVERSE);
  attroff(COLOR_PAIR(5));
  attron(COLOR_PAIR(1));
      getch();
  DataLink();
  break;

  case '4':
  clear();
  refresh();
  sobre();
  break;

  case '5':
  attron(COLOR_PAIR(5));
  printw( "\nVoce TECLOU [6]\n" );
  printw( "\nDeseja realmente SAIR do programa? Tecle 'S' ou 's'");
      op2=getch();
  switch (op2){
  case 'S':
  libera_serial();
  return 1;
  libera_serial();
  case 's':
  return 1;
  case 'N':
  break;
  case 'n':
  break;
  }
  }
}
  return 0;
}

bool InterageRS232()
{
  int op;
  bool rv = false;
  do{
  attroff(COLOR_PAIR(5));
  attron(COLOR_PAIR(2));
  clear();
  printw( "\n\n|----------------------------------------------| " );
  printw(   "\n| ------------ Interagir via RS232 ----------- |" );
  printw(   "\n|----------------------------------------------|" );
  printw(   "\n| Digite a opcao abaixo:                       |" );
  printw(   "\n|----------------------------------------------|" );
  printw(   "\n| Visualizar Recepcao (Rx)  [ASCII] -----[1]   |" );
  printw(   "\n| Enviar um Arquivo via RS232 -----------[2]   |" );
  printw(   "\n| Enviar uma STRING via RS232 -----------[3]   |" );
  printw(   "\n| Voltar ao Menu Anterior ---------------[4]   |" );
  printw(   "\n|----------------------------------------------|" );
  attroff(COLOR_PAIR(2));
      op=getch();
        switch (op)
        {
        case '1':
        VisualizaRecepcaoR2S32();
        break;

        case '2':
        EnviaArquivo();
        break;

        case '3':
        EnviaStringRS232Interface();
        break;

        case '4':
        //Volta ao MENU Anterior
        rv = true;
        }
   }while (rv == false);
        return true;
}

bool VisualizaRecepcaoR2S32()
{ int op;
  bool rv = false;
  do{
  attroff(COLOR_PAIR(2));
  attron(COLOR_PAIR(3));
  clear();
  printw( "\n\n|----------------------------------------------| " );
  printw(   "\n| ----- Visualizar Recepcao (Rx) [ASCII] ----- |" );
  printw(   "\n|----------------------------------------------|" );
  printw(   "\n| Digite a opcao abaixo:                       |" );
  printw(   "\n|----------------------------------------------|" );
  printw(   "\n| Visualizacao Extratificada -------------[1]  |" );
  printw(   "\n| Visualizacao em Frases -----------------[2]  |" );
  printw(   "\n| Voltar ao Menu Anterior ----------------[3]  |" );
  printw(   "\n|----------------------------------------------|" );
  attroff(COLOR_PAIR(3));
      op=getch();
      switch (op)
      {
          case '1':
          VisualizaRX_Extratificada();
          break;

          case '2':
          VisualizaRX_Frases();
          break;

          case '3':
          //Volta ao MENU Anterior
          rv = true;
          break;
      }
   }while (rv == false);
return true;
}

void sobre()
{
    clear();
	WINDOW *instruct;
	int wmline=5,wmcol=2; 	//coordenadas em relação ao terminal (GLOBAIS)
	int mline=0,mcol=0;	//coordenadas em relação a janela instruct (LOCAIS)
	int wlargura=40,waltura=9;

	instruct =newwin(waltura,wlargura,wmline,wmcol);
	wbkgd(instruct,COLOR_PAIR(PAR4));
	wattron(instruct,A_BOLD);
	wattrset(instruct,COLOR_PAIR(PAR2));
	box(instruct,ACS_VLINE,ACS_HLINE);
	mvwprintw(instruct,mline,mcol+1,"SOBRE ESTE PROGRAMA:");

	wattrset(instruct,COLOR_PAIR(PAR5));
	mvwprintw(instruct,mline+2,mcol+2,"Comunica RS232 -- Versao 1.0 (rev03)");
	mvwprintw(instruct,mline+3,mcol+2,"Desenvolvido por Marcio H D Marques");
 	mvwprintw(instruct,mline+4,mcol+(20-6),"Maio de 2011");
	wattron(instruct,A_BLINK);
	mvwprintw(instruct,mline+6,mcol+(20-13),"<TECLE ALGO PARA RETORNAR>");
	wgetch(instruct);
	wrefresh(instruct);
}

