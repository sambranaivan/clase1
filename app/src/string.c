#include "string.h"

char *strcat (char *dest, const char *src)
  {
    const char *p;
    char *q;

    for (q = dest; *q != '\0'; q++)
       ;
    
    for(p = src; *p != '\0'; p++, q++)
       *q = *p;
    
    *q = '\0';

    return dest;
  }
