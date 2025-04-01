#ifndef DISPLAY_H
#define DISPLAY_H
// #ifndef __AVR_ATtiny85__

#include <Wire.h> 
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include "MegaSquirt3.h"
#include "BMI088.h"
#include <SD.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include <cmath>
#include <stdio.h>

const int ALL_LEDS[] =  {0,1,2,3,4,5,  8,9,10,11,7,6};

void lightSequence(void);

// returns size of num
int length(int num);

void arrangeMid(int rpm, Adafruit_7segment matrix1, Adafruit_7segment matrix2);

void displayRPM(int rpm, Adafruit_7segment matrix1, Adafruit_7segment matrix2);

void displayClt(int coolant, Adafruit_7segment matrix1, Adafruit_7segment matrix2);

void displayOilPres(int oilPressure, Adafruit_7segment matrix1, Adafruit_7segment matrix2);

int displaying(MegaSquirt3 ecu, Adafruit_7segment matrix1, Adafruit_7segment matrix2, int re);


#endif