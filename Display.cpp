#include "Display.h"

void lightSequence(void) {
  // length of array
  int size = sizeof(ALL_LEDS) / sizeof(ALL_LEDS[0]);

  // initilize
  for (int i = 0; i < size; i++) {
    pinMode(ALL_LEDS[i], OUTPUT);
  }

  // -->
  for (int i = 0; i < size/2; i++) {
    digitalWrite(ALL_LEDS[i], HIGH);
    digitalWrite(ALL_LEDS[size - 1 - i], HIGH);
    delay(200);
    digitalWrite(ALL_LEDS[i], LOW);
    digitalWrite(ALL_LEDS[size - 1 - i], LOW);
  }

  // <--
  for (int i = 0; i < size/2; i++) {
    digitalWrite(ALL_LEDS[size/2 - 1 - i], HIGH);
    digitalWrite(ALL_LEDS[size/2 + i], HIGH);
    delay(200);
    digitalWrite(ALL_LEDS[size/2 - 1 - i], LOW);
    digitalWrite(ALL_LEDS[size/2 + i], LOW);
  }

  delay(200);

  for (int i = 0; i < size; i++) {
    if (i % 2 == 0) {
      digitalWrite(ALL_LEDS[i], HIGH);
    }
  }
  delay(200);

  for (int i = 0; i < size; i++) {
    if (i % 2 == 0) {
      digitalWrite(ALL_LEDS[i], LOW);
    }
  }

  for (int i = 0; i < size; i++) {
    if (i % 2 == 1) {
      digitalWrite(ALL_LEDS[i], HIGH);
    }
  }

  delay(200);

  for (int i = 0; i < size; i++) {
    if (i % 2 == 1) {
      digitalWrite(ALL_LEDS[i], LOW);
    }
  }



}

// returns size of num
int length(int num) {
  if (num == 0) {
    return 1;
  }
  return floor(log10(abs(num))) + 1;
}

void arrangeMid(int rpm, Adafruit_7segment matrix1, Adafruit_7segment matrix2) {

int size = length(rpm);

if (size > 1) {

  int size2 = 0;
  int split = 0;
  int split2 = 0;
  int display1 = 0;
  int hold = 0;
  String display2 = "\0";

  char* idk = "";
  String irdk = "";

  if (size % 2 == 0) {
    split = split2 = size/2;
  } else {
    split = (size/2);
    split2 = size/2 +1;
  }

  display1 = rpm / pow(10, split);
  
  hold = rpm - (display1 * pow(10, split));
  sprintf(idk, "%d", hold);
  irdk = idk;

  int t = length(hold);

  if (length(hold) + length(display1) < size) {
    irdk += "0";
    t++;
  }

  for (int i = 0; i < 4; i++) {
    if (i >= t) {
      irdk+= " ";
    }
  }
  
  matrix2.println(display1);
  matrix1.println(irdk);
  matrix1.writeDisplay();
  matrix2.writeDisplay();

} else {

  String numnum = "";

  char* help = "";

  sprintf(help, "%d", rpm);

   numnum = help;
  for (int i = 0; i < 4; i++) {
    numnum += " ";
  }

  matrix1.println(numnum);
  matrix1.writeDisplay();
  matrix2.println();
  matrix2.writeDisplay();
}

}


void displayRPM(int rpm, Adafruit_7segment matrix1, Adafruit_7segment matrix2) {
  matrix2.setDisplayState(true);
  matrix1.setDisplayState(true);

  arrangeMid(rpm, matrix1, matrix2);

  delay(500);
  matrix1.setDisplayState(false);
  matrix2.setDisplayState(false);

}


void displayClt(int coolant, Adafruit_7segment matrix1, Adafruit_7segment matrix2) {

  matrix1.setDisplayState(true);
  matrix2.setDisplayState(true);

  arrangeMid(coolant, matrix1, matrix2);
  // for (int i = 0; i < 5; i++) {
  //   matrix1.setDisplayState(true);
  //   matrix1.println(coolant);
  //   matrix1.writeDisplay();
  //   delay(600);

  //   matrix1.setDisplayState(false);
  // }



  Serial.println(coolant);
    delay(500);
  matrix1.setDisplayState(false);
  matrix2.setDisplayState(false);
}

void displayOilPres(int oilPressure, Adafruit_7segment matrix1, Adafruit_7segment matrix2) {

  matrix1.setDisplayState(true);
  matrix2.setDisplayState(true);
  
  arrangeMid(oilPressure, matrix1, matrix2);

  Serial.println(oilPressure);
    delay(500);
  matrix1.setDisplayState(false);
  matrix1.setDisplayState(false);

  // for (int i = 0; i < 5; i++) {
  //   matrix1.setDisplayState(true);
  //   matrix1.println(oilPressure);
  //   matrix1.writeDisplay();
  //   delay(600);
  //   matrix1.setDisplayState(false);
  // }
}


int displaying(MegaSquirt3 ecu, Adafruit_7segment matrix1, Adafruit_7segment matrix2, int re) {
  int rpm = ecu.data.rpm;
  int coolant = ecu.data.clt;
  int oilPressure = ecu.data.sensors1;

  // Serial.print("0 = ");
  // Serial.println(length(0));

  // Serial.print("22 = ");
  // Serial.println(length(22));

  // Serial.print("9 = ");
  // Serial.println(length(9));

  // Serial.print("8903 = ");
  // Serial.println(length(8903));
  if (coolant > 230) {
    if (re != 1) {
    matrix2.setDisplayState(true);
    matrix1.setDisplayState(true);

    matrix2.println("CLNt");
    matrix1.println(" tEP");
    matrix2.writeDisplay();
    matrix1.writeDisplay();
    delay(1000);

    matrix2.setDisplayState(false);
    matrix1.setDisplayState(false);
    delay(100);
    }
      displayClt(coolant, matrix1, matrix2);
    
    Serial.println("error found coolant");
    return 1;
  }

  else if (oilPressure  > 80 || oilPressure < -1) {
    if (re != 2) {

      matrix1.setDisplayState(true);
      matrix2.setDisplayState(true);
      matrix2.println("OIL");
      matrix1.println("PRES");
      matrix2.writeDisplay();
      matrix1.writeDisplay();
      delay(1000);

      matrix1.setDisplayState(false);
      matrix2.setDisplayState(false);
      delay(100);

    }

    displayOilPres(oilPressure, matrix1, matrix2);
    Serial.println("error found oil pressure");
    return 2;
  }

  else {

            if (re != 3) {
              
              matrix2.setDisplayState(true);
              matrix1.setDisplayState(false);
              matrix2.println("RPN");
              // matrix1.println("   ");
              matrix2.writeDisplay();
              // matrix1.writeDisplay();
              delay(500);

              matrix2.setDisplayState(false);
              matrix1.setDisplayState(false);
              delay(100);

            }

            displayRPM(rpm, matrix1, matrix2);
            return 3;
  }

}