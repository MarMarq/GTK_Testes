
#include "rs232W_fn01.h"

//#include <curses.h>


string recebeStringRS232(){
  char c;
  string buffer;
  int tamanhoarq=0;
  unsigned int count=0;

  cout << endl << "AGUARDANDO ENVIO DE SINAL ROBO --> PC:" << endl;
  cout << endl << "-- Pressione QUALQUER TECLA para terminar a Leitura de SINAL --" << endl;
  cout <<         "AGUARDANDO RESPOSTA DO ROBO:";

  while (!kbhit())
  {
  if ( !recebe_caracter_serial(&c) )
  {
    if (count< 30) {
        cout << ".";
        count++;   }
    if (count==30) {
        cout <<       "NENHUMA RESPOSTA!!" << endl;
        cout <<       "AGUARDANDO RESPOSTA DO ROBO:";
        count=0;   }
  }
   else
  {   if (c==13)
      {
      printf("\nByte [%d]   |   DADO transferido ROBO --> PC: (CR)  |   Valor Decimal [%d]\n",tamanhoarq,c,(int)c);
      cout <<       " Recebido STRING [" << buffer << "]" << endl;
      return buffer;
      }
      buffer+=c;
      printf("\nByte [%d]   |   DADO transferido ROBO --> PC: %c    |   Valor Decimal [%d]",tamanhoarq,c,(int)c);

  }
  }
  return buffer="<RECEPCAO CANCELADA PELO USUARIO>";
}

int EnviaStringRS232( string str ){
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
/*
void EnviaStringRS232Interface()
{
    string str,str_temp;
    int i;
    printw("\nDigite STRING a ser enviada seguido de <ENTER>. ");
    printw("\nOu digite <ESC> para SAIR. ");
    printw("\nDigite a STRING: ");
    str.clear();
do
{
    i=wgetch(stdscr);
    if (i!=27)
    str+=(char)i;
    else
    str+='\0';

    str_temp = str;
    if (i!=13)
    {
        printw("%c", i );
        refresh();
    }
    else
    {
    str_temp[str_temp.size()-1]='(';
    str_temp+="CR)";
    printw("  ---->  Enviando [%s]", str_temp.c_str() );
    printw("\nDigite a STRING: ");
    refresh();
    EnviaStringRS232(str);
    str.clear();
    str_temp.clear();
    }

}while (i!=27);
}

void VisualizaRX_Extratificada()
{   int  i;
    char c;
cout << endl << "    <Tecle algo para iniciar a leitura de RX ESTRATIFICADA>" << endl;
cout << endl << "*** Para voltar ao MENU PRINCIPAL teclar <ESC> ***" << endl;
getch();

do
{
while ( !kbhit() )
{
if (recebe_caracter_serial(&c))
printf("\nRECEBIDO [DISPOSITIVO --> ESTE PC]   |   DADO [%c] = Valor Decimal [%d]",c,(int)c);
else
printf("\nNENHUM DADO Recebido [DISPOSITIVO --> ESTE PC] ...");
}
    i=getch();
    if (i!=27)
    c = (char)i;
    else c='\0';
    char *cstr = new char[2];
    cstr[0]=c;
    cstr[1]='\0';
    envia_caracter_serial( cstr );
    if ( cstr[0]!= 13 )
    printf("\n                TRANSMITINDO [ESTE PC --> DISPOSITIVO]   |   DADO [%s] = Valor Decimal [%d]",cstr, i );
    else
    printf("\n                TRANSMITINDO [ESTE PC --> DISPOSITIVO]   |  DADO [(CR)] = Valor Decimal [%d]", i );

}
while (i!=27);
}

void VisualizaRX_Frases()
{   int  i;
    int num = 60;
    int count;
    char c;
    count = num;
    bool modo=true;

cout << endl << "    <Tecle algo para iniciar a leitura de RX em FRASES>" << endl;
cout << endl << "*** Para voltar ao MENU PRINCIPAL tecle <ESC> ***" << endl;
getch();
do
{
while ( !kbhit() )
{
    if (recebe_caracter_serial(&c))
         if (c==13)
            printf("(CR)\n");
            else
            printf("%c",c);

    if (!modo)
    {
        if (count==num) printf("\nAguardando");
        else             printf(".");
        if (count==0)
            {
            count=num+1;
            printf("SEM RESPOSTA!!");
            }
        count--;
    }
}
    i=getch();
    if (i!=27)
    c = (char)i;
    else c='\0';
    char *cstr = new char[2];
    cstr[0]=c;
    cstr[1]='\0';
    envia_caracter_serial( cstr );
    if ( cstr[0]!= 13 )
    printf("\n                TRANSMITINDO [ESTE PC --> DISPOSITIVO]   |   DADO [%s] = Valor Decimal [%d]",cstr, i );
    else
    printf("\n                TRANSMITINDO [ESTE PC --> DISPOSITIVO]   |  DADO [(CR)] = Valor Decimal [%d]", i );

}
while (i!=27);
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
    list1.push_back(name);
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
       list2.push_back(list1[k]);
 }
  cout << endl << "Selecione o numero do Arquivo a ser ENVIADO via RS232: " ;
  cin >> op;
  if ( (op> list2.size()+1 )||(op<= 0 ) )
  {
   cout << endl << endl << "* ERRO! Entrada Invalida! *" << endl;
   cout << endl <<         "<TECLE ALGO PARA CONTINUAR>" << endl;
   getch();
   goto LISTAGEM;
  }else
   cout << "Enviando o arquivo [" << list2[op-1] << "]" << endl;

  buffer = new char[list2[op-1].length()+1];
  strcpy(buffer, list2[op-1].c_str());
    is.open ( buffer );
    if (is.is_open())
    {
        name.clear();
  while (is.good())     // loop while extraction from file is possible
  {
    c = is.get();       // get character from file
        if  (is.eof()==true)
        {
        name+=c;
        EnviaStringRS232( name );
        }
            if  (c!=10)
            name+=c;
            else
            {
            name+=c;
            EnviaStringRS232( name );
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
*/
