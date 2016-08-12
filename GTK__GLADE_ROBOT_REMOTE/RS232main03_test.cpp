// read a file into memory
#include <windows.h>
#include <winbase.h>
#include <iostream>
#include <fstream>
#include <string>

#include "rs232api2.h"

using namespace std;

int EnviaString( string str );

int main () {

  int PORTA;
  int DATABITS;
  BYTE PARADA;
  BYTE PARIDADE;
  int TAXA;
  int TIMEOUT;

  const int MAX=80;
  char buff[MAX];

ifstream fin("RS232.conf");   // Abre arquivo para leitura
                                //em modo texto
//while(fin)                      // Enquanto n�o for fim de arquivo
 fin.getline(buff, MAX);       // L� qual porta COM ser� aberta
 PORTA=(int)buff;
 cout << "PORTA:............................" << buff << '\n';
 DATABITS=(int)buff;
 fin.getline(buff, MAX);       // L� a configura��o dos Bits de DADOS
 cout << "Bits de DADOS:...................." << buff << '\n';
 PARADA= new PARADA(buff.length());
 PARADA=(BYTE)buff;
 fin.getline(buff, MAX);       // L� a configura��o dos Bits de PARADA
 cout << "Configuracao de PARADA:..........." << buff << '\n';
 PARIDADE=buff;
 fin.getline(buff, MAX);       // L� a configura��o de PARIDADE
 cout << "Configuracao de PARIDADE:........." << buff << '\n';
 TAXA=(int)buff;
 fin.getline(buff, MAX);       // L� a configura��o da Taxa BaudRate (de transmiss�o)
 cout << "TAXA de TRANSMISSAO (BaudRate):..." << buff << '\n';
 TIMEOUT=(int)buff;
 fin.getline(buff, MAX);       // L� a configura��o do TIMEOUT
 cout << "TIMEOUT:.........................." << buff << '\n';
 TIMOUT=(int)buff;

//}         // Exibe no v�deo

  system("PAUSE");
  return 0;
}

