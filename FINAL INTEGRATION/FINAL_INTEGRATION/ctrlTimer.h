/*
 * Example of how to setup a timer of the SAMD51 in compare mode
 * The example uses Timer 3 (TC3)
 * Created by: Simon Lind Kappel - slk@ece.au.dk, simon@lkappel.dk - 2024
*/

#ifndef CTRL_TIMER_H
#define CTRL_TIMER_H

#include <Arduino.h>

#define GCLK_TC3	26

// Make groundSpeedReady variable globally accessible
extern volatile bool isSpeedUpdated;

// Setup the timer.
void setupTimer(void);

// Start the timer
void startTimer(void);

// Flag for new speed available
bool newSpeedAvailable();

#endif /* CTRL_TIMER_H */
