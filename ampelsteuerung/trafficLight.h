#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "def.h"
#include "data.h"
#include "shift.h"
#include <stdint.h>

street_t zweiFeldAmpel(void);
street_t dreiFeldAmpel(street_t aktStreet);
street_t alleRot(unsigned int dT, street_t lastState);

#endif
