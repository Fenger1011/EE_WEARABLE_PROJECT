#include "ctrlTimer.h"
#include "u-BloxGNSS.h"

// Flag for showing new speed ping available
volatile bool isSpeedUpdated = false;

// Timer interupt handler
void TC3_Handler() {
  // If this interrupt is due to the compare register matching the timer count
  if (TC3->COUNT16.INTFLAG.bit.MC0 == 1) 
  {
    // Clear interupt flag
    TC3->COUNT16.INTFLAG.bit.MC0 = 1;
    
    // Timer interrupt service routine
    isSpeedUpdated = true;
  }
}

// Setup the timer.
void setupTimer(void) {
  // Disable the timer
  TC3->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
  while (TC3->COUNT16.SYNCBUSY.bit.ENABLE);    // Wait for clock domain sync

  GCLK->PCHCTRL[GCLK_TC3].reg = GCLK_PCHCTRL_CHEN | GCLK_PCHCTRL_GEN_GCLK0;
  while ( GCLK->SYNCBUSY.bit.GENCTRL0); // Wait for clock domain sync

	// Use match mode so that the timer counter resets when the count matches the compare register
	TC3->COUNT16.WAVE.reg = TC_WAVE_WAVEGEN_MFRQ;

	// Use the 16-bit timer and set prescaler
	TC3->COUNT16.CTRLA.reg = TC_CTRLA_MODE_COUNT16 | TC_CTRLA_PRESCALER_DIV1024 | TC_CTRLA_PRESCSYNC_PRESC;
	
	// Enable the compare interrupt
	TC3->COUNT16.INTENSET.reg = TC_INTENSET_MC0;

  NVIC_DisableIRQ(TC3_IRQn);
  NVIC_SetPriority(TC3_IRQn, 7);  
}

// Start the timer
void startTimer(void) {
  NVIC_EnableIRQ(TC3_IRQn);

  // Enable the timer
  TC3->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
  while (TC3->COUNT16.SYNCBUSY.bit.ENABLE);    // Wait for clock domain sync
}

// Flag for new speed available to be used in main loop
bool newSpeedAvailable() {
  if (isSpeedUpdated) {
    isSpeedUpdated = false;
    return true;
  }
  return false;
}
