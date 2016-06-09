#ifndef DATA_H
#define DATA_H

#include "def.h"


/* Definition des Datentyps central_data_t */
typedef struct 
{
    uint32_t ampel_alle;    /* Wert aller LEDs -> 1 Bit entspricht einer LED */
    uint16_t taster;        /* Wert aller Taster -> 1 Bit entspricht einem Taster */
    uint8_t sr_out[4];      /* Zwischenvariable für das Versenden ueber das Schieberegister */
}central_data_t;

/* Dem Compiler mitteilen, dass eine Instanz einer Variable vom Datentypt */
/* central_data_t exisitert */
/* Diese muss Global sein damit verschiedene Funktionen darauf zugreifen koennen */
extern central_data_t central_data;

void init_central_data(void);


#endif
