#ifndef UBLOX_GNSS_H
#define UBLOX_GNSS_H

#include <Arduino.h>

// Initialize GNSS
void init_GNSS(int setNavFreq);

// Get ground speed
double getSpeed(void);

#endif /* UBLOX_GNSS_H*/