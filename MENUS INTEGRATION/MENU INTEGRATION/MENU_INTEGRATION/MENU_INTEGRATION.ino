#include <Wire.h>
#include "oledControl.h"
#include "ISR.h"
#include "u-BloxGNSS.h"
#include "ctrlTimer.h"

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

  // Initialize GNSS module with navigation frequency 5Hz
  init_GNSS(5); 

  // Setup the timer (Timer 3)
  setupTimer();                                   // Setup the timer
  TC3->COUNT16.CC[0].reg = 0x5B8D;                // Set timer frequency to 5Hz
  while (TC3->COUNT16.SYNCBUSY.bit.CC0);          // Wait for clock domain sync
  startTimer();                                   // Start the timer
  
  // Show main menu by default
  updateMainMenu();
}

void loop() {
  if(moveDownFlag) { // User presses down button
    if(currentMenu == 1) { // Main menu
      mainMenu++; // Increment menu variable
      updateMainMenu(); // Update main menu
    }
    else if(currentMenu == 2) { // FreeRun Menu
      freeRunMenu++; // Increment freerunmenu variable
      updateFreeRunMenu();
    }
    else if(currentMenu == 3) { // Start run menu
      startRunMenu++; // Increment startrunmenu variable
      updateStartRunMenu(); 
    }
    else if(currentMenu == 4) { // Start run menu
      settingsMenu++; // Increment startrunmenu variable
      updateSettingsMenu(); 
    }
    moveDownFlag = false; // Reset movedown flag  
  }

  if(selectOptionFlag) { // User presses select button
    if(currentMenu == 1) { // currentMenu = 1 = mainMenu
      if(mainMenu == 1) { // mainmenu = 1 = freerun mode
        currentMenu = 2; // Current menu is now freerun screen
        updateFreeRunMenu();
      }
      else if(mainMenu == 2) { // mainmenu = 2 = start run mode 
        currentMenu = 3; // current menu is now start run screen
        updateStartRunMenu();
      }
      else if(mainMenu == 3){ // Show settings menu
        currentMenu = 4; // Current menu is now settings screen
        updateSettingsMenu();
      }
      else if(mainMenu == 4){ // Show menuItem menu
        currentMenu = 5; // Current menu is now menuItem screen
      }
    }

    else if(currentMenu == 2) { // currentMenu = 2 = freeRunMenu
      if(freeRunMenu == 1) {
        // Show freerun screen
        showFreerunScreen();
        // Run get ground speed code
        while(1) {
          if (newSpeedAvailable()) {
          double velocity_kmh = getSpeed(); // Get current speed in kmh
          OLED_UpdateSpeed(velocity_kmh); // Update OLED screen with current velocity
          }
        }
      }
      else if(freeRunMenu == 2) { // return to main menu
        currentMenu = 1;
        freeRunMenu = 1;
        updateMainMenu(); // Return to main menu
      }
    }

    else if(currentMenu == 3) { // currentMenu = 3 = start run menu
      if(startRunMenu == 1) {
        /*WHILE: START-RUN CODE */
      }
      else if(startRunMenu == 2) {
        currentMenu = 1;
        startRunMenu = 1;
        updateMainMenu(); // Return to main menu
      }
    }

    else if(currentMenu == 4) { // currentMenu = 4 = settings menu
      if(settingsMenu == 1) {
        /*WHILE: SETTINGS-MENU CODE */
      }
      else if(settingsMenu == 3) {
        currentMenu = 1;
        settingsMenu = 1;
        updateMainMenu(); // Return to main menu
      }
    }

    selectOptionFlag = false; // Reset select flag
  }
}
