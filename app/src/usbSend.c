#include "usbSend.h"
#include "sapi.h"

void usbSend(char* result)
{
		char * registro = result;

        uartWriteString(UART_USB, registro);
}