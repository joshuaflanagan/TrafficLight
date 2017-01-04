/*
Switch
Version 7-12-2012
Copyright (C) 2012  Albert van Dalen http://www.avdweb.nl
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License at http://www.gnu.org/licenses .              
                  _______________________      _                                 
                 |                       |||||| |||                              
                 |                       |||||| |||                                                         
 ________________|                       |||||| |||____________                     
        
 poll            ^                         ^   ^          ^                          
 switchedTime    ^                         ^                         
 debounceDelay              <------------->                      
 switched                                  1   0          0                            
 newlevel                                  0   1          0                               
                        ___________________                 
 level                                     |___________________                                                           
*/

#if ARDUINO >= 100 
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Switch.h"

Switch::Switch(byte _pin, byte PinMode, bool _polarity, unsigned long _debounceDelay): 
pin(_pin), polarity(_polarity), debounceDelay(_debounceDelay) // level(0) peculiarity 4*) // peculiarity 2*) 
{ pinMode(pin, PinMode); 
  _switchedTime = millis();
  level = digitalRead(pin);
}

bool Switch::poll()
{ bool newlevel = digitalRead(pin); // peculiarity 1*)
  if((newlevel != level) & (millis() - _switchedTime >= debounceDelay)) 
  { _switchedTime = millis();
    level = newlevel;
    return _switched = 1;
  }
  return _switched = 0;
}

bool Switch::switched()
{ return _switched;
}

bool Switch::on()
{ return !(level^polarity);
}

bool Switch::pushed() 
{ return _switched && !(level^polarity); 
}

bool Switch::released() 
{ return _switched && (level^polarity); 
}
