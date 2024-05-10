#include <SFE_MicroOLED.h>

#define DC_JUMPER 1
#define PIN_RESET 9 // Optional - Connect RST on display to pin 9 on Arduino

MicroOLED oled(PIN_RESET, DC_JUMPER); //Example I2C declaration

// Holds value for current menu option
volatile int currentMenu = 1;
volatile int mainMenu = 1;
volatile int freeRunMenu = 1;
volatile int startRunMenu = 1;
volatile int settingsMenu = 1;

// Initializes OLED and wipes screen
void startOLED() {
  oled.begin(); // Inits and configures oled
  oled.clear(ALL);
  oled.clear(PAGE);
}

// Updates main menu
void updateMainMenu() {
  switch (mainMenu) {
    case 0:
      mainMenu = 1;
      break;
    case 1:
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("MAIN MENU");
      oled.setCursor(0,10);
      oled.print(">Freerun");
      oled.setCursor(0,20);
      oled.print(" Start run");
      oled.setCursor(0,30);
      oled.print(" Settings");
      oled.display();
      break;
    case 2:
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("MAIN MENU");
      oled.setCursor(0,10);
      oled.print(" Freerun");
      oled.setCursor(0,20);
      oled.print(">Start run");
      oled.setCursor(0,30);
      oled.print(" Settings");
      oled.display();
      break;
    case 3:
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("MAIN MENU");
      oled.setCursor(0,10);
      oled.print(" Freerun");
      oled.setCursor(0,20);
      oled.print(" Start run");
      oled.setCursor(0,30);
      oled.print(">Settings");
      oled.display();
      break;
    case 4:
      mainMenu = 1;
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("MAIN MENU");
      oled.setCursor(0,10);
      oled.print(">Freerun");
      oled.setCursor(0,20);
      oled.print(" Start run");
      oled.setCursor(0,30);
      oled.print(" Settings");
      oled.display();
      break;
  }
}

// Updates free run menu
void updateFreeRunMenu() {
  switch(freeRunMenu) {
    case 0:
      freeRunMenu = 1;
      break;
    case 1:
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("FREERUN");
      oled.setCursor(0,10);
      oled.print(">Start");
      oled.setCursor(0,20);
      oled.print(" Return");
      oled.display();
      break;
    case 2:
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("FREERUN");
      oled.setCursor(0,10);
      oled.print(" Start");
      oled.setCursor(0,20);
      oled.print(">Return");
      oled.display();
      break;
    case 3:
      freeRunMenu = 1;
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("FREERUN");
      oled.setCursor(0,10);
      oled.print(">Start");
      oled.setCursor(0,20);
      oled.print(" Return");
      oled.display();
      break;
  }
}

// Updates start run menu
void updateStartRunMenu() {
  switch(startRunMenu) {
    case 0:
      startRunMenu = 1;
      break;
    case 1:
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("START RUN");
      oled.setCursor(0,10);
      oled.print(">Start Run");
      oled.setCursor(0,20);
      oled.print(" Return");
      oled.display();
      break;
    case 2:
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("START RUN");
      oled.setCursor(0,10);
      oled.print(" Start Run");
      oled.setCursor(0,20);
      oled.print(">Return");
      oled.display();
      break;
    case 3:
      startRunMenu = 1;
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("START RUN");
      oled.setCursor(0,10);
      oled.print(">Start Run");
      oled.setCursor(0,20);
      oled.print(" Return");
      oled.display();
      break;
  }
}

// Updates settings menu
void updateSettingsMenu() {
  switch(settingsMenu) {
    case 0:
      settingsMenu = 1;
      break;
    case 1:
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("SETTINGS");
      oled.setCursor(0,10);
      oled.print(">GPS");
      oled.setCursor(0,20);
      oled.print(" Units");
      oled.setCursor(0,30);
      oled.print(" Return");
      oled.display();
      break;
    case 2:
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("SETTINGS");
      oled.setCursor(0,10);
      oled.print(" GPS");
      oled.setCursor(0,20);
      oled.print(">Units");
      oled.setCursor(0,30);
      oled.print(" Return");
      oled.display();
      break;
    case 3:
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("SETTINGS");
      oled.setCursor(0,10);
      oled.print(" GPS");
      oled.setCursor(0,20);
      oled.print(" Units");
      oled.setCursor(0,30);
      oled.print(">Return");
      oled.display();
      break;
    case 4:
      settingsMenu = 1;
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("SETTINGS");
      oled.setCursor(0,10);
      oled.print(">GPS");
      oled.setCursor(0,20);
      oled.print(" Units");
      oled.setCursor(0,30);
      oled.print(" Return");
      oled.display();
      break;
  }
}

void showFreerunScreen() {
  oled.clear(PAGE);
  oled.setCursor(0,0);
  oled.print("Kmh: ");
  oled.setCursor(0,10);
  oled.print("Alt: ");
  oled.display();
}

void showLogModeScreen() {
  oled.clear(PAGE);
  oled.setCursor(0,0);
  oled.print("Start log?");
  oled.setCursor(0,10);
  oled.print("[Y], [N] ");
  oled.display();
}

void OLED_UpdateSpeed(double speed) {
  // Update OLED speed
  //oled.clear(PAGE);
  oled.setCursor(24, 0);
  oled.print(speed);
  oled.display();
}

void OLED_UpdateTime(long time) {
  // Update OLED time
  int seconds = time / 1000;  // Calculate the full seconds
  int milliseconds = time % 1000;  // Calculate the remaining milliseconds

  // Clear the previous display to prevent ghosting of text
  oled.setCursor(18, 30);
  
  // Print formatted time as xx.yy where xx is seconds and yy is milliseconds
  if (milliseconds < 10) {
    oled.print(seconds);
    oled.print(".00");
    oled.print(milliseconds);  // Ensures three digits are always displayed
  } else if (milliseconds < 100) {
    oled.print(seconds);
    oled.print(".0");
    oled.print(milliseconds);  // Ensures three digits are always displayed
  } else {
    oled.print(seconds);
    oled.print(".");
    oled.print(milliseconds);
  }

  // Update the OLED display to show new time
  oled.display();
}

void showLogRunScreen() {
  oled.clear(PAGE);
  oled.setCursor(0,0);
  oled.print("Kmh: ");
  oled.setCursor(0,10);
  oled.print("Alt: ");
  oled.display();
}
