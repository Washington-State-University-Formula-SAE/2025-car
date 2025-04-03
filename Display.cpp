#include "Display.h"

/* BLOCKING */
void lightSequence(void) {
  // length of array
  int size = 14;

  // initilize
  for (int i = 0; i < size; i++) {
    pinMode(ALL_LEDS[i], OUTPUT);
  }

  // -->
  for (int i = 0; i < size/2; i++) {
    digitalWrite(ALL_LEDS[2*i], HIGH);
    digitalWrite(ALL_LEDS[(2*i)+1], HIGH);
    delay(200);
    digitalWrite(ALL_LEDS[2*i], LOW);
    digitalWrite(ALL_LEDS[(2*i)+1], LOW);
  }

  // <--
  for (int i = size/2; i > 0; i--) {
    digitalWrite(ALL_LEDS[2*i], HIGH);
    digitalWrite(ALL_LEDS[(2*i)+1], HIGH);
    delay(200);
    digitalWrite(ALL_LEDS[2*i], LOW);
    digitalWrite(ALL_LEDS[(2*i)+1], LOW);
  }

  delay(200);

  for (int i = 0; i < size; i++) {
    if (i % 2 == 0) {
      digitalWrite(ALL_LEDS[i], HIGH);
    } else {
      digitalWrite(ALL_LEDS[i], LOW);
    }
  }
  delay(200);

  for (int i = 0; i < size; i++) {
    digitalWrite(ALL_LEDS[i], LOW);
  }

  for (int i = 0; i < size; i++) {
    if (i % 2 == 1) {
      digitalWrite(ALL_LEDS[i], HIGH);
    } else {
      digitalWrite(ALL_LEDS[i], LOW);
    }
  }

  delay(200);

  for (int i = 0; i < size; i++) {
      digitalWrite(ALL_LEDS[i], LOW);
  }
}

// returns number of digits in num
int n_digits(int num) {
  if (num == 0) {
    return 1;
  }
  return floor(log10(abs(num))) + 1;
}

void displayText(String s, Adafruit_7segment matrix1, Adafruit_7segment matrix2) {
  if (s.length() > 4) {
    matrix1.print(s.substring(0, 4));
    matrix2.print(s.substring(4));
  } else {
    matrix1.print(s);
    matrix2.print("");
  }
  matrix1.writeDisplay();
  matrix2.writeDisplay();
}

void displayInt(int value, Adafruit_7segment matrix1, Adafruit_7segment matrix2) {
  matrix1.setDisplayState(true);
  matrix2.setDisplayState(true);

  int number_digits = n_digits(value);

  if (number_digits > 1) {
    int size2 = 0;
    int split = 0;
    int split2 = 0;
    int display1 = 0;
    int hold = 0;
    String display2 = "\0";

    char* temp1 = "";
    String temp2 = "";

    if (number_digits % 2 == 0) {
      split = split2 = number_digits/2;
    } else {
      split = (number_digits/2);
      split2 = number_digits/2 +1;
    }

    display1 = value / pow(10, split);
    
    hold = value - (display1 * pow(10, split));
    sprintf(temp1, "%d", hold);
    temp2 = temp1;

    int t = n_digits(hold);

    if (n_digits(hold) + n_digits(display1) < number_digits) {
      temp2 += "0";
      t++;
    }

    for (int i = 0; i < 4; i++) {
      if (i >= t) {
        temp2+= " ";
      }
    }
    
    matrix2.println(display1);
    matrix1.println(temp2);
    matrix1.writeDisplay();
    matrix2.writeDisplay();

  } else {

    String numnum = "";

    char* help = "";

    sprintf(help, "%d", value);

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


// void displayRPM(int rpm, Adafruit_7segment matrix1, Adafruit_7segment matrix2) {
//   matrix2.setDisplayState(true);
//   matrix1.setDisplayState(true);

//   displayInt(rpm, matrix1, matrix2);

//   delay(500);
//   matrix1.setDisplayState(false);
//   matrix2.setDisplayState(false);

// }


// void displayClt(int coolant, Adafruit_7segment matrix1, Adafruit_7segment matrix2) {
//   matrix1.setDisplayState(true);
//   matrix2.setDisplayState(true);

//   displayInt(coolant, matrix1, matrix2);

//   Serial.println(coolant);
//   delay(500);
//   matrix1.setDisplayState(false);
//   matrix2.setDisplayState(false);
// }

// void displayOilPres(int oilPressure, Adafruit_7segment matrix1, Adafruit_7segment matrix2) {

//   matrix1.setDisplayState(true);
//   matrix2.setDisplayState(true);
  
//   displayInt(oilPressure, matrix1, matrix2);

//   Serial.println(oilPressure);
//   delay(500);
//   matrix1.setDisplayState(false);
//   matrix1.setDisplayState(false);
// }


int displaying(MegaSquirt3 ecu, Adafruit_7segment matrix1, Adafruit_7segment matrix2, int re) {
  int rpm = ecu.data.rpm;
  int coolant = ecu.data.clt;
  int oilPressure = ecu.data.sensors1;

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

// SET RPM ==============================================================================================================================================================
void set_rpm(int i) {
  bool evenodd = ((int)floor(millis()/1000)) % 2;
  if (i <= 6500) {
    digitalWrite(ALL_LEDS[0], evenodd ? HIGH : LOW);
    digitalWrite(ALL_LEDS[1], evenodd ? HIGH : LOW);
    for (int j = 2; j < 14; j++) {  
      digitalWrite(ALL_LEDS[j], LOW);
    }
  } 
  else if (i > 6500 && i < 9500) {
    int numleds = (i - 6500) / 429;  
    for (int j = 0; j < numleds/2; j++) {  
      digitalWrite(ALL_LEDS[j], HIGH);
      digitalWrite(ALL_LEDS[j+1], HIGH);
    }
   
  } 
  else {
    for (int j = 0; j < 12; j++) {
      digitalWrite(ALL_LEDS[j], HIGH);
    }
    digitalWrite(ALL_LEDS[12], evenodd ? HIGH : LOW);
    digitalWrite(ALL_LEDS[13], evenodd ? HIGH : LOW);
  }
}