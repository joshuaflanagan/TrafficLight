#include <ShiftBrite.h>
#include <Switch.h>

#define GREEN 0
#define YELLOW 1
#define RED 2
ShiftBrite led(11, 13, 9, 10);

Switch changeColorButton(2);
Switch useYellowSwitch(4);
Switch timedChangeSwitch(7);
 
int currentColor = RED;
unsigned long lastChangeTime = 0;

// These will be controlled by hardware inputs
int waitTimes[] = {3000, 2000, 3000};
boolean includeYellow = true;
boolean timedChange = true;

void setup() {
  Serial.begin(9600);
  updateColor();
}

void loop() {
  boolean timeToChange = false; // can be triggered by time, or a button

  // check input
  changeColorButton.poll();
  useYellowSwitch.poll();
  timedChangeSwitch.poll();
  
  if (useYellowSwitch.switched()){
    includeYellow = useYellowSwitch.on();
    Serial.print("Use Yellow is now ");
    Serial.println(includeYellow);
  }
  if (timedChangeSwitch.switched()){
    timedChange = timedChangeSwitch.on();
    Serial.print("Manual change is now ");
    Serial.println(timedChange);
  }
  
  if (!timedChange && changeColorButton.pushed()){
    Serial.println("change color");
    timeToChange = true;
  }

  if (timedChange) {
    unsigned long now = millis();
    if (now - lastChangeTime > waitTimes[currentColor]){
      lastChangeTime = now;
      timeToChange = true;
    }
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
  } else if (currentColor == YELLOW) {
    currentColor = RED;
  } else {
    // current is GREEN - where to next?
    if (includeYellow) {
      currentColor = YELLOW;
    } else {
      currentColor = RED;
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
