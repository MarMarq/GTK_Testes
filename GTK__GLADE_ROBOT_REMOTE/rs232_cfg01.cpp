
#include "rs232_cfg01.h"

#include <cstdlib>
//#include <curses.h>


using namespace std;

vector <string> LeRS232Conf(string str)
{
MANIPULA_ARQUIVO ponteiro;
vector <string> config;

  string buffSUCESSO;
  string buffPORTA;
  string buffDATABITS;
  string buffSTOPBIT;
  string buffPAR;
  string buffTAXA;
  string buffTIMEOUT;

config = ponteiro.LeLinhaArqASCII( str );

buffPORTA    = config[0];
buffDATABITS = config[1];
buffSTOPBIT  = config[2];
buffPAR      = config[3];
buffTAXA     = config[4];
buffTIMEOUT  = config[5];
/*
  printw("\nbuffPORTA = %s",buffPORTA.c_str() );
  printw("\nbuffDATABTIS = %s",buffDATABITS.c_str() );
  printw("\nbuffSTOPBIT = %s",buffSTOPBIT.c_str() );
  printw("\nbuffPAR = %s",buffPAR.c_str() );
  printw("\nbuffTAXA = %s",buffTAXA.c_str() );
  printw("\nbuffTIMEOUT = %s",buffTIMEOUT.c_str() );
 getch(); */

if (ConfiguraSerial(buffPORTA, buffDATABITS, buffSTOPBIT, buffPAR, buffTAXA, buffTIMEOUT))
   {config.push_back("true");
    return config;}
    else
   {config.push_back("false");
    return config;}
}
//********************************************************************************************************
//********************************************************************************************************
bool ConfiguraSerial(string buffPORTA, string buffDATABITS, string buffSTOPBIT,
                    string buffPAR,   string buffTAXA,     string buffTIMEOUT)
{
int PORTA;
int DataBits;
BYTE STOPBITS;
BYTE PARIDADE;
int TAXA;
int timeout;
BOOL ERRO;
// Verifica qual porta COM será aberta **********************************************
 if (buffPORTA=="COM1")  PORTA=COM1;
 if (buffPORTA=="COM2")  PORTA=COM2;
 if (buffPORTA=="COM3")  PORTA=COM3;
 if (buffPORTA=="COM4")  PORTA=COM4;
 if ((PORTA!=COM1)&&(PORTA!=COM2)&&(PORTA!=COM3)&&(PORTA!=COM4))
 {printf(   "\nErro de Leitura arquivo: Linha de Configuracao de PORTA INVALIDA!" );
  printf(   "\nTecle algo para SAIR do programa\n\n" );
// getch();
 return false;}
// Lê a configuração dos Bits de DADOS ****************************************
 DataBits=atoi(buffDATABITS.c_str() );
// Lê a configuração dos Bits de PARADA ****************************************
 if ( buffSTOPBIT=="ONESTOPBIT")   STOPBITS=ONESTOPBIT;
 if ( buffSTOPBIT=="ONE5STOPBITS") STOPBITS=ONE5STOPBITS;
 if ( buffSTOPBIT=="TWOSTOPBITS")  STOPBITS=TWOSTOPBITS;
 if ((buffSTOPBIT!="ONESTOPBIT")&&(buffSTOPBIT!="ONE5STOPBITS")&&(buffSTOPBIT!="TWOSTOPBITS"))
 {printf(   "\nErro de Leitura arquivo: Linha de Configuracao de PARADA!" );
  printf(   "\nTecle algo para SAIR do programa\n\n" );
 //getch();
 return false;}
 // Lê a configuração de PARIDADE ***********************************************
  if (buffPAR=="NOPARITY")   PARIDADE=NOPARITY;
 if ( buffPAR=="MARKPARITY") PARIDADE=MARKPARITY;
 if ( buffPAR=="EVENPARITY")  PARIDADE=EVENPARITY;
 if ( buffPAR=="ODDPARITY")  PARIDADE=ODDPARITY;
 if ((buffPAR!="NOPARITY")&&(buffPAR!="MARKPARITY")&&(buffPAR!="EVENPARITY")&&(buffPAR!="ODDPARITY"))
 {printf(   "\nErro de Leitura arquivo: Linha de Configuracao de PARIDADE!" );
  printf(   "\nTecle algo para SAIR do programa\n\n" );
// getch();
 return false;}
// Lê a configuração de TAXA *************************************************
  TAXA=atoi( buffTAXA.c_str() );
// Lê a configuração de TIMEOUT ***********************************************
  timeout=atoi( buffTIMEOUT.c_str() );

  ERRO=Inicia_Serial_Port(PORTA, DataBits, STOPBITS, PARIDADE, TAXA, timeout);
  if (ERRO==FALSE)   {
  printf(   "\nERRO: Nao foi possivel INICIAR a PORTA [%s]",buffPORTA.c_str() );
  printf(   "\nTECLE ALGO PARA CONTINUAR\n" );
//  printw(   "TECLE ALGO PARA ENCERRAR O PROGRAMA." );
//  getch();
  return false;   }
  else
  printf(   "\nPORTA %s iniciada com SUCESSO!!\n", buffPORTA.c_str() );
  return true;
}
//********************************************************************************************************
//********************************************************************************************************


