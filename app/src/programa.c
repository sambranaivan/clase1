/*============================================================================
 * Licencia: 
 * Autor: 
 * Fecha: 
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "programa.h"   // <= su propio archivo de cabecera
#include "sapi.h"       // <= Biblioteca sAPI
#include "chip.h"       // <= Biblioteca LPCOpen, capa chip (del fabricante NXP)

/*==================[definiciones y macros]==================================*/

// Para configurar cualquier pin hay que saber todos estos datos:
// Los que van en SCU: SCU_PORT, SCU_PIN, SCU_FUNC y los que van en GPIO:
// GPIO_PORT, GPIO_PIN

// Ver en sapi_gpio.c el pin que sAPI llama GPIO0 (por la serigrafía de la
// placa EDU-CIAA) es:

// SCU
#define GPIO0_SCU_PORT   6
#define GPIO0_SCU_PIN    1
#define GPIO0_SCU_FUNC   SCU_MODE_FUNC0

// GPIO
#define GPIO0_GPIO_PORT  3
#define GPIO0_GPIO_PIN   0

// Interrupt
#define PININT_INDEX         0                  // PININT index used for GPIO mapping
#define PININT_IRQ_HANDLER   GPIO0_IRQHandler   // GPIO interrupt IRQ function name
#define PININT_NVIC_NAME     PIN_INT0_IRQn      // GPIO interrupt NVIC interrupt name


///GPIO DE CONTROL
#define PIN_1 GPIO0
#define PIN_2 GPIO2
#define PIN_3 GPIO4
int STATE = 12;
gpioMap_t LEDCONTROL = LEDB;

/*==================[definiciones de datos internos]=========================*/


/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/
char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}


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


/*==================[Maquina de Estados]====================*/
void STATE_MACHINE()
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

              gpioWrite(LEDB,OFF);
              gpioWrite(LEDG,!gpioRead(PIN_1));
              LEDCONTROL = LEDG;
            ///SEÑAL SINCRONIZADA IR AL ESTADO INICIAL
              
              STATE = 0;
          }
      break;
         case 13:
              gpioWrite(LEDG,OFF);
              gpioWrite(LEDR,!gpioRead(PIN_1));
              //ESTADO DE ERROR 
              LEDCONTROL = LEDR;
      break;
  	}

}

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

// Handle interrupt from GPIO pin or GPIO pin mapped to PININT
void PININT_IRQ_HANDLER(void)
{
   Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX) );
    STATE_MACHINE();
   gpioToggle(LEDCONTROL);//LEd de conntrol de interrupciones
  
    if(gpioRead(PIN_1)){gpioWrite(LED1,ON);}
    else{gpioWrite(LED1,OFF);}
      if(gpioRead(PIN_2)){gpioWrite(LED2,ON);}
      else{gpioWrite(LED2,OFF);}
      if(gpioRead(PIN_3)){gpioWrite(LED3,ON);}
      else{gpioWrite(LED3,OFF);}
      
      
      
    
   
}

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){
    
    
   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();   
   
   /* Configuración de GPIO0 de la EDU-CIAA-NXP como entrada con pull-up */
   gpioConfig( GPIO0, GPIO_INPUT_PULLUP );
    
    /*CONFIGURAR GPIO 1,2,3*/

    gpioConfig( PIN_2, GPIO_INPUT);
    gpioConfig( PIN_3, GPIO_INPUT);
    
    i2cConfig( I2C0, 100000 );
    uartConfig( UART_USB, 115200 );
    
    gpioWrite(LEDB,gpioRead(PIN_1));
   // Comienzo de funciones LPCOpen para configurar la interrupción

   // Configure interrupt channel for the GPIO pin in SysCon block
   Chip_SCU_GPIOIntPinSel( PININT_INDEX, GPIO0_GPIO_PORT, GPIO0_GPIO_PIN );

   // Configure channel interrupt as edge sensitive and falling edge interrupt
   Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX) );
   Chip_PININT_SetPinModeEdge( LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX) );
   Chip_PININT_EnableIntLow( LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX) );
   Chip_PININT_EnableIntHigh( LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX) );

   // Enable interrupt in the NVIC
   NVIC_ClearPendingIRQ( PININT_NVIC_NAME );
   NVIC_EnableIRQ( PININT_NVIC_NAME );

   // Fin de funciones LPCOpen
   
   
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {      
      // No hace nada
   } 

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta 
   // directamenteno sobre un microcontroladore y no es llamado/ por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

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



/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/
