#include <Arduino.h> // For using serial print

volatile bool moveDownFlag = false;
volatile bool selectOptionFlag = false;

void moveDown() {
  moveDownFlag = true;
  Serial.println("DOWN BUTTON PRESSED"); // For debugging
}

void selectOption() {
  selectOptionFlag = true;
  Serial.println("SELECT BUTTON PRESSED"); // For debugging
}