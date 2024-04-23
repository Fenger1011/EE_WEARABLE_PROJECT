#ifndef ISR_H
#define ISR_H

extern volatile bool moveDownFlag;
extern volatile bool selectOptionFlag;

// ISR for moving down button
void moveDown();

// ISR for selecting option
void selectOption();

#endif /* ISR_H */