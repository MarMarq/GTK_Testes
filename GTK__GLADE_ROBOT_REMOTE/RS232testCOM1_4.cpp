#include <windows.h>
#include <winbase.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "rs232api2.h"
#include "strmanip03.h"

using namespace std;

void startup();
string recebeStringRS232();
void enviaRS232(unsigned int i);
int EnviaString( string str );
void VisualizaRX();
int ConfiguraSerial(int PORTA, int DataBits, BYTE STOPBITS, BYTE PARIDADE, int TAXA, int timeout  );
int EnviaArquivo();
int DataLink();

int main () {

  //int i=0;
  int op=15;
  int op2=20;
  BOOL ERRO;
  string name;

int PORTA;
int DataBits;
BYTE STOPBITS;
BYTE PARIDADE;
int TAXA;
int timeout;

  string buff;
  string buffPORTA;
  string buffSTOPBIT;
  string buffPAR;

  char *temp;

// Abre arquivo para leitura **************************************************
ifstream fin("RS232.conf");
 cout << "Lendo o arquivo RS232.conf..." << endl;
// Lê qual porta COM será aberta **********************************************
  getline(fin, buff);
 if (buff=="COM1")  PORTA=COM1;
 if (buff=="COM2")  PORTA=COM2;
 if (buff=="COM3")  PORTA=COM3;
 if (buff=="COM4")  PORTA=COM4;
 if ((PORTA!=COM1)&&(PORTA!=COM2)&&(PORTA!=COM3)&&(PORTA!=COM4))
 {cout << endl <<"Erro de Leitura arquivo: Linha de Configuracao de PORTA!" << endl;
 cout << "Tecle algo para SAIR do programa" << endl;
 getch();
 return 0; }
 buffPORTA=buff;
// Lê a configuração dos Bits de DADOS *****************************************
 getline(fin, buff);
 temp = new char[buff.length()+1];
 strcpy(temp, buff.c_str());
 DataBits=atoi(temp);
// Lê a configuração dos Bits de PARADA ****************************************
 getline(fin, buff);
 if (buff=="ONESTOPBIT")   STOPBITS=ONESTOPBIT;
 if (buff=="ONE5STOPBITS") STOPBITS=ONE5STOPBITS;
 if (buff=="TWOSTOPBITS")  STOPBITS=TWOSTOPBITS;
 if ((buff!="ONESTOPBIT")&&(buff!="ONE5STOPBITS")&&(buff!="TWOSTOPBITS"))
 {cout << endl <<"Erro de Leitura arquivo: Linha de Configuracao de PARADA!" << endl;
 cout << "Tecle algo para SAIR do programa" << endl;
 getch();
 return 0; }
 buffSTOPBIT=buff;
// Lê a configuração de PARIDADE ***********************************************
 getline(fin, buff);
  if (buff=="NOPARITY")   PARIDADE=NOPARITY;
 if (buff=="MARKPARITY") PARIDADE=MARKPARITY;
 if (buff=="EVENPARITY")  PARIDADE=EVENPARITY;
 if (buff=="ODDPARITY")  PARIDADE=ODDPARITY;
 if ((buff!="NOPARITY")&&(buff!="MARKPARITY")&&(buff!="EVENPARITY")&&(buff!="ODDPARITY"))
 {cout << endl <<"Erro de Leitura arquivo: Linha de Configuracao de PARIDADE!" << endl;
 cout << "Tecle algo para SAIR do programa" << endl;
 getch();
 return 0; }
  buffPAR=buff;
// Lê a configuração da Taxa BaudRate (de transmissão) ***************************
 getline(fin, buff);
 temp = new char[buff.length()+1];
 strcpy(temp, buff.c_str());
 TAXA=atoi(temp);
// Lê a configuração do TIMEOUT **************************************************
 getline(fin, buff);
 temp = new char[buff.length()+1];
 strcpy(temp, buff.c_str());
 timeout=atoi(temp);

   fin.close();

    ERRO=inicializa_serial(PORTA, DataBits, STOPBITS, PARIDADE, TAXA, timeout);
  if (ERRO==FALSE)   {
  cout << endl << "ERRO: Nao foi possivel INICIAR a PORTA "  << buffPORTA << endl << endl;
  cout << "Verifique o arquivo RS232.conf e execute o programa novamente." << endl;
  cout << "TECLE ALGO PARA ENCERRAR O PROGRAMA." << endl;
  getch();
  exit(0);   }
  else
  cout << endl << "PORTA " << buffPORTA << " iniciada com SUCESSO!!" << endl << endl;

while(op)
{ cout << "Configuracoes atuais" << endl << endl;
  cout << "PORTA:............................" << buffPORTA << endl;
  cout << "Bits de DADOS:...................." << DataBits << endl;
  cout << "Configuracao de PARADA:..........." << buffSTOPBIT << '\n';
  cout << "Configuracao de PARIDADE:........." << buffPAR << '\n';
  cout << "TAXA de TRANSMISSAO (BaudRate):..." << TAXA << '\n';
  cout << "TIMEOUT:.........................." << timeout << endl << endl;

  cout << "|--------------------------------------------|" << endl;
  cout << "| -- Comunica RS232 -- Versao 1.0 (rev02) -- |" << endl;
  cout << "|--------------------------------------------|" << endl;
  cout << "| Digite a opcao abaixo:                     |" << endl;
  cout << "|--------------------------------------------|" << endl;
  cout << "| Visualizar Recepcao (Rx)  [ASCII] ---[1]   |" << endl;
  cout << "| Configurar/Rever Interface RS232 ----[2]   |" << endl;
  cout << "| Selecionar Arquivo a ser ENVIADO ----[3]   |" << endl;
  cout << "| Abrir um Link de DADOS PC <-> ROBO --[4]   |" << endl;
  cout << "| Sair do Programa --------------------[5]   |" << endl;
  cout << "| Sobre este Programa -----------------[6]   |" << endl;
  cout << "|--------------------------------------------|" << endl << endl;
  op=getch();

  switch (op){
  case '1':
  cout << endl<< "Voce TECLOU [1]" << endl<< endl;
  cout << "FUNCAO EM FASE DE TESTE!!" << endl<< endl;
  cout << "<PRESSIONE QUALQUER TECLA PARA CONTINUAR>"<<endl;
      op2=getch();
  VisualizaRX();
  break;

  case '2':
  cout << endl<< "Voce TECLOU [2]" << endl<< endl;
  cout << "FUNCAO AINDA EM IMPLEMENTACAO!!" << endl<< endl;
  cout << "<PRESSIONE QUALQUER TECLA PARA CONTINUAR>"<<endl;
      op2=getch();
  ConfiguraSerial(PORTA, DataBits, STOPBITS, PARIDADE, TAXA, timeout);
  break;

  case '3':
  cout << endl<< "Voce TECLOU [3]" << endl<< endl;
  cout << "FUNCAO EM FASE DE TESTE!!" << endl<< endl;
  cout << "<PRESSIONE QUALQUER TECLA PARA CONTINUAR>"<<endl;
      op2=getch();
  EnviaArquivo();
  break;

  case '4':
  cout << endl<< "Voce TECLOU [4]" << endl<< endl;
  cout << "FUNCAO AINDA EM IMPLEMENTACAO!!" << endl<< endl;
  cout << "<PRESSIONE QUALQUER TECLA PARA CONTINUAR>"<<endl;
      op2=getch();
  DataLink();
  break;

  case '5':
  cout << endl<< "Voce TECLOU [5]" << endl<< endl;
  cout << "Deseja realmente SAIR do programa? Tecle <S/N>" << endl<< endl;
      op2=getch();
  switch (op2){
  case 'S':
  libera_serial();
  return 1;
  libera_serial();
  case 's':
  return 1;
  case 'N':
  goto REINICIA_MENU;
  break;
  case 'n':
  goto REINICIA_MENU;
  break;
  }

  case '6':
  cout << endl << endl<< endl << endl;
  cout <<      "|--------------------------------------------|" << endl;
  cout <<      "| -- Comunica RS232 -- Versao 1.0 (rev02) -- |" << endl;
  cout <<      "|--------------------------------------------|" << endl;
  cout <<      "|Desenvolvido por Marcio H D Marques         |" << endl;
  cout <<      "|Maio de 2011                                |" << endl;
  cout <<      "|--------------------------------------------|" << endl;
  cout <<endl<<"  <PRESSIONE QUALQUER TECLA PARA CONTINUAR>";
  getch();
  break;
  }
  REINICIA_MENU:
  cout << endl << endl<< endl << endl<< endl << endl<< endl << endl << endl << endl;
  cout << endl << endl<< endl << endl<< endl << endl<< endl << endl << endl << endl;
  cout << endl << endl<< endl << endl<< endl << endl<< endl << endl << endl << endl;
  cout << endl << endl<< endl << endl<< endl << endl<< endl << endl << endl << endl;
  cout << endl << endl<< endl << endl<< endl << endl<< endl << endl << endl << endl;
  cout << endl << endl<< endl << endl<< endl << endl<< endl << endl << endl << endl;
}
  return 0;
}

