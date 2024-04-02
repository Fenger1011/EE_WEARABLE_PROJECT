#include <SFE_MicroOLED.h>

#define DC_JUMPER 1
#define PIN_RESET 9 // Optional - Connect RST on display to pin 9 on Arduino

MicroOLED oled(PIN_RESET, DC_JUMPER); //Example I2C declaration

// Holds value for current menu option
int menu = 1;

// Initializes OLED and wipes screen
void startOLED() {
  oled.begin(); // Inits and configures oled
  oled.clear(ALL);
  oled.clear(PAGE);
}

// Updates main menu
void updateMainMenu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("MAIN MENU");
      oled.setCursor(0,10);
      oled.print(">Freestyle");
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
      oled.print(" Freestyle");
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
      oled.print(" Freestyle");
      oled.setCursor(0,20);
      oled.print(" Start run");
      oled.setCursor(0,30);
      oled.print(">Settings");
      oled.display();
      break;
    case 4:
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("MAIN MENU");
      oled.setCursor(0,10);
      oled.print(" Start run");
      oled.setCursor(0,20);
      oled.print(" Settings");
      oled.setCursor(0,30);
      oled.print(">MenuItem");
      oled.display();
      break;
    case 5:
      menu = 1;
      oled.clear(PAGE);
      oled.setCursor(0,0);
      oled.print("MAIN MENU");
      oled.setCursor(0,10);
      oled.print(">Freestyle");
      oled.setCursor(0,20);
      oled.print(" Start run");
      oled.setCursor(0,30);
      oled.print(" Settings");
      oled.display();
      break;
  }
}