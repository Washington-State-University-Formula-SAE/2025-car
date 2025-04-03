#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h> 
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "MegaSquirt3.h"

#include <cmath>
// const int ALL_LEDS[] =  {0,1,2,3,4,5,  8,9,10,11,7,6};
const int ALL_LEDS[14] = {7, 4, 8, 5, 9, 6, 10, 2, 11, 3, 12, 0, 26, 1};

void lightSequence(void);

// returns size of num
int n_digits(int num);

void displayText(String s, Adafruit_7segment matrix1, Adafruit_7segment matrix2);

void displayInt(int rpm, Adafruit_7segment matrix1, Adafruit_7segment matrix2);

void displayRPM(int rpm, Adafruit_7segment matrix1, Adafruit_7segment matrix2);

void displayClt(int coolant, Adafruit_7segment matrix1, Adafruit_7segment matrix2);

void displayOilPres(int oilPressure, Adafruit_7segment matrix1, Adafruit_7segment matrix2);

int displaying(MegaSquirt3 ecu, Adafruit_7segment matrix1, Adafruit_7segment matrix2, int re);

void set_rpm(int i);

#endif