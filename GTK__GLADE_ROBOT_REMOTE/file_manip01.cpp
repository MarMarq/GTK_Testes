
#include "file_manip01.h"

using namespace std;

vector <string> MANIPULA_ARQUIVO::LeLinhaArqASCII(string NomeArqu )
{ string str;
  vector <string> linha;
  ifstream f_read;
  char *CHARNomeArqu;
  CHARNomeArqu = new char [NomeArqu.size()];
  strcpy( CHARNomeArqu , NomeArqu.c_str() );

  f_read.open (CHARNomeArqu, ios::in );

  while (f_read.good())     // loop while extraction from file is possible
  {
      getline( f_read, str);
      linha.push_back(str);
  }
  f_read.close();
  return linha;}
// --------------------------------------------------------------------------------
vector <string> MANIPULA_ARQUIVO::LeLinhaArqASCII(char *NomeArqu )
{
  vector <string> linha;
  string strNomeArqu = (string)NomeArqu;

  linha = LeLinhaArqASCII ( strNomeArqu );
  return linha;}
//*********************************************************************************
//*********************************************************************************
bool MANIPULA_ARQUIVO::EscreveArq_Linhas_ASCII( string NomeArqu , int MODO , vector <string> dados, int TERMINACAO  )
{
    unsigned int i;
    ofstream f_write;
    ifstream f_read;
    string::iterator it;

/*      #define ABRE_LEITURA 0
        #define ABRE_NOVO 1
        #define ABRE_NOVO_CHECA_EXISTENCIA 2
        #define ABRE_ESCRITA_DESCART_CONTEUDO 3
        #define ABRE_ESCRITA_CHECA_EXISTENCIA 4
        #define ABRE_ESCRITA_ADICIONA_AOFINAL 5         */


    if ( (MODO==ABRE_NOVO)||(MODO==ABRE_ESCRITA_DESCART_CONTEUDO) )
    {
        f_write.open(NomeArqu.c_str(), ios::trunc );
          for (i = 0 ; i < dados.size() ; i++)
            {
            if (TERMINACAO == DOSWINDOWS)
            {
            dados[i].push_back(13);  // Caracter '\r' (CR)
            dados[i].push_back(10);  // Caracter '\n' (LF)
            }
            if ( (TERMINACAO == UNIX_LINUX) || (TERMINACAO == MAC_OS_V9) )
            {
            dados[i].push_back(10);  // Caracter '\n' (LF)
            }
            if ( (TERMINACAO == MAC_OS_X) || (TERMINACAO == ROBORV2AJ) )
            {
            dados[i].push_back(13);  // Caracter '\r' (CR)
            }
            f_write.write( dados[i].c_str() , dados[i].size() );
            }
        f_write.close();
        return true;
    }else{
         cout << "Nao possivel abrir criar o arquivo!!" << endl;
         return false;
         }

    if ( (MODO==ABRE_NOVO_CHECA_EXISTENCIA)||(MODO==ABRE_ESCRITA_CHECA_EXISTENCIA) )
    {
        f_read.open(NomeArqu.c_str(), ios::in );
        if (f_read.is_open())
        {
        cout << "O Arquivo [" << NomeArqu << "] Ja existe!!" << endl << "Acesso NEGADO!!" << endl;
        f_read.close();
        return false;
        }else{
             f_write.open(NomeArqu.c_str(), ios::trunc );
             for (i = 0 ; i < dados.size() ; i++)
            {
            if (TERMINACAO == DOSWINDOWS)
            {
            dados[i].push_back(13);  // Caracter '\r' (CR)
            dados[i].push_back(10);  // Caracter '\n' (LF)
            }
            if ( (TERMINACAO == UNIX_LINUX) || (TERMINACAO == MAC_OS_V9) )
            {
            dados[i].push_back(10);  // Caracter '\n' (LF)
            }
            if ( (TERMINACAO == MAC_OS_X) || (TERMINACAO == ROBORV2AJ) )
            {
            dados[i].push_back(13);  // Caracter '\r' (CR)
            }
            f_write.write( dados[i].c_str() , dados[i].size() );
            }
          f_write.close();
        return true;
        }
    }
return false;
}
// --------------------------------------------------------------------------------
bool MANIPULA_ARQUIVO::EscreveArq_Linhas_ASCII(char *NomeArqu , int MODO , vector <string> dados, int TERMINACAO )
{
     bool rf;
     string strNomeArqu = (string)NomeArqu;

    rf = EscreveArq_Linhas_ASCII( strNomeArqu , MODO , dados, TERMINACAO );
    return rf;
}
// --------------------------------------------------------------------------------
bool MANIPULA_ARQUIVO::EscreveArq_Linhas_ASCII(const char *NomeArqu , int MODO , vector <string> dados, int TERMINACAO )
{
     bool rf;
     string strNomeArqu = (string)NomeArqu;

    rf = EscreveArq_Linhas_ASCII( strNomeArqu , MODO , dados, TERMINACAO );
    return rf;
}
//*********************************************************************************
//*********************************************************************************
