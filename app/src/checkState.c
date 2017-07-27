#include "checkState.h"
#include "sapi.h"
#define PIN_1 GPIO0
#define PIN_2 GPIO2
#define PIN_3 GPIO4
/*==================[definiciones de funciones internas]=====================*/
int check_state(int p1,int p2, int p3)
{
    
    if(gpioRead(PIN_1) == p1 & gpioRead(PIN_2) == p2 & gpioRead(PIN_3) == p3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int show_state()
{
	 if(gpioRead(PIN_1)){gpioWrite(LED1,ON);}
    else{gpioWrite(LED1,OFF);}
     if(gpioRead(PIN_2)){gpioWrite(LED2,ON);}
     else{gpioWrite(LED2,OFF);}
      if(gpioRead(PIN_3)){gpioWrite(LED3,ON);}
      else{gpioWrite(LED3,OFF);}    
}