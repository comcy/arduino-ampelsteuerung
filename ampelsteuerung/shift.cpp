#include "shift.h"

/* Funktionsprototypen privater Funktionen */
void long2char(long in, uint8_t *out);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);




/* Funktion um die Schieberegister zu initalisieren */
/* Hierbei werden die dementsprechenden Pins eingestellt */
void init_shiftRegister(void)
{
    /* Schieberegister out */
    pinMode(DIN1, OUTPUT);
    pinMode(SCK1, OUTPUT);
    pinMode(CLK1, OUTPUT);
    pinMode(RCK1, OUTPUT);
    
    digitalWrite(DIN1, LOW);
    digitalWrite(SCK1, LOW);
    digitalWrite(RCK1, LOW);
    digitalWrite(CLK1, HIGH);
    
    /* Schieberegister in */
    pinMode(DOUT2, INPUT);
    pinMode(PL2, OUTPUT);
    pinMode(CLK2, OUTPUT);
    
    digitalWrite(PL2, LOW);
    digitalWrite(CLK2, LOW);
    
}


/* Funktion um eine long-Variable in vier Char-Variablen umzuwandeln */
/* Der Funktion wird eine Vorzeichenlose long-Variable sowie ein Zeiger auf char-Array*/
/* Das Char-Array muss mindestens 4 Elemente enthalten */
void long2char(uint32_t in, uint8_t *out)
{
    uint32_t temp;
    
    temp = in;
    out[0] = (uint8_t) (temp & 0x000000ff);
    
    temp = in;
    out[1] = (uint8_t) ( (temp >> 8) & 0x000000ff);
    
    temp = in;
    out[2] = (uint8_t) ( (temp >> 16) & 0x000000ff);
    
    temp = in;
    out[3] = (uint8_t) ( (temp >> 24) & 0x000000ff);
}


/* Funktion um ein Char-Array  mit 4 Elementen in eine Vorzeichenlose Long-Variable umzuwandeln */
/* Der Funktion wird ein Zeiger auf ein Array mit mindestens 4 Elementen uebergeben */
/* Die Funktion gibt die Umgewandelte Long-Variable zurueck */  
uint32_t char2long(uint8_t *in)
{
   uint32_t u32_return = 0;
   uint8_t i;
   
   for(i=0; i<4; i++)
   {
      u32_return |= ( (long) (in[i] << i));
   }
   
   return u32_return;
}


/* Diese Funktion um die LEDs zu beschreiben */
/* Die Daten - welche LEDs aktiviert bzw deaktiviert werden - werden aus dem Zentralen */
/* Datenspeicher entnommen */
void writeLed(void)
{
    uint8_t i, u8_data[4];
    
    /* 32 Bit Variable in vier 8 Bit Variablen umwandel */
    long2char(central_data.ampel_alle, u8_data);
    
    digitalWrite(RCK1, LOW);
    for(i=0; i<4; i++)
    {
        shiftOut(DIN1, SCK1, LSBFIRST, u8_data[i]);
    }
    digitalWrite(RCK1, HIGH);
}


/* Funktion fuer das auslesen der Taster */
/* Diese Funktion wird zyklisch in einem Task alle 50ms aufgerufen */
/* Die Funktion gibt nichts zurueck */
/* Der Funktion muss ein integer und ein Zeiger auf eine integer- */
/* Variabel uebergeben werden. Dies ist eine Vorgabe der Funktion */
/* createTask() */
void readSwitch(int a, void *b)
{
    uint8_t u8_data[2];
    uint16_t i, temp = 0;
    
    
    digitalWrite(PL2, HIGH);    /* Paralell Input load */
    for(i=0; i<2; i++)
        u8_data[i] = shiftIn(DOUT2, CLK2, MSBFIRST);
        
    digitalWrite(PL2, LOW);
    
    /* Daten in Zentralen Datenspeicher schreiben */
    central_data.taster |= (uint16_t) (u8_data[1] << 8);
    central_data.taster |= (uint16_t) u8_data[0];
}



/* Diese Funktion wurde aus der Arduino Umgebung heraus kopiert */
/* Der Funktion muss uebergeben werden an welchen Pin sich der */
/* der Datenausgang befindet, an welchem Pin sich der Taktausgang */
/* befindet und in welcher reihenfolge die Bits rausgeschoben werden */
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
	uint8_t value = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i) {
		digitalWrite(clockPin, HIGH);
		if (bitOrder == LSBFIRST)
			value |= digitalRead(dataPin) << i;
		else
			value |= digitalRead(dataPin) << (7 - i);
		digitalWrite(clockPin, LOW);
	}
	return value;
}
