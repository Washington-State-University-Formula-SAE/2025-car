#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h> 
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include "MegaSquirt3.h"
#include "BMI088.h"
#include <SD.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

void setup(Adafruit_7segment *matrix1, Adafruit_7segment *matrix2);

void intro();

void displayRPM(int rpm);

void displayClt(int coolant);

void displayOilPres(int oilPressure);

void writting(MegaSquirt3 ecu);


#endif


