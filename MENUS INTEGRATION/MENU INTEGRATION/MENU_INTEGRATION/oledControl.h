#ifndef OLED_CONTROL_H
#define OLED_CONTROL_H

extern volatile int currentMenu;
extern volatile int mainMenu;
extern volatile int freeRunMenu;
extern volatile int startRunMenu;
extern volatile int settingsMenu;

// Initializes OLED and wipes screen
void startOLED();

// Updates main manu
void updateMainMenu();

// Update freerun menu
void updateFreeRunMenu();

// Update start run menu
void updateStartRunMenu();

// Update settings menu
void updateSettingsMenu();

// Update speed on screen
void OLED_UpdateSpeed(double speed);

// Freerun static screen
void showFreerunScreen();

// Start run static screen
void showRunTypeMenu();

#endif /* OLED_CONTROL_H */