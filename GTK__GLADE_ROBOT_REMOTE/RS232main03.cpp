// read a file into memory
#include <windows.h>
#include <winbase.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "rs232api2.h"

using namespace std;

int EnviaString( string str );

int main () {
  char c;
  char *teste = "teste";
  unsigned char buffer[60000];
  int tamanhoarq;

  string name;
  ifstream is;

  inicializa_serial(COM1, 8, ONESTOPBIT, NOPARITY, 9600, 100);

  cout << "SINAL RECEBIDO:..." << endl;
  while (!kbhit())
  if (recebe_caracter_serial(&c))
  {
      buffer[tamanhoarq]=c;
      tamanhoarq++;
      if (tamanhoarq==(tamanhoarq&0xFFFC00))
      printf("\r%d bytes transferidos  ", tamanhoarq);

  }




  is.open ("DATA01.txt", ios::binary );

  while (is.good())     // loop while extraction from file is possible
  {
    c = is.get();       // get character from file
        if  (is.eof()==true)
        {
        name+=c;
        EnviaString( name );
        }
            if  (c!=10)
            name+=c;
            else
            {
            name+=c;
            EnviaString( name );
            name="";
            }
    }
  is.close();
  libera_serial();
  system("PAUSE");
  return 0;
}

int EnviaString( string str )
{
  int i;
  string temp;
  string::iterator it;
  temp = str;
for ( i = 0 ; i < str.size() ; i++)
{
//    cout <<"[temp] = " << temp;
  char *buffer = new char[temp.length()+1];
  strcpy(buffer, temp.c_str());
    envia_caracter_serial(buffer);
    it=temp.begin();
    temp.erase (it);
}
return 0;
}





//#include "windows.h"
//#include "conio.h"
//#include "stdio.h"
//
//
//
//struct time {
//  unsigned char  ti_min;   /* minutos */
//  unsigned char  ti_hour;  /* horas */
//  unsigned char  ti_hund;  /* centésimos de segundos */
//  unsigned char  ti_sec;   /* seconds */
//
//};
//
//struct date {
//  int da_year;     /* Ano corrente */
//  char da_day;     /* Dia do mês */
//  char da_mon;     /* Mês (1 = Jan.) */
//};
//
//void main (void)
//{
//struct time tempo;
//struct date data;
//
//int c=1;
//int i = 0;
//
//    do
//    {
//printf("i = %d  \n Pressione uma tecla:",i);
//if (c==1) printf("Nenhuma Tecla Pressionada");
//
//i++;
//Sleep(300);
//    }
//    while ( !kbhit() );
//    c=getch();
//    system("pause");
//    printf("Voce Pressionou %d",c);
//}
//


