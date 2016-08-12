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
//while(fin)                      // Enquanto não for fim de arquivo
 fin.getline(buff, MAX);       // Lê qual porta COM será aberta
 PORTA=(int)buff;
 cout << "PORTA:............................" << buff << '\n';
 DATABITS=(int)buff;
 fin.getline(buff, MAX);       // Lê a configuração dos Bits de DADOS
 cout << "Bits de DADOS:...................." << buff << '\n';
 PARADA= new PARADA(buff.length());
 PARADA=(BYTE)buff;
 fin.getline(buff, MAX);       // Lê a configuração dos Bits de PARADA
 cout << "Configuracao de PARADA:..........." << buff << '\n';
 PARIDADE=buff;
 fin.getline(buff, MAX);       // Lê a configuração de PARIDADE
 cout << "Configuracao de PARIDADE:........." << buff << '\n';
 TAXA=(int)buff;
 fin.getline(buff, MAX);       // Lê a configuração da Taxa BaudRate (de transmissão)
 cout << "TAXA de TRANSMISSAO (BaudRate):..." << buff << '\n';
 TIMEOUT=(int)buff;
 fin.getline(buff, MAX);       // Lê a configuração do TIMEOUT
 cout << "TIMEOUT:.........................." << buff << '\n';
 TIMOUT=(int)buff;

//}         // Exibe no vídeo

  system("PAUSE");
  return 0;
}