void startup(){
  char c;
  unsigned char buffer[60000];
  int tamanhoarq=0;

  cout << endl << "TESTANDO ENVIO DE SINAL ROBO --> PC:...." << endl;
  cout << endl << "-- Pressione <ESC> para terminar a Leitura de RX --" << endl;
  while (!kbhit())
  if (recebe_caracter_serial(&c))
  {
      buffer[tamanhoarq]=c;
      tamanhoarq++;
      printf("\nByte [%d]   |   DADO transferido ROBO --> PC: %c    |   Valor Decimal [%d]",tamanhoarq,c,(int)c);
   }
   else
  {
    printf(("\nNENHUM DADO TRANSFERIDO ROBO --> PC.."));
  }
}

string recebeStringRS232(){
  char c;
  string buffer;
  int tamanhoarq=0;
  unsigned int count=0;

  cout << endl << "AGUARDANDO ENVIO DE SINAL ROBO --> PC:" << endl;
  cout << endl << "-- Pressione QUALQUER TECLA para terminar a Leitura de SINAL --" << endl;
  cout <<         "AGUARDANDO RESPOSTA DO ROBO:";
  LE_RS232:

//  while (!kbhit())
//  {
//  if ( !recebe_caracter_serial(&c) )
//  {
//    if (count< 30) {
//        cout << ".";
//        count++;
//                   }
//    if (count==30) {
//        cout <<       "NENHUMA RESPOSTA!!" << endl;
////       cout << endl<<"*******************************" << endl;
////       cout <<       "*  NENHUM DADO TRANSFERIDO!!  *" << endl;
////       cout <<       "*******************************" << endl;
//        cout <<       "AGUARDANDO RESPOSTA DO ROBO:";
//        count=0;
//                   }
//    goto LE_RS232;
//    return buffer;
//  }
//   else
//  {
////      buffer+=c;
////      printf("\nByte [%d]   |   DADO transferido ROBO --> PC: %c    |   Valor Decimal [%d]",tamanhoarq,c,(int)c);
////      cout <<       "Recebido STRING [" << buffer << "]" << endl;
////      if (c!='\n')
////      goto LE_RS232;
////      return buffer;
//      if (c!='\n')
//      {
//      buffer+=c;
//      printf("\nByte [%d]   |   DADO transferido ROBO --> PC: %c    |   Valor Decimal [%d]",tamanhoarq,c,(int)c);
//      goto LE_RS232;
//      }
//      cout <<       "Recebido STRING [" << buffer << "]" << endl;
//      return buffer;
//  }
//  }

  while (!kbhit())
  {
  if ( !recebe_caracter_serial(&c) )
  {
    if (count< 30) {
        cout << ".";
        count++;
                   }
    if (count==30) {
        cout <<       "NENHUMA RESPOSTA!!" << endl;
        cout <<       "AGUARDANDO RESPOSTA DO ROBO:";
        count=0;
                   }
    goto LE_RS232;
  }
   else
  {
      buffer+=c;
      printf("\nByte [%d]   |   DADO transferido ROBO --> PC: %c    |   Valor Decimal [%d]",tamanhoarq,c,(int)c);
      cout <<       "Recebido STRING [" << buffer << "]" << endl;
      if (c=(int)13) return buffer;
      goto LE_RS232;
  }
  }
  return buffer="<RECEPCAO CANCELADA PELO USUARIO>";
}

