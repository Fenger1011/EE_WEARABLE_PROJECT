#include <Wire.h>
#include <Arduino.h>
#include "oledControl.h"
#include "ISR.h"
#include "u-BloxGNSS.h"
#include "ctrlTimer.h"
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

#define FACTORYRESET_ENABLE 0
#define MINIMUM_FIRMWARE_VERSION "0.6.6"
#define MODE_LED_BEHAVIOUR "HWUART"

// Create bluefruit hardware UART object
Adafruit_BluefruitLE_UART ble(Serial1, BLUEFRUIT_UART_MODE_PIN);  // Serial1 er UART på MCU'en

// A small helper function (HVAD GØR DEN?!!?)
void error(const __FlashStringHelper* err) {
  Serial.println(err);
  while (1)
    ;
}

void setup() {
  Serial1.begin(115200);  // Init UART på SAMD51
  Serial.begin(115200);   // Init serial

  pinMode(13, INPUT_PULLUP);  // MoveDown button
  pinMode(4, INPUT_PULLUP);  // SelectOption button
  attachInterrupt(digitalPinToInterrupt(13), moveDown, FALLING);
  attachInterrupt(digitalPinToInterrupt(4), selectOption, FALLING);

  /* Initialize I2C */
  Wire.begin();

  /* Start and init oled */
  startOLED();

  /* Initialize GNSS module with navigation frequency 5Hz */
  init_GNSS(5);

  /* Initialise the module */
  ble.begin(VERBOSE_MODE);

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  /* Set to low */
  ble.setMode(BLUEFRUIT_MODE_DATA);

  // Setup the timer (Timer 3)
  setupTimer();                     // Setup the timer
  TC3->COUNT16.CC[0].reg = 0x5B8D;  // Set timer frequency to 5Hz
  while (TC3->COUNT16.SYNCBUSY.bit.CC0);            // Wait for clock domain sync
  startTimer();  // Start the timer

  // Show main menu by default
  updateMainMenu();
}

void loop() {
  // Start timer for LogModeRun loop:
  unsigned long startTime = millis();

  if (moveDownFlag) {               // User presses down button
    if (currentMenu == 1) {         // Main menu
      mainMenu++;                   // Increment menu variable
      updateMainMenu();             // Update main menu
    } else if (currentMenu == 2) {  // FreeRun Menu
      freeRunMenu++;                // Increment freerunmenu variable
      updateFreeRunMenu();
    } else if (currentMenu == 3) {  // Start run menu
      startRunMenu++;               // Increment startrunmenu variable
      updateStartRunMenu();
    } else if (currentMenu == 4) {  // Start run menu
      settingsMenu++;               // Increment startrunmenu variable
      updateSettingsMenu();
    }
    moveDownFlag = false;  // Reset movedown flag
  }

  if (selectOptionFlag) {    // User presses select button
    if (currentMenu == 1) {  // currentMenu = 1 = mainMenu
      if (mainMenu == 1) {   // mainmenu = 1 = freerun mode
        currentMenu = 2;     // Current menu is now freerun screen
        updateFreeRunMenu();
      } else if (mainMenu == 2) {  // mainmenu = 2 = start run mode
        currentMenu = 3;           // current menu is now start run screen
        updateStartRunMenu();
      } else if (mainMenu == 3) {  // Show settings menu
        currentMenu = 4;           // Current menu is now settings screen
        updateSettingsMenu();
      } else if (mainMenu == 4) {  // Show menuItem menu
        currentMenu = 5;           // Current menu is now menuItem screen
      }
    }

    
    /*FREERUN MENU & FREERUN CODE*/
    else if (currentMenu == 2) {  // currentMenu = 2 = freeRunMenu
      if (freeRunMenu == 1) {
        // Show freerun screen
        showFreerunScreen();

        // Run get ground speed code
        while (!moveDownFlag) {
          if (newSpeedAvailable()) {
            double velocity_kmh = getSpeed();  // Get current speed in kmh
            OLED_UpdateSpeed(velocity_kmh);    // Update OLED screen with current velocity
          }
        }
      } else if (freeRunMenu == 2) {  // return to main menu
        currentMenu = 1;
        freeRunMenu = 1;
        updateMainMenu();  // Return to main menu
      }
    }
    
    
    /*START RUN CODE & START RUN CODE*/
    else if (currentMenu == 3) {  // currentMenu = 3 = start run menu
      if (startRunMenu == 1) {
        
        // Show run screen
        showLogRunScreen();

        // Run start run code
        while (!moveDownFlag) {
          if (newSpeedAvailable()) {
              double velocity_kmh = getSpeed();  // Get current speed in kmh
              unsigned long currentTime = (millis() - startTime); // Get current time
              OLED_UpdateSpeed(velocity_kmh);    // Update OLED screen with current velocity
              OLED_UpdateTime(currentTime);      // Update OLED screen with current time

              // Send velocity over BT
              ble.print(velocity_kmh);
              ble.print(";");
          }
        }
      } else if (startRunMenu == 2) {
        currentMenu = 1;
        startRunMenu = 1;
        updateMainMenu();  // Return to main menu
      }
    }

    else if (currentMenu == 4) {  // currentMenu = 4 = settings menu
      if (settingsMenu == 1) {
        /*WHILE: SETTINGS-MENU CODE */
      } else if (settingsMenu == 3) {
        currentMenu = 1;
        settingsMenu = 1;
        updateMainMenu();  // Return to main menu
      }
    }

    selectOptionFlag = false;  // Reset select flag
  }
}
