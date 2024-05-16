volatile bool moveDownFlag = false;
volatile bool selectOptionFlag = false;

// ISR raising flag when user press 'down'
void moveDown() {
  moveDownFlag = true;
}

// ISR raising flag when user press 'select'
void selectOption() {
  selectOptionFlag = true;
}