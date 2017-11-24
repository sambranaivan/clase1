
#include "stateMachine.h"
#include "checkState.h"
#include "obtenerDatos.h"
#include "sapi.h"
/*==================[Maquina de Estados]====================*/
int STATE = 12;
gpioMap_t LEDCONTROL = LEDB;
void stateMachine()
{
    
  switch (STATE)
  	{
  		case 0:
  			if(check_state(1,0,0)){
  				STATE = 1;
  			}
        else
          {
            STATE = 13;
          }
  		break;
  		case 1:
  			if(check_state (0,0,0)){
  				STATE = 2;
  			}
        else
          {
            STATE = 13;
          }
  		break;
  		case 2:
  			if(check_state(1,1,0)){
  				STATE = 3;
  			}
        else
          {
            STATE = 13;
          }
  		break;
  		case 3:
  			if(check_state(0,1,0)){
  				STATE = 4;
  			}
        else
          {
            STATE = 13;
          }
  		break;
  		case 4:
  			if(check_state(1,0,0)){
  				STATE = 5;
  			}
        else
          {
            STATE = 13;
          }
  		break;
  		case 5:
  			if(check_state(0,0,0)){
  				STATE = 6;
  			}
        else
          {
            STATE = 13;
          }
  		break;
  		case 6:
  			if(check_state(1,0,0)){
  				STATE = 7;
  			}
        else
          {
            STATE = 13;
          }
  		break;
  		case 7:
  			if(check_state(0,0,0)){
  				STATE = 8;
  			}
        else
          {
            STATE = 13;
          }
  		break;
  		case 8:
  			if(check_state(1,0,0)){
  				STATE = 9;
  			}
        else
          {
            STATE = 13;
          }
  		break;
  		case 9:
  			if(check_state(0,0,0)){
  				STATE = 10;
  			}
        else
          {
            STATE = 13;
          }
  		break;
  		case 10:
  			if(check_state(1,0,1)){
  				STATE = 11;
  			}
        else
          {
            STATE = 13;
          }
  		break;
  		case 11:
  			if(check_state(0,0,1)){
  				STATE = 0;
                obtenerDatos();
  			}
        else
          {
            STATE = 13;
          }
  		break;
      case 12:
          if(check_state(0,0,1))
          {

              // gpioWrite(LEDB,OFF);
              // gpioWrite(LEDG,!gpioRead(PIN_1));
              LEDCONTROL = LEDG;
            //SEÑAL SINCRONIZADA IR AL ESTADO INICIAL
              
              STATE = 0;
          }
      break;
         case 13:
              // gpioWrite(LEDG,OFF);
              // gpioWrite(LEDR,!gpioRead(PIN_1));
              //ESTADO DE ERROR 
              LEDCONTROL = LEDR;
      break;
  	}

}
