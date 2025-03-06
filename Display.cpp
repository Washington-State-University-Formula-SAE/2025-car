#include "Display.h"

void setup(Adafruit_7segment *matrix1, Adafruit_7segment *matrix2) {
    *matrix1 = Adafruit_7segment();
    *matrix2 = Adafruit_7segment();

    #ifndef __AVR_ATtiny85__
    Serial.begin(9600);
    Serial.println("7 Segment Backpack Test");
    #endif
    matrix1->begin(0x70, &Wire);
    matrix2->begin(0x70, &Wire1);
}

void intro() {
    Adafruit_7segment matrix1;
    Adafruit_7segment matrix2;

    setup(&matrix1, &matrix2);

  for (int i = 0; i < 5; i++) {
    matrix1.setDisplayState(true);
    matrix2.setDisplayState(true);
    matrix2.println("gO C");
    matrix1.println("OUgS");
    matrix2.writeDisplay();
    matrix1.writeDisplay();
    delay(600);
    matrix1.setDisplayState(false);
    matrix2.setDisplayState(false);
    delay(100);
  }


}

void displayRPM(int rpm) {
  Adafruit_7segment matrix1;
  Adafruit_7segment matrix2;

  setup(&matrix1, &matrix2);

  matrix2.println("RPn");
  matrix1.println(rpm);
  matrix2.writeDisplay();
  matrix1.writeDisplay();
  delay(100);

  // matrix1.setDisplayState(false);
  // matrix2.setDisplayState(false);
}

void displayClt(int coolant) {
  Adafruit_7segment matrix1;
  Adafruit_7segment matrix2;

  setup(&matrix1, &matrix2);

  for (int i = 0; i < 5; i++) {

    matrix2.setDisplayState(true);
    matrix1.setDisplayState(true);

    matrix2.println("CLNt");
    matrix1.println(" tEP");
    matrix2.writeDisplay();
    matrix1.writeDisplay();
    delay(400);

    matrix2.setDisplayState(false);
    matrix1.setDisplayState(false);
    delay(100);

    matrix1.setDisplayState(true);
    matrix1.println(coolant);
    matrix1.writeDisplay();
    delay(600);

    matrix1.setDisplayState(false);
  }

  // matrix1.setDisplayState(false);
  // matrix2.setDisplayState(false);
}

void displayOilPres(int oilPressure) {
  Adafruit_7segment matrix1;
  Adafruit_7segment matrix2;

  setup(&matrix1, &matrix2);

  for (int i = 0; i < 5; i++) {
    matrix1.setDisplayState(true);
    matrix2.setDisplayState(true);
    matrix2.println("OIL");
    matrix1.println("PRES");
    matrix2.writeDisplay();
    matrix1.writeDisplay();
    delay(400);

    matrix1.setDisplayState(false);
    matrix2.setDisplayState(false);
    delay(100);

    matrix1.setDisplayState(true);
    matrix1.println(oilPressure);
    matrix1.writeDisplay();
    delay(600);
    matrix1.setDisplayState(false);
  }


}


void writting(MegaSquirt3 ecu) {


  int rpm = ecu.data.rpm;
  int coolant = ecu.data.clt;
  int oilPressure = ecu.data.sensors1;


  if (coolant > 230) {
    displayClt(coolant);
    Serial.println("error found coolant");
  }

  else if (oilPressure  > 80 || oilPressure < -1) {
    displayOilPres(oilPressure);
    Serial.println("error found oil pressure");
  }

  else {
    displayRPM(rpm);
  }

}