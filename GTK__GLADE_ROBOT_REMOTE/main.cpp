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
  char c;
  string name;

  inicializa_serial(COM1, 8, ONESTOPBIT, NOPARITY, 9600, 100);

  ifstream is;
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
