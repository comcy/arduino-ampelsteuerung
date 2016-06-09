#ifndef DEF_H
#define DEF_H

#include <stdint.h>
#include <Arduino.h>

/* Pinbelegung der Schieberegister fuer die LEDs */
#define DIN1 34      /* Serielle Daten In */
#define SCK1 35     /* Serieller Tackt */
#define CLK1 36     /* muss high gesetzt werden */
#define RCK1 37     /* Seriell Update -> Ausgaenge setzten */
    
/* Pinbelegung der Schieberegister fuer die Taster */
#define DOUT2  5    /* Serielle Daten Out */
#define PL2    6    /* Parallel Load  -> auf LOW setzten wenn Taster gelesen werden */
#define CLK2   7    /* Serieller Takt */

/* Bit-Masken fuer die Freigaben der Strassen  */
#define MASK_FG_RED         0b00010100000101000001010000010100 /* Fussgaenger gesperrt */
#define MASK_FG_GREEN       0b00001010000010100000101000001010 /* Fussgaenger frei*/

#define MASK_HS_RED         0b00000000100000000000000010000000 /* Hauptstrasse gesperrt*/
#define MASK_HS_GREEN       0b00000000001000000000000000100000 /* Hauptstrasse frei*/
#define MASK_HS_YELLOWRED   0b00000000110000000000000011000000 /* Hauptstrasse noch gesperrt*/
#define MASK_HS_YELLOW      0b00000000010000000000000001000000 /* Hauptstrasse noch frei*/

#define MASK_QS_RED         0b10000000000000001000000000000000 /* Querstrasse gesperrt*/
#define MASK_QS_GREEN       0b00100000000000000010000000000000 /* Querstrasse frei */
#define MASK_QS_YELLOWRED   0b11000000000000001100000000000000 /* Querstrasse noch gesperrt*/
#define MASK_QS_YELLOW      0b01000000000000000100000000000000 /* Querstrasse noch frei*/

#define MASK_ALL_RED        0b10010100100101001001010010010100 /* Alle Wege sind geperrt */


#define GREEN_TIME          5000 /* Gruenphasendauer in ms */
#define YELLOW_TIME         1000 /* Gelb- und Gelbrotphasendauer in ms */
#define RED_TIME            10000 /* maximale Rotphasendauer in ms */


#define FGA    0b0011011000110110   /* Maskierung der Taster Fussgaenger */ 
#define IS_QS  0b0000100000001000   /* Maskierung der Taster Induktionsschleife Querstrasse */
#define IS_HS  0b0100000001000000   /* Maskierung der Taster Induktionsschleife Hauptstrasse */


/* Definition von Datentypen */
typedef enum {green, yellow, yellowred, red}color_t;
typedef enum {ar, hs, qs, fg}street_t;

#endif