void enviaRS232(unsigned int i){
  char c;
  string name;
  c = (char)i;
    name.clear();
    name.append(1,c);
//    name.append(1,'\n');
    cout << "\nTESTANDO ENVIO DE SINAL PC --> ROBO:.... ENVIANDO ["<< name[0] << "] = " << (int)c<< endl;

    EnviaString(name );
}

int EnviaString( string str ){
unsigned int i;
  string temp;
  string::iterator it;
  temp = str;
for ( i = 0 ; i < str.size() ; i++)
{
  char *buffer = new char[temp.length()+1];
  strcpy(buffer, temp.c_str());
    envia_caracter_serial(buffer);
    it=temp.begin();
    temp.erase (it);
}
return 0;
}

void VisualizaRX(){

int i;
cout << endl << "    <Tecle algo para iniciar a leitura de RX>" << endl;
cout << endl << "*** Para voltar ao MENU PRINCIPAL tecle <ESC> ***" << endl;

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
//libera_serial();
}

int ConfiguraSerial(int PORTA, int DataBits, BYTE STOPBITS, BYTE PARIDADE, int TAXA, int timeout  ){
BOOL ERRO;
int op=20;
int op2=20;
int c=0;
while(op!='4'){

  cout << "|--------------------------------------------|" << endl;
  cout << "|      -- Configuracao Atual RS232 --        |" << endl;
  cout << "|--------------------------------------------|" << endl;
  cout << "| Arquivo de Configuracao: RS232.conf        |" << endl;
if (c!=0){
  cout << "|--------------------------------------------|" << endl;
  cout << "|-------------*!* ALTERADO *!*---------------|" << endl;
         }
         else{
  cout << "|--------------------------------------------|" << endl;
  cout << "|-----------OK!---ATUALIZADO---OK!-----------|" << endl;
         }
  cout << "|--------------------------------------------|" << endl;
  cout << "| Porta: ----------------->  COM" << PORTA << endl;
  cout << "| Taxa BaudRate: --------->  " << TAXA << endl;
  cout << "| Bits de DADOS: --------->  " << DataBits << endl;
  cout << "| Bit(s) de PARADA:------->  " << STOPBITS << endl;
  cout << "| PARIDADE: -------------->  " << PARIDADE << endl;
  cout << "| Controle de Fluxo: NAO" << endl << endl;
  cout << "|--------------------------------------------|" << endl;



  cout << "|--------------------------------------------|" << endl;
  cout << "|          -- Configura RS232 --             |" << endl;
  cout << "|--------------------------------------------|" << endl;
  cout << "| Digite a opcao abaixo:                     |" << endl;
  cout << "|--------------------------------------------|" << endl;
  cout << "| Seleciona porta COMx ----------------[1]   |" << endl;
  cout << "| Configura a Taxa BaudRate -----------[2]   |" << endl;
  cout << "| Seleciona PARIDADE ------------------[3]   |" << endl;
  cout << "| Seleciona Bit(s) de PARADA ----------[4]   |" << endl;
  cout << "| Seleciona Bits de DADOS -------------[5]   |" << endl;
  cout << "| Seleciona o valor TIMEOUT -----------[6]   |" << endl;
  cout << "| Terminar/Gravar a Configuracao ------[7]   |" << endl;
  cout << "| Terminar/Descartar Configuracao -----[8]   |" << endl;
  cout << "|--------------------------------------------|" << endl << endl;
  op=getch();

  switch (op){
  case '1':
  cout << endl<< "Você TECLOU [1]" << endl<< endl;
  cout << "1 = COM1" << endl;
  cout << "2 = COM2" << endl;
  cout << "3 = COM3" << endl;
  cout << "4 = COM4" << endl << endl;
  cout << "Digite o numero da porta COM (acima) para seleciona-la:";
  cin >> op2;
    if (op2==1) PORTA=COM1;
    if (op2==2) PORTA=COM2;
    if (op2==3) PORTA=COM3;
    if (op2==4) PORTA=COM4;
  c=1;
    if ( (op2!=1)&&(op2!=2)&&(op2!=3)&&(op2!=4) )
    {
  cout << endl << "**** ERRO DE ENTRADA! ****" << endl;
  cout <<         "*** OPCAO INEXISTENTE! ***" << endl;
  c=0;
    }
  break;

  case '2':
  cout << endl<< "Você TECLOU [2]" << endl<< endl;
  cout << "Digite o valor da TAXA BaudRate para seleciona-la." << endl;
  cout << "Ex.: 1200 para 1200 Bps, 9600 para 9600 Bps, ..., etc." << endl << endl;
  cout << "Nova TAXA:";
  cin >> TAXA;
  c=1;
  break;

  case '3':
  cout << endl<< "Você TECLOU [3]" << endl<< endl;
  cout << "1 = SEM PARIDADE   [NOPARITY]" << endl;
  cout << "2 = PARIDADE MARCA [MARKPARITY]" << endl;
  cout << "3 = PARIDADE PAR   [EVENPARITY]" << endl;
  cout << "4 = PARIDADE IMPAR [ODDPARITY]" << endl << endl;
  cout << "Digite o padrao de PARIDADA conforme as opcoes abaixo:";
    cin >> op2;
    if (op2==1) PARIDADE=NOPARITY;
    if (op2==2) PARIDADE=MARKPARITY;
    if (op2==3) PARIDADE=EVENPARITY;
    if (op2==4) PARIDADE=ODDPARITY;
  c=1;
    if ( (op2!=1)&&(op2!=2)&&(op2!=3)&&(op2!=4) )
    {
  cout << endl << "**** ERRO DE ENTRADA! ****" << endl;
  cout <<         "*** OPCAO INEXISTENTE! ***" << endl;
  c=0;
    }
  break;

  case '4':
  cout << endl<< "Você TECLOU [4]" << endl<< endl;
  cout << "1 = 1.0 Bit" << endl;
  cout << "2 = 1.5 Bits" << endl;
  cout << "3 = 2.0 Bits" << endl << endl;
  cout << "Digite o padrao dos Bits de PADADA conforme as opcoes abaixo:";
    cin >> op2;
    if (op2==1) STOPBITS=ONESTOPBIT;
    if (op2==2) STOPBITS=ONE5STOPBITS;
    if (op2==3) STOPBITS=TWOSTOPBITS;
  c=1;
    if ( (op2!=1)&&(op2!=2)&&(op2!=3) )
    {
  cout << endl << "**** ERRO DE ENTRADA! ****" << endl;
  cout <<         "*** OPCAO INEXISTENTE! ***" << endl;
  c=0;
    }
  break;

  case '5':
  cout << endl<< "Você TECLOU [5]" << endl<< endl;
  cout << "1 = 4 Bits" << endl;
  cout << "2 = 5 Bits" << endl;
  cout << "3 = 8 Bits" << endl;
  cout << "4 = 9 Bits" << endl;
  cout << "Digite o padrao dos Bits de DADOS conforme as opcoes abaixo:";
    cin >> op2;
    if ( (op2!=1)&&(op2!=2)&&(op2!=3) )
    {
  cout << "**** ERRO DE ENTRADA! ****" << endl;
  cout << "*** OPCAO INEXISTENTE! ***" << endl;
  c=0;
    }else
    {
  c=1;
  DataBits=op2;
    }
  break;

  case '6':
    cout << endl<< "Você TECLOU [6]" << endl<< endl;
  cout << "Ex.: 200 para 200 microsegundos." << endl << endl;
  cout << "O valor PADRAO e 100 microsegundos." << endl << endl;
  cout << "Digite o valor do TIMEOUT em microsegundos:";
    cin >> op2;
  if (op2==100) c=0;
  else
  c=1;

  break;
  case '7':
  cout << endl<< "Você TECLOU [7]" << endl<< endl;

  ERRO=inicializa_serial(PORTA, DataBits, STOPBITS, PARIDADE, TAXA, timeout);
  if (ERRO==FALSE)
  {
  cout << endl << "ERRO: Nao foi possivel ATUALIZAR as configuracoes!!" << endl << endl;
  cout << "TECLE ALGO PARA RETORNAR AO MENU PRINCIPAL" << endl;
  c=1;

  }else
  {
  cout << endl << "Configuracoes ATUALIZADAS com SUCESSO!!" << endl << endl;
  c=0;
  }
  break;

  case '8':
  cout << endl<< "Você TECLOU [8]" << endl<< endl;
  cout << endl << "Deseja mesmo descartar as configuracoes?" << endl << endl;
  cout << "Digite 'S' para Descartar ou 'N' para Retornar ao Menu de Configuracoes." << endl;
    op2=getch();
  switch (op2){
  case 'S':
  return 1;
  case 's':
  return 1;
  case 'N':
  return 0;
  case 'n':
  return 0;
  }
  break;
  }
}
 return 0;
}

