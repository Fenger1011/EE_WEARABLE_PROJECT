#include <Wire.h>
#include "oledControl.h"
#include "ISR.h"

void setup() {
  Serial.begin(9600);
  pinMode(0, INPUT_PULLUP); // MoveDown button
  pinMode(4, INPUT_PULLUP); // SelectOption button
  attachInterrupt(digitalPinToInterrupt(0), moveDown, FALLING);
  attachInterrupt(digitalPinToInterrupt(4), selectOption, FALLING);

  // Initialize I2C
  Wire.begin();

  // Start and init oled
  startOLED();
  
  // Show main menu by default
  updateMainMenu();
}

void loop() {
  // put your main code here, to run repeatedly:

}
