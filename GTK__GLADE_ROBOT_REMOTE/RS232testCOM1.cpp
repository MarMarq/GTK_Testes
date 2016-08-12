// read a file into memory
#include <windows.h>
#include <winbase.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "rs232api2.h"

using namespace std;

void startup();
bool recebeRS232();
void enviaRS232(int i);
int EnviaString( string str );

int main () {

  char c;
  int i=0;
  bool test;
  char *teste = "teste";
  unsigned char buffer[60000];
  int tamanhoarq=0;
  string name;
  ifstream is;

  inicializa_serial(COM1, 8, ONESTOPBIT, NOPARITY, 9600, 100);

  cout << "START UP................................" << endl;

  startup();

do
{
while ( !kbhit() );
i=getch();
{
if (i==27) break;

cout << endl << "VALOR de i = " << i << endl;
enviaRS232(i);
startup();
}
}
while (i!=27);

  libera_serial();
  system("PAUSE");
  return 0;
}

void startup()
{
  char c;
  unsigned char buffer[60000];
  int tamanhoarq=0;

  cout << endl << "TESTANDO ENVIO DE SINAL ROBO --> PC:...." << endl;
  while (!kbhit())
  if (recebe_caracter_serial(&c))
  {
      buffer[tamanhoarq]=c;
      tamanhoarq++;
      if (tamanhoarq==(tamanhoarq&0xFFFC00))
      printf("\r %d DADOS transferidos ROBO --> PC:\n\n %s", tamanhoarq,buffer);
      printf("\nBytes Transmitidos = %d Bytes\n",tamanhoarq);
   }
   else
  {
    printf(("\nNENHUM DADO TRANSFERIDO ROBO --> PC.."));
  }
}

bool recebeRS232()
{
  char c;
  unsigned char buffer[60000];
  int tamanhoarq=0;

  cout << endl << "TESTANDO ENVIO DE SINAL ROBO --> PC:...." << endl;
//  while (!kbhit())
  if (recebe_caracter_serial(&c))
  {
      buffer[tamanhoarq]=c;
      tamanhoarq++;
      if (tamanhoarq==(tamanhoarq&0xFFFC00))
      printf("\r %d DADOS transferidos ROBO --> PC:\n\n %s", tamanhoarq,buffer);
      printf("\nBytes Transmitidos = %d Bytes\n",tamanhoarq);
      return true;
  }
   else
  {
    printf(("\nNENHUM DADO TRANSFERIDO!!\n"));
    return false;
  }
}

void enviaRS232(int i)
{
  char c;
  string name;
  c = (char)i;

 //   while ( !kbhit() );
//    c=getch();
    name="";
    name.append(1,c);
    name.append(1,'\n');
    //printf("\nTESTANDO ENVIO DE SINAL PC --> ROBO:.... ENVIANDO [%c] = %d \n",c,c);
    cout << "\nTESTANDO ENVIO DE SINAL PC --> ROBO:.... ENVIANDO ["<< name[0] << "] = " << (int)c<< endl;

    EnviaString(name );
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


