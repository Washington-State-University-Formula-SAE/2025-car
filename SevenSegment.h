#ifndef SevenSegment_h
#define SevenSegment_h

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

class SevenSegment {
public:
  Adafruit_7segment matrix;
  int reg;
  TwoWire* wire;
  
  SevenSegment(int reg, TwoWire* wire) : matrix(), reg(reg), wire(wire) {}
  void initialize();
  void show(int x, int base = DEC);
  void show(double x, int prec = 2);
  void show(const char* c);

};

#endif