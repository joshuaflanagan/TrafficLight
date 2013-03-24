#include <ShiftBrite.h>
#include <Switch.h>

#define GREEN 0
#define YELLOW 1
#define RED 2
ShiftBrite led(11, 13, 9, 10);

Switch changeColorButton(2);
Switch useYellowSwitch(4);
Switch timedChangeSwitch(7);
Switch randomTimeSwitch(8);
 
int currentColor = GREEN;
unsigned long lastChangeTime = 0;

// These will be controlled by hardware inputs
int waitTimes[] = {3000, 2000, 3000};
int waitTime;
boolean includeYellow;
boolean timedChange;

void setup() {
  Serial.begin(9600);
  // check initial state of switches
  useYellowSwitch.poll();
  includeYellow = useYellowSwitch.on();
  timedChangeSwitch.poll();
  timedChange = timedChangeSwitch.on();
  waitTime = determineWaitTime();

  updateColor();
}

void loop() {
  boolean timeToChange = false; // can be triggered by time, or a button

  // check input
  changeColorButton.poll();
  useYellowSwitch.poll();
  timedChangeSwitch.poll();
  randomTimeSwitch.poll();
  
  if (useYellowSwitch.switched()){
    includeYellow = useYellowSwitch.on();
    Serial.print("Use Yellow is now ");
    Serial.println(includeYellow);
  }
  if (timedChangeSwitch.switched()){
    timedChange = timedChangeSwitch.on();
    Serial.print("Timed change is now ");
    Serial.println(timedChange);
  }
  
  if (!timedChange && changeColorButton.pushed()){
    Serial.println("change color");
    timeToChange = true;
  }

  if (timedChange && randomTimeSwitch.switched()){
    Serial.print("Use random time is now ");
    Serial.println(randomTimeSwitch.on());
  }

  if (timedChange) {
    unsigned long now = millis();
    if (now - lastChangeTime > waitTime){
      lastChangeTime = now;
      timeToChange = true;
    }
  }

  // update state
  if (timeToChange){
    cycleToNextColor();
    waitTime = determineWaitTime();
  }
  
  // paint
  if (timeToChange) {
    updateColor();
  }
}

int determineWaitTime(){
  if (currentColor == YELLOW) return waitTimes[YELLOW];
  if (randomTimeSwitch.on()){
    return random(1, 6) * 1000;
  } else {
    return waitTimes[currentColor];
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
