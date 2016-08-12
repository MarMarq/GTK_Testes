
#include "rs232api2.h"

HANDLE handle_serial=NULL;
COMMTIMEOUTS timeoutespera;
DCB DCBrs232win;	/* declaracao da estrurura DCB para inicializacao da porta serial */

/* Rotina para inicializar a porta serial. Retorna TRUE,
	se for executada com sucesso, ou FALSE, se falhar */
BOOL Inicia_Serial_Port(
		int porta,		/* porta de comunicacao */
		BYTE ByteSize,	/* tamanho do caracter: 5 a 8 */
		BYTE StopBits,	/* numero de Stop Bits: ONESTOPBIT, ONE5STOPBITS ou TWOSTOPBITS */
		BYTE Parity,	/* paridade: NOPARITY, MARKPARITY, EVENPARITY ou ODDPARITY */
		int BaudRate,	/* taxa de transmissao: 2400, 9600, etc. */
		int timeout		/* timeout, em milissegundos */)
{
	timeoutespera.ReadIntervalTimeout=timeout;
	timeoutespera.ReadTotalTimeoutMultiplier=timeout;
	timeoutespera.ReadTotalTimeoutConstant=0;
	timeoutespera.WriteTotalTimeoutMultiplier=timeout;
	timeoutespera.WriteTotalTimeoutConstant=0;

	CloseHandle(handle_serial);
	handle_serial=INVALID_HANDLE_VALUE;
	if (porta==COM1)
		handle_serial= CreateFile("COM1",GENERIC_READ|GENERIC_WRITE,0,
											NULL,OPEN_EXISTING,0,NULL);
	if (porta==COM2)
		handle_serial= CreateFile("COM2",GENERIC_READ|GENERIC_WRITE,0,
											NULL,OPEN_EXISTING,0,NULL);
	if (porta==COM3)
		handle_serial= CreateFile("COM3",GENERIC_READ|GENERIC_WRITE,0,
											NULL,OPEN_EXISTING,0,NULL);
	if (porta==COM4)
		handle_serial= CreateFile("COM4",GENERIC_READ|GENERIC_WRITE,0,
											NULL,OPEN_EXISTING,0,NULL);
	if (handle_serial==INVALID_HANDLE_VALUE) return(FALSE);
	SetCommMask(handle_serial,EV_RXCHAR|EV_TXEMPTY|EV_ERR);
	SetCommTimeouts(handle_serial,&timeoutespera);
	GetCommState(handle_serial,&DCBrs232win);
	DCBrs232win.BaudRate=BaudRate;	/* 2400, 9600, 144400, etc. */
	DCBrs232win.ByteSize=ByteSize;	/* 5, 6, 7 ou 8 */
	DCBrs232win.Parity=Parity;			/* NOPARITY, MARKPARITY, EVENPARITY ou ODDPARITY */
	DCBrs232win.StopBits=StopBits;	/* ONESTOPBIT, ONE5STOPBITS ou TWOSTOPBITS */
	if (SetCommState(handle_serial,&DCBrs232win)) return(TRUE);
	else return(FALSE);
}

/* Rotina para liberar o uso da porta serial */
void libera_serial(void)
{
		CloseHandle(handle_serial);
}

/* Rotina para transmitir um caracter pela porta serial.
	Espera bit TXDE ficar ativado */
BOOL envia_caracter_serial(char *caracter)
{
	int checatransmissao;
	BOOL status;
	status=WriteFile(handle_serial,caracter,1,(LPDWORD)(&checatransmissao),NULL);
	if ((status==TRUE) && (checatransmissao==1)) return(TRUE);
	else return(FALSE);
}

/* Rotina para receber um caracter pela porta serial.
	Espera bit RXDA ficar ativado */
BOOL recebe_caracter_serial(char *caracter)
{
	int checatransmissao;
	BOOL status;
	status=ReadFile(handle_serial,caracter,1,(LPDWORD)(&checatransmissao),NULL);
	if ((status==TRUE) && (checatransmissao==1)) return(TRUE);
	else return(FALSE);
}


/* Rotina para transmitir um caracter pela porta serial.
	Nao espera bit TXDE ficar ativado */
BOOL envia_caracter_serial_TXDE(char *caracter)
{
	int mascara_event;
	BOOL status;
	WaitCommEvent(handle_serial,(LPDWORD)(&mascara_event),NULL);
	if (mascara_event&EV_TXEMPTY)
		{
			status=envia_caracter_serial(caracter);
			return(status);
		}
	else return(FALSE);
}

/* Rotina para receber um caracter pela porta serial.
	Nao espera bit RXDA ficar ativado */
BOOL recebe_caracter_serial_RXDA(char *caracter)
{
	int mascara_event;
	BOOL status;
	WaitCommEvent(handle_serial,(LPDWORD)(&mascara_event),NULL);
	if (mascara_event&EV_RXCHAR)
		{
			status=recebe_caracter_serial(caracter);
			return(status);
		}
	else return(FALSE);
}


