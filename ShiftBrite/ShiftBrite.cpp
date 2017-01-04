#include "ShiftBrite.h"

ShiftBrite::ShiftBrite(int data, int clock, int latch, int enable) {
  //TODO: this only needs to happen once per sketch - do not run if multiple instances of LEDs
  // Configure communication pins 
  pinMode(data, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(enable, OUTPUT);
  pinMode(clock, OUTPUT);
  // Configure communication settings
  SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(0<<SPR0);

  digitalWrite(latch, LOW);
  digitalWrite(enable, LOW);
  _latchPin = latch;
}

void ShiftBrite::changeColor(int red, int green, int blue) {
  // Send color information
  _sendPacket(B00, red, green, blue);
  _latchDataInRegisters();

   // Write to current control registers
  _sendPacket(B01, 120, 100, 100);
  _latchDataInRegisters();
};


// NOTE: Only need to do this after all LEDs in series have been updated
void ShiftBrite::_latchDataInRegisters(){
  delayMicroseconds(15);
  digitalWrite(_latchPin,HIGH);
  delayMicroseconds(15);
  digitalWrite(_latchPin,LOW);
}

//TODO: figure out better names for params - based on bit order? b0_10, or lowByte, medByte, hiByte
void ShiftBrite::_sendPacket(int command, int red, int green, int blue) {
  SPDR = command << 6 | blue>>4;
  while(!(SPSR & (1<<SPIF)));
  SPDR = blue<<4 | red>>6;
  while(!(SPSR & (1<<SPIF)));
  SPDR = red << 2 | green>>8;
  while(!(SPSR & (1<<SPIF)));
  SPDR = green;
  while(!(SPSR & (1<<SPIF)));
};
