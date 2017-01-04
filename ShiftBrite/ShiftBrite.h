/*
 ShiftBrite.h - control a single Macetech ShiftBrite/Megabrite RGB LED

 Library created by Joshua Flanagan, based on code from:
 http://docs.macetech.com/doku.php/shiftbrite_2.0
*/

#ifndef ShiftBrite_h
#define ShiftBrite_h

#include "Arduino.h"

class ShiftBrite
{
  public:
    ShiftBrite(int data, int clock, int latch, int enable);
    void changeColor(int red, int green, int blue);

  private:
    void _sendPacket(int command, int red, int green, int blue);
    void _latchDataInRegisters();

    int _latchPin;
 };

 #endif
