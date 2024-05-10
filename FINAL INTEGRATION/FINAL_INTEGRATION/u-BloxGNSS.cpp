#include <SparkFun_u-blox_GNSS_Arduino_Library.h> //U-blox GNSS library
#include <stdint.h>
SFE_UBLOX_GNSS myGNSS;

double getSpeed(void) {
  double velocity_kmh = myGNSS.getGroundSpeed() * 0.0036; //Get speed in kmh from mm/s

  // Datafiltering: If the speed is below 1kmh, assume no movement ****** SLÅET FRA GRUNDET OLED TESTING ******
  /*
  if (velocity_kmh < 1.0) {
    velocity_kmh = 0;
  }
  */ 

  // Debugging
  Serial.print("Ground Speed kmh: ");
  Serial.println(velocity_kmh);

  return velocity_kmh;
}

void init_GNSS(int setNavFreq) {
  if (myGNSS.begin() == false) //Connect to the u-blox module using I2C, display error if not found
  {
    Serial.println(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
    while (1);
  }
  myGNSS.setI2COutput(COM_TYPE_UBX);                  // Initialize GNSS module for UBX communication
  myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT);  // ??
  myGNSS.setNavigationFrequency(setNavFreq);          // Set navigation frequency 5Hz
}

