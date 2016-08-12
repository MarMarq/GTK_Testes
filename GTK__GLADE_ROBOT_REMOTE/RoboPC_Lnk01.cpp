
#include "RoboPC_Lnk01.h"
#include "rs232W_fn01.h"
#include "file_manip01.h"

int DataLink(){
//unsigned int i;
unsigned int NumLin;
unsigned int NumLinhas;

    string str;
    vector <string> vector_str;

    MANIPULA_ARQUIVO ponteiro;

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
  cout <<      "|  |ROBO|                         | PC |     |" << endl;
  cout <<      "|  |CR-1|                         |    |     |" << endl;
  cout <<      "|  |----|                         |----|     |" << endl;
  cout <<      "|  |    | ----\"R_DATA01.txt\"----> |    |     |" << endl;
  cout <<      "|  |    |                         |    |     |" << endl;
  cout <<      "|  |    | --------\"DTRQT\"-------> |    |     |" << endl;
  cout <<      "|  |    | <------**DADOS**------- |    |     |" << endl;
  cout <<      "|  |    |                         |    |     |" << endl;
  cout <<      "|  |    | --------\"DTRQT\"-------> |    |     |" << endl;
  cout <<      "|  |    | <------**DADOS**------- |    |     |" << endl;
  cout <<      "|  |    |                         |    |     |" << endl;
  cout <<      "|  |    | --------\"DTRQT\"-------> |    |     |" << endl;
  cout <<      "|  |    | <------**DADOS**------- |    |     |" << endl;
  cout <<      "|  |    |                         |    |     |" << endl;
  cout <<      "|  |    | --------\"LOOP\"--------> |    |     |" << endl;
  cout <<      "|  .    .          ....           .    .     |" << endl;
  cout <<      "|  .    .          ....           .    .     |" << endl;
  cout <<      "|                                            |" << endl;
  cout <<      "|  |    | --------\"ENDL\"--------> |    |     |" << endl;
  cout <<      "|  |----|                         |----|     |" << endl;
  cout <<      "|                                            |" << endl;
  cout <<      "| IMPORTANTE: O NOME DO ARQUIVO ARMAZENADO   |" << endl;
  cout <<      "| PC DEVE TER TODAS AS LETRAS EM MAIUSCULAS  |" << endl;
  cout <<      "|--------------------------------------------|" << endl;
  cout <<endl<<"  <PRESSIONE QUALQUER TECLA PARA LIMPAR O BUFFER>";
// getch();

  cout <<endl<<"  <PRESSIONE QUALQUER TECLA PARA CONTINUAR>";
  getch();
str=recebeStringRS232();    // Recebe o Nome do arquivo a ser manipulado

  cout <<endl<<"  *********";
  cout <<endl<<"  *** 1 ***";
  cout <<endl<<"  *********";

  NumLin = 0;
  NumLinhas = 0;
  if (str=="<RECEPCAO CANCELADA PELO USUARIO>" ) {
  getch();

      return 0;}

  if (str.size()!=0 )
    {

  cout <<endl<<"  *********";
  cout <<endl<<"  *** 2 ***";
  cout <<endl<<"  *********";


  vector_str=ponteiro.LeLinhaArqASCII(str);
  if (vector_str.size()==0)
  {
   cout << endl << "NAO FOI POSSIVEL ABRIR O ARQUIVO ["<<str<<"]"<< endl<< endl;
     getch();
      return 0;
  }
  NumLinhas = atoi(vector_str[0].c_str() );

  cout <<endl<<"  *********";
  cout <<endl<<"  *** 3 ***";
  cout <<endl<<"  *********";


  if (NumLinhas == 0 ) return 0;

do
{
  str = recebeStringRS232();
  if (str == "DTRQT"){
   cout << endl << "Recebido:   [" << str << "]";
   cout << endl << "Enviando... [" << vector_str[NumLin] << "]";
   EnviaStringRS232(vector_str[NumLin]);
   cout << endl << "Enviado:   [" << vector_str[NumLin] << "]";
   NumLin++;
   }else
   cout << endl << "Recebido:   [___" << str << "___]" << endl;
   if (str=="LOOP") NumLin = 0;

}while( str!="ENDL");

    }
  cout <<endl<<"  ***  Operacao CANCELADA pelo USUARIO  ***";
  cout <<endl<<"  <PRESSIONE QUALQUER TECLA PARA CONTINUAR>";
return 0;
}