int EnviaArquivo(){
unsigned char c;
         char *buffer;
unsigned int  i,j,k;
unsigned int count=1;

unsigned int op=10000;
  string name;
  vector <string> list1;
  vector <string> list2;
  ifstream is;

LISTAGEM:

count=1;
op=10000;
name.clear();
list1.clear();
list2.clear();

 for (i = 0 ; i <= 1 ; i++)
 {
  if (i==0) system("dir *.txt /ON /A-D > dir.temp");
  if (i==1) {system("dir *.txt /B /ON > dir.temp");
               list1.clear();}
    is.open ("dir.temp", ios::in );
      while (is.good())     // loop while extraction from file is possible
  {
    getline(is, name );
//    cout << "Linha [" << count2 << "] --[" << name << "]" << endl;
    list1.push_back(name);
//    count2++;
//   getch();
  }
  is.close();
  if (i==0)
  {
  cout << endl << "Listagem do Diretorio Atual:" << endl << endl;
  for (j = 0 ; j < list1.size() ; j++)
  {
      if ( (j>4)&&(j<list1.size()-3))
      {
       cout <<  "[" << setfill('0') << setw(2) << count << "] --> " << list1[j] <<endl;
       count++;
      }
  }
  }
  if (i==1)
   for (k = 0 ; k < list1.size()-1 ; k++)
//   {
       list2.push_back(list1[k]);
//       cout << "list1.[" << k << "] =[" << list1[k] << "] --> list2.[" <<k << "] =[" <<list2[k] <<"] - size("
//       << list2[k].size() << ")"<< endl;
//   getch();
   //}
 }

//  cout << endl << "Tamanho do VECTOR list2 = " << list2.size() << endl;

  cout << endl << "Selecione o numero do Arquivo a ser ENVIADO via RS232: " ;
  cin >> op;
  if ( (op> list2.size()+1 )||(op<= 0 ) )
  {
   cout << endl << endl << "* ERRO! Entrada Invalida! *" << endl;
   cout << endl <<         "<TECLE ALGO PARA CONTINUAR>" << endl;
   getch();
   goto LISTAGEM;
  }else
  {
    cout << "Enviando o arquivo [" << list2[op-1] << "]" << endl;
//    "]  -str [" << list2[op-1].size() << "]"<< endl;
  }

  buffer = new char[list2[op-1].length()+1];
  strcpy(buffer, list2[op-1].c_str());

//    cout << "Abrindo arquivo [" << buffer << "] -newchar [" << strlen(buffer) << "]" << endl;
    is.open ( buffer );
    if (is.is_open())
    {
//        cout << "Abrindo [" << buffer << "] -newchar aberto com SUCESSO!" << endl;
        name.clear();
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
            name.clear();
            }
    }
  is.close();
    }else
    {
        cout << "Falha ao Abrir o arquivo [" << buffer << "] -newchar !!" << endl;
        cout << endl <<         "<TECLE ALGO PARA CONTINUAR>" << endl;
        getch();
        return 0;
    }

  system("del dir.temp");
  system("PAUSE");
  return 1;

}

