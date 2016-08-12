//---------------------------------------------------------------------------
#ifndef FILE_MANIP01H
#define FILE_MANIP01H
//---------------------------------------------------------------------------
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class MANIPULA_ARQUIVO
{
public:

#define ABRE_LEITURA 0
#define ABRE_NOVO 1
#define ABRE_NOVO_CHECA_EXISTENCIA 2
#define ABRE_ESCRITA_DESCART_CONTEUDO 3
#define ABRE_ESCRITA_CHECA_EXISTENCIA 4
#define ABRE_ESCRITA_ADICIONA_AOFINAL 5

#define INSERE_CRLF 0
#define INSERE_LF 1
#define INSERE_CR 2

#define DOSWINDOWS INSERE_CRLF
#define UNIX_LINUX INSERE_LF
#define MAC_OS_X   INSERE_CR
#define MAC_OS_V9  INSERE_LF
#define ROBORV2AJ  INSERE_CR

/*-----------------------------------------------------
  ----  Método LeLinhaArqASCII ------------------------
  Lê arquivo ASCCII linha a  linha e  armazena a linha
  dentro de um vector <string> que é retorno do método
  -----------------------------------------------------
Sobrecarga de Médotos para a Função LeLinhaArqASCII          */
vector <string> LeLinhaArqASCII( string NomeArqu );
vector <string> LeLinhaArqASCII(  char *NomeArqu );
/*-----------------------------------------------------
  ----  Método EscreveArq_Linhas_ASCII ----------------
  Lê arquivo ASCCII linha a  linha e  armazena a linha
  dentro de um vector <string> que é retorno do método
  -----------------------------------------------------
Sobrecarga de Médotos para a Função EscreveArq_Linhas_ASCII  */
bool EscreveArq_Linhas_ASCII( string NomeArqu , int MODO , vector <string> dados , int TERMINACAO);
bool EscreveArq_Linhas_ASCII(  char *NomeArqu , int MODO , vector <string> dados , int TERMINACAO);
bool EscreveArq_Linhas_ASCII( const char *NomeArqu , int MODO , vector <string> dados , int TERMINACAO);
};
//*********************************************************************************
//*********************************************************************************
#endif
