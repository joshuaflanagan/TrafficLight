#include <ShiftBrite.h>

ShiftBrite led( 11,  // DI - data
                13,  // CI - clock
                 9,  // LI - latch
                10); // EI - enable

void setup() { 
}

void loop() {
  int pause = 1000;

  //red
  led.changeColor(1023, 0, 0);
  delay(pause);

   //orange
  led.changeColor(1023, 200, 0);
  delay(pause);

  //yellow
  led.changeColor(1023, 600, 0);
  delay(pause);

  //green
  led.changeColor(0, 1023, 0);  
  delay(pause);

  //blue
  led.changeColor(0, 0, 1023);
  delay(pause); 
  
  //violet
  led.changeColor(1023, 0, 800);
  delay(pause);
}
