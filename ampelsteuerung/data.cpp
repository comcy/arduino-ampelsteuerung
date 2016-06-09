#include "data.h"

central_data_t central_data;

/* Funktion um den Zentralen Datenspeicher zu initalisieren */
void init_central_data(void)
{
    uint8_t i;
    
    central_data.ampel_alle = 0;
    central_data.taster = 0;
    for(i=0; i<4; i++)
        central_data.sr_out[i] = 0;   
}
