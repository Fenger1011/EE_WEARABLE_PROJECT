#include <Arduino.h> // For using serial print

volatile bool moveDownFlag = false;
volatile bool selectOptionFlag = false;

void moveDown() {
  moveDownFlag = true;
}

void selectOption() {
  selectOptionFlag = true;
}