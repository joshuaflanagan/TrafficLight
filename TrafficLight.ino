#include <ShiftBrite.h>
#define GREEN 0
#define YELLOW 1
#define RED 2
ShiftBrite led(11, 13, 9, 10);
 
int currentColor = RED;
unsigned long lastChangeTime = 0;
int waitTime;

// These will be controlled by hardware inputs
int redGreenTime = 3000;
int yellowTime = 2000;
boolean includeYellow = true;

void setup() {
  updateColor();
}

void loop() {
  boolean timeToChange = false; // can be triggered by time, or a button
  
  // check input
  unsigned long now = millis();
  if (now - lastChangeTime > waitTime){
    lastChangeTime = now;
    timeToChange = true;
  }
  
  // update state
  if (timeToChange){
    cycleToNextColor();
  }
  
  // paint
  if (timeToChange) {
    updateColor();
  }
}

void cycleToNextColor(){
  if (currentColor == RED){
    currentColor = GREEN;
    waitTime = redGreenTime;
  } else if (currentColor == YELLOW) {
    currentColor = RED;
    waitTime = redGreenTime;
  } else {
    // current is GREEN - where to next?
    if (includeYellow) {
      currentColor = YELLOW;
      waitTime = yellowTime;
    } else {
      currentColor = RED;
      waitTime = redGreenTime;
    }
  }
}
  
void updateColor(){
  if (currentColor == GREEN){
    led.changeColor(0, 1023, 0);
  } else if (currentColor == YELLOW) {
    led.changeColor(1023, 400, 0);
  } else {
    led.changeColor(1023, 0, 0);
  };
}
