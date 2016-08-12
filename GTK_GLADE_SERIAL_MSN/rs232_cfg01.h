//---------------------------------------------------------------------------
#ifndef RS232_CFG01H
#define RS232_CFG01H
//---------------------------------------------------------------------------

#include "file_manip01.h"
#include "rs232W_fn01.h"

vector <string> LeRS232Conf(string str);
bool ConfiguraSerial(string buffPORTA, string buffDATABITS, string buffSTOPBIT,
                    string buffPAR,   string buffTAXA,     string buffTIMEOUT);

vector <string> RS232UserConfig(vector <string> config);


#endif
