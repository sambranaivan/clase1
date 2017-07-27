#include "obtenerRegistro.h"
#include "sapi.h"
#include "itoa.h"

char* obtenerRegistros(char* result)
{
	   char buff[10];
	uint16_t muestra = 0;
	char * registro = result;
  int j;
  //limpio el registro antes de cargar de nuevo
   for(j = 0; j<=70; j++){registro[j] = 0;}


	muestra = adcRead( AI0 );
  //  muestra = adcRead( CH1 );


	int i;
	for(i=0;i<=12;i++)
	{
    //CONVIERNO SEÑAL A STRING
     itoa(muestra + i*5,buff,10);

        	if(i == 0)
          {
          		strcpy(registro,"\r\n");
          		strcat(registro,buff);
          }
        	else
         	{
          		strcat(registro,buff);
          }


        	if(i != 12)
          {
              strcat(registro,",");
          }

    	}
	   return result;
	}