#include <Wire.h>
#include <Arduino.h>
#include "oledControl.h"
#include "ISR.h"
#include "u-BloxGNSS.h"
#include "ctrlTimer.h"
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

// Constants for Bluefruit BLE module
#define FACTORYRESET_ENABLE 0
#define MINIMUM_FIRMWARE_VERSION "0.6.6"
#define MODE_LED_BEHAVIOUR "HWUART"

// Create Bluefruit hardware UART object
Adafruit_BluefruitLE_UART ble(Serial1, BLUEFRUIT_UART_MODE_PIN);  // Serial1 er UART på MCU'en

void setup() {
  // Initialize UART for SAMD51 and Serial monitor
  Serial1.begin(115200);
  Serial.begin(115200);

  // Initialize pins for buttons with pull-up resistors
  pinMode(13, INPUT_PULLUP);  // MoveDown button
  pinMode(4, INPUT_PULLUP);  // SelectOption button

  // Attach interrupt handlers for buttons
  attachInterrupt(digitalPinToInterrupt(13), moveDown, FALLING);
  attachInterrupt(digitalPinToInterrupt(4), selectOption, FALLING);

  // Initialize I2C
  Wire.begin();
  Wire.setClock(400000);

  // Initialize OLED display
  startOLED();

  // Initialize GNSS module with navigation frequency 5Hz
  init_GNSS(5);

  // Initialize Bluefruit BLE module
  ble.begin(VERBOSE_MODE);
  ble.echo(false); // Disable command echo
  ble.setMode(BLUEFRUIT_MODE_DATA); // Set to data mode

  // Setup the timer (Timer 3) with frequency 5Hz
  setupTimer();
  TC3->COUNT16.CC[0].reg = 0x5B8D;  // Set timer frequency
  while (TC3->COUNT16.SYNCBUSY.bit.CC0); // Wait for clock domain sync
  startTimer();

  // Display the main menu upon start
  updateMainMenu();
}

void loop() {
  // Start timer for LogModeRun loop
  unsigned long startTime = millis();

  // Handle MoveDown button press
  if (moveDownFlag) {
    switch (currentMenu) {
      case 1:  // Main menu
        mainMenu++;
        updateMainMenu();
        break;
      case 2:  // FreeRun menu
        freeRunMenu++;
        updateFreeRunMenu();
        break;
      case 3:  // StartRun menu
        startRunMenu++;
        updateStartRunMenu();
        break;
      case 4:  // Settings menu
        settingsMenu++;
        updateSettingsMenu();
        break;
    }
    moveDownFlag = false;  // Reset MoveDown flag
  }

  // Handle SelectOption button press
  if (selectOptionFlag) {
    switch (currentMenu) {
      case 1:  // Main menu
        if (mainMenu == 1) {  // FreeRun mode
          currentMenu = 2;
          updateFreeRunMenu();
        } else if (mainMenu == 2) {  // StartRun mode
          currentMenu = 3;
          updateStartRunMenu();
        } else if (mainMenu == 3) {  // Settings menu
          currentMenu = 4;
          updateSettingsMenu();
        } else if (mainMenu == 4) { 
          currentMenu = 5;
        }
        break;

      case 2:  // FreeRun menu, no Bluetooth traffic
        if (freeRunMenu == 1) {
          showFreerunScreen();
          while (!moveDownFlag) {
            if (newSpeedAvailable()) {
              double velocity_kmh = getSpeed();  // Get current speed in km/h
              int altitude = getAltitude();      // Get current altitude in m
              OLED_UpdateSpeed(velocity_kmh);    // Update OLED screen with current velocity
              OLED_UpdateAltitude(altitude);
            }
          }
        } else if (freeRunMenu == 2) {  // Return to main menu
          currentMenu = 1;
          freeRunMenu = 1;
          updateMainMenu();
        }
        break;

      case 3:  // StartRun menu, Bluetooth traffic
        if (startRunMenu == 1) {
          showLogRunScreen();
          while (!moveDownFlag) {
            if (newSpeedAvailable()) {
              double velocity_kmh = getSpeed();  // Get current speed in km/h
              unsigned long currentTime = millis() - startTime;  // Get current time
              int altitude = getAltitude(); // Get current altitutde in m
              OLED_UpdateSpeedAltTime(velocity_kmh, altitude, currentTime); // Update all parameters to minimize I2C bus traffic

              // Send velocity over Bluetooth
              ble.print(velocity_kmh);
              ble.print(";");
            }
          }
        } else if (startRunMenu == 2) {  // Return to main menu
          currentMenu = 1;
          startRunMenu = 1;
          updateMainMenu();
        }
        break;

      case 4:  // Settings menu
        if (settingsMenu == 1) {
          // Add settings menu code here
        } else if (settingsMenu == 3) {  // Return to main menu
          currentMenu = 1;
          settingsMenu = 1;
          updateMainMenu();
        }
        break;
    }
    selectOptionFlag = false;  // Reset SelectOption flag
  }
}