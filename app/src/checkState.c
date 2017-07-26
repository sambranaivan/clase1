#include "checkState.h"
#include "sapi.h"
// #include "sapi.h"
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