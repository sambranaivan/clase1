#include "sdCard.h"
#include "ff.h"

#define FILENAME "ciaa.txt"

/*==================[internal data declaration]==============================*/

static FATFS fs;           /**< FatFs work area needed for each volume */
static FIL fp;  


int escribirSD(char* result)
{
	UINT nbytes;
	  /* ------ PROGRAMA QUE ESCRIBE EN LA SD ------- */
	char * registro = result;
	   /* Give a work area to the default drive */
	   if( f_mount( &fs, "", 0 ) != FR_OK ){
	      /* If this fails, it means that the function could
	       * not register a file system object.
	       * Check whether the SD card is correctly connected */
	   }

	   /* Create/open a file, then write a string and close it */
	   if( f_open( &fp, FILENAME, FA_WRITE | FA_OPEN_APPEND ) == FR_OK ){
	      //f_write( &fp, "Hola mundo\r\n", 12, &nbytes );
		   f_write( &fp, registro, 70, &nbytes );

	      f_close(&fp);

	      if( nbytes == 70 ){
	         /* Turn ON LEDG if the write operation was successful */
	         //gpioWrite( LEDG, ON );
	         return 1;//para ok

	      }
	   } else{
	      /* Turn ON LEDR if the write operation was fail */
	      //gpioWrite( LEDR, ON );
	      return 0;//para error
	   }
	}

