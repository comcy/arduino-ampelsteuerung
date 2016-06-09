#include "trafficLight.h"

/* Funktion fuer die Steuerung der Zweifeldampeln */
/* Der Rueckgabewert der Funktion ist der naechste Zustand der Ampel */
street_t zweiFeldAmpel(void)
{
    static color_t aktColor = red;
    static uint32_t cntTime = 0;
    uint32_t dT;
    street_t s_return;
    
    /* Berechnung der Zeitdifferenz seit dem letzten aufruf */
    dT = millis() - cntTime;
    if( aktColor == red )
    {
        /* Ampel von rot auf gruen schalten */
        central_data.ampel_alle &= ~MASK_FG_RED;
        central_data.ampel_alle |= MASK_FG_GREEN;
        writeLed();
        cntTime = millis();
      
        /* Naechster Zustand ist "Fussgaenger" */
        aktColor = green;
        s_return = fg;
    }
    else if( (aktColor == green) && ( dT > GREEN_TIME) )
    {
        /* ampeln von gruen auf rot schalten */
        central_data.ampel_alle &= ~MASK_FG_GREEN;
        central_data.ampel_alle |= MASK_FG_RED;
        writeLed();
      
        /* Naechster Zustand ist "alleRot" */
        aktColor = red;
        s_return = ar;
        
        /* Taster-Werte loeschen */
        central_data.taster &= ~FGA;
    }
    else s_return = fg; /* Zustand ist Weiterhin Fussgaenger */
  
    return s_return;  
}


/* Funktion fuer die Steuerung der Dreifeldampeln */
/* Der Funktion muss uebergeben werde ob die Haupt- oder die Querstrasse gesteuert wird */
/* Die Funktion gibt den naechsten Zustand der Ampel zurueck */
street_t dreiFeldAmpel(street_t street)
{
    /* Variablendeklaration */
    static color_t aktColor = red;
    static uint32_t cntTime = 0; 
    uint32_t dT;
    street_t s_return; 
    
    /* Zeitdifferenz berechnen */
    dT = millis() - cntTime;
    
    if(aktColor == red)
    {
      /* Ampel von rot auf rot-gelb schalten */
      if(street == hs)
      {
        central_data.ampel_alle &= ~MASK_HS_RED;
        central_data.ampel_alle |= MASK_HS_YELLOWRED;
        s_return = hs;
      }
      else
      {
        central_data.ampel_alle &= ~MASK_QS_RED;
        central_data.ampel_alle |= MASK_QS_YELLOWRED;
        s_return = qs;
      }
      writeLed();
      cntTime = millis();
      aktColor = yellowred; /* Naechste Farbe ist gelbrot */
    }
    else if( (aktColor ==  yellowred) && ( dT > YELLOW_TIME) )
    {
        /* von rot-gelb auf gruen schalten */
        if(street == hs)
        {
            central_data.ampel_alle &= ~MASK_HS_YELLOWRED;
            central_data.ampel_alle |= MASK_HS_GREEN;
            s_return = hs;
        }
        else
        {
            central_data.ampel_alle &= ~MASK_QS_YELLOWRED;
            central_data.ampel_alle |= MASK_QS_GREEN;
            s_return = qs;
        }
        writeLed();
        cntTime = millis();
        aktColor = green;
    }
    else if( (aktColor ==  green) && (dT > GREEN_TIME) )
    {
        /* von gruen auf gelb schalten */
        if(street == hs)
        {
            central_data.ampel_alle &= ~MASK_HS_GREEN;
            central_data.ampel_alle |= MASK_HS_YELLOW;
            s_return = hs;
        }
        else
        {
            central_data.ampel_alle &= ~MASK_QS_GREEN;
            central_data.ampel_alle |= MASK_QS_YELLOW;
            s_return = qs;
        }        
        writeLed();
        cntTime = millis();
        aktColor = yellow;
    }
    else if((aktColor ==  yellow) && (dT > YELLOW_TIME))
    {
        /* von gelb auf rot schalten */
        if(street == hs)
        {
            central_data.ampel_alle &= ~MASK_HS_YELLOW;
            central_data.ampel_alle |= MASK_HS_RED;
            central_data.taster &= ~ IS_HS;
        }
        else
        {
            central_data.ampel_alle &= ~MASK_QS_YELLOW;
            central_data.ampel_alle |= MASK_QS_RED;
            central_data.taster &= ~ IS_QS;
        }
        writeLed();
        cntTime = millis();
        
        aktColor = red;
        s_return = ar; 
    }
    else
    {
        if(street == hs) s_return = hs;
        else s_return = qs;
    }
    
    return s_return;
}

/* Funktion fuer die Bestimmung des naechsten */
/* Zustandes der Ampel */
/* Der Funktion muss die Zeitdifferenz seit der */ 
/* Letzten freigabe einer Strasse uebergeben werden */
/* Der Funktion muss die zuletzt freigebene Strasse */ 
/*ueberbegeben werden um eine Blockierun zu verhindern */
/* Die Funktion gibt den naechsten Zustand der Ampel zurueck */
street_t alleRot(unsigned int dT, street_t lastStreet)
{
    street_t s_return;
    
    if ( (central_data.taster & FGA) && (lastStreet != fg) ) s_return = fg;
    else if( (central_data.taster & IS_HS) && (lastStreet != hs) ) s_return = hs; 
    else if( (central_data.taster & IS_QS) && (lastStreet != qs) ) s_return = qs; 
    else if( dT > RED_TIME ) 
    {
        if( lastStreet != hs ) s_return = hs;
        else s_return = qs;
    }
    else s_return = ar; /* Ampel bleibt rot */
    
    return s_return;
}