int DataLink(){

unsigned char c;
    string str;
    string name;
    char *CHARstr;
    ifstream is;


  cout << endl << endl<< endl << endl;
  cout <<      "|--------------------------------------------|" << endl;
  cout <<      "| Iniciando um Link de dados PC -- ROBO..... |" << endl;
  cout <<      "|--------------------------------------------|" << endl;
  cout <<      "| Observacao: O Programa executado no ROBO   |" << endl;
  cout <<      "| deve enviar um pedido de dados para o PC.  |" << endl;
  cout <<      "|                                            |" << endl;
  cout <<      "| Exemplo: PRINT #1,\"R_DATA01.txt\"           |" << endl;
  cout <<      "|                                            |" << endl;
  cout <<      "|  |----|                         |----|     |" << endl;
  cout <<      "|  |ROBO| ----\"R_DATA01.txt\"----> |    |     |" << endl;
  cout <<      "|  |CTRL|                         | PC |     |" << endl;
  cout <<      "|  |CR-1| <-------**DADOS**------ |    |     |" << endl;
  cout <<      "|  |----|                         |----|     |" << endl;
  cout <<      "|                                            |" << endl;
  cout <<      "| IMPORTANTE: O NOME DO ARQUIVO ARMAZENADO   |" << endl;
  cout <<      "| PC DEVE TER TODAS AS LETRAS EM MAIUSCULAS  |" << endl;
  cout <<      "|--------------------------------------------|" << endl;
  cout <<endl<<"  <PRESSIONE QUALQUER TECLA PARA CONTINUAR>";
  getch();

  str = recebeStringRS232();
  cout << endl << "Recebido   [Original]: [" << str << "]" << endl;
  str.erase(str.end()-1);
  cout << endl << "Recebido [Modifacado]: [" << str << "]" << endl;
getch();
  if (str.size()!=0 )
    {
  cout << endl << "Recebido: [" << str << "]" << endl;
  cout << endl << "Enviando: [" << str << "]" << endl;

//   CHARstr = new char[ str.size()];
//   for (unsigned int i = 0 ; i < str.size()-1 ; i++ )
//   CHARstr[i]=str[i];

   CHARstr = new char[str.length()+1];
   strcpy(CHARstr, str.c_str());

      is.open ( CHARstr , ifstream::in );

  if (is.is_open())
  {
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
  }
  else
  cout << "ERRO ao ABRIR O ARQUIVO: " << str << endl;

  is.close();
      }
      else
  cout <<endl<<"  ***  Operacao CANCELADA pelo USUARIO  ***";
  cout <<endl<<"  <PRESSIONE QUALQUER TECLA PARA CONTINUAR>";
  getch();

return 0;
}



