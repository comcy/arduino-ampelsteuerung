#include "def.h"
#include "shift.h"
#include "data.h"
#include "trafficLight.h"

/* Varibalen */
int task_var;

void setup(void)
{
    /* Initalisierung */
    init_central_data();
    init_shiftRegister();
    
    /* Alle Ampeln auf Rot Schalten */
    central_data.ampel_alle = MASK_ALL_RED;
    writeLed();
    
    /* Task der alle 50 ms Taster liest */
    createTask(readSwitch, 50, TASK_ENABLE, &task_var);   
}

void loop(void)
{
  static street_t aktState = ar, lastState = qs;
  static unsigned int cntTime = 0;
   
  /* Zustandsautomat */
  switch(aktState)
  {
    case ar:
        /* Zustand: Alle Rot */
        aktState = alleRot( (millis() - cntTime), lastState );
    break;
    
    case hs:
        /* Zustand: Freigabe der Hauptstrasse */
        aktState = dreiFeldAmpel(hs);
        lastState = hs;     /* hs als letzten Zustand abspeichern */
        cntTime = millis(); /* Zeit festhalten */
    break;
    
    case qs:
        /* Zustand: Freigabe der Querstrasse */
        aktState = dreiFeldAmpel(qs);
        lastState = qs;     /* qs als letzten Zustand abspeichern */
        cntTime = millis(); /* Zeit festhalten */
    break;
    
    case fg:
        /* Zustand: Freigabe des Fussgaengeruebergangs */
      aktState = zweiFeldAmpel();
      cntTime = millis();   /* Zeit festhalten */
      lastState = fg;       /* fg als letzten Zustand abspeichern */
    break;
  
    default: 
    break;
  }

}
