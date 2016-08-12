//---------------------------------------------------------------------------
#ifndef RS232W_FN1H
#define RS232W_FN1H
//---------------------------------------------------------------------------
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>

#include "rs232api2.h"

using namespace std;

string recebeStringRS232();
int EnviaStringRS232( string str );
void EnviaStringRS232Interface();
void VisualizaRX_Extratificada();
void VisualizaRX_Frases();
int EnviaArquivo();

#endif
