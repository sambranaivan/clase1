#include "obtenerDatos.h"
#include "sapi.h"

void obtenerDatos()
{
    uint8_t dataToReadBuffer;
    uint8_t Address;
    char xresult;
    char buff[10];
    int buffsize = 4;
   dataToReadBuffer = 0x00;
    Address = 0x03;
    //Address = 0x00;
   i2cRead( I2C0, Address,
            &dataToReadBuffer, 1, TRUE,
            &xresult, buffsize, TRUE );
    
    //itoa(xresult,buff,10);
    uartWriteString(UART_USB,&xresult);
    //uartWriteString(UART_USB,buff);

}