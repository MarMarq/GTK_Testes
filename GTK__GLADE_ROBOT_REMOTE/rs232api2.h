//---------------------------------------------------------------------------
#ifndef RS232API2H
#define RS232API2H
//---------------------------------------------------------------------------

#include <windows.h>
#include <winbase.h>

//#define COM1 0x378
#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

/* Rotina para inicializar a porta serial. Retorna TRUE,
	se for executada com sucesso, ou FALSE, se falhar */
BOOL Inicia_Serial_Port(
		int porta,		/* porta de comunicacao */
		BYTE ByteSize,	/* tamanho do caracter: 5 a 8 */
		BYTE StopBits,	/* numero de Stop Bits: ONESTOPBIT, ONE5STOPBITS ou TWOSTOPBITS */
		BYTE Parity,	/* paridade: NOPARITY, MARKPARITY, EVENPARITY ou ODDPARITY */
		int BaudRate,	/* taxa de transmissao: 2400, 9600, etc. */
		int timeout		/* timeout, em milissegundos */);

/* Rotina para liberar o uso da porta serial */
void libera_serial(void);

/* Rotina para transmitir um caracter pela porta serial.
	Espera bit TXDE ficar ativado */
BOOL envia_caracter_serial(char *caracter);

/* Rotina para receber um caracter pela porta serial.
	Espera bit RXDA ficar ativado */
BOOL recebe_caracter_serial(char *caracter);

/* Rotina para transmitir um caracter pela porta serial.
	Nao espera bit TXDE ficar ativado */
BOOL envia_caracter_serial_TXDE(char *caracter);

/* Rotina para receber um caracter pela porta serial.
	Nao espera bit RXDA ficar ativado */
BOOL recebe_caracter_serial_RXDA(char *caracter);

#endif
