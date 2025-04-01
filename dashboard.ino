#include "MegaSquirt3.h"
#include "BMI088.h"
#include <Wire.h>
#include <SD.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include "Selector.h"
#include "Display.h"

bool is_dashboard = false;

const int WRITE_FREQ = 10; // ms

const int SELECTOR_PINS[] = {35, 36, 37, 38, 39, 40};
const int CHECK_ENGINE = 27;
const int DATA_SWITCH = 28;
const int ALL_LEDS[14] = {4, 26, 5, 8, 6, 7, 3, 10, 2, 11, 1, 12, 0, 9};
// const int ALL_LEDS[14] = {4, 4,4,4,4,4,4,4,4,4,4,4,4,4};

// const int ALL_LEDS[] =  {0,1,2,3,4,5,  8,9,10,11,7,6};

Bmi088Accel accel(Wire,0x18);
Bmi088Gyro gyro(Wire,0x68);
SFE_UBLOX_GNSS myGNSS;
SevenSegment display1(0x70, &Wire);
Selector selector(SELECTOR_PINS);
MegaSquirt3 ecu;
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can;
int re;

// #include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix1 = Adafruit_7segment();

Adafruit_7segment matrix2 = Adafruit_7segment();


// Adafruit_7segment matrix = Adafruit_7segment();
    // Adafruit_7segment matrix1 = Adafruit_7segment();
bool is_dashboard = true;
File file;

void handler(const CAN_message_t &msg) {
  
//   accel.readSensor();
//   gyro.readSensor();

// myGNSS.checkUblox(); // Check for the arrival of new data and process it.
// 	int latitude = myGNSS.getLatitude();
// 	int longitude = myGNSS.getLongitude();
// 	int altitude = myGNSS.getAltitude();
// 	int groundSpeed = myGNSS.getGroundSpeed();
	
// 	int SIV = myGNSS.getSIV();


    ecu.data.rpm = 90;

    Serial.println("This is the rpm");
    Serial.println(ecu.data.rpm);

  if (ecu.decode(msg)) {
      // Serial.println(msg.id);

    //Serial.println("this is the rpm");





    //Serial.println(data.rpm);

    // check engine
    bool engine_bad = true;
    digitalWrite(CHECK_ENGINE, engine_bad ? HIGH : LOW);

    // shift lights
    // if (rpm > 7000) digitalWrite(SHIFT_GREEN, HIGH)//......

    // show displays
    display1.show(ecu.data.map);
    Serial.println(ecu.data.map);
    //DASHBOARD_STATE v = (DASHBOARD_STATE)2;
    // switch (v) {
    //   case OFF:
    //     display1.show("....");
    //     // display1.show(0);
    //     break;
    //   case RPM:
    //     display1.show(data.rpm);
    //     // display1.show(1);
    //     break;
    //   case COOLANT:
    //     display1.show(data.clt);
    //     // display1.show(2);
    //     break;
    //   case BATTERY:
    //     display1.show(data.batt);
    //     // display1.show(3);
    //     break;
    //   case THROTTLE_POS:
    //     display1.show(data.tps);
    //     // display1.show(4);
    //     break;
    //   case GEAR:
    //     display1.show(data.gear);
    //     // display1.show(5);
    //     break;
    //   default:
    //     display1.show("    ");
    //     break;
    // }
  } else if (msg.id == 935444) {
    double a = ((msg.buf[0]) + (msg.buf[1]<<8))/5024.0;
    double b = ((msg.buf[2]) + (msg.buf[3]<<8))/5024.0;
    double c = ((msg.buf[4]) + (msg.buf[5]<<8))/5024.0;
    double d = ((msg.buf[6]) + (msg.buf[7]<<8))/5024.0;
    Serial.print(a);Serial.print("\t");
    Serial.print(b);Serial.print("\t");
    Serial.print(c);Serial.print("\t");
    Serial.print(d);Serial.print("\t batt: ");
    Serial.println(ecu.data.batt);

  // write to SD card if time in time
  if (!is_dashboard && millis() > lastwrite + WRITE_FREQ) {
    tosend.write_millis = millis();
    file.write((byte*) &tosend, sizeof(tosend));
    Serial.println("WROTE ##############################################################");
    lastwrite = millis();
  }
  if (is_dashboard) {
    switch (selector.get()) {
      case 0:
        break;
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      default:
        break;
    }
  }
}

// void setup() {

//     intro();


  // #ifndef __AVR_ATtiny85__
  // Serial.begin(9600);
  // Serial.println("7 Segment Backpack Test");
  // #endif
  // matrix.begin(0x70);





    // ecu.data.rpm = 90;

    // Serial.println("this is the rpm");
    // Serial.println(ecu.data.rpm);


  // matrix.print(" gO ");
  // matrix.writeDisplay();
  // delay(10);


  // if (!SD.begin(BUILTIN_SDCARD)) {



    // ecu.data.rpm = 90;

    // Serial.println("this is the rpm");
    // Serial.println(ecu.data.rpm);

    // matrix.print(ecu.data.rpm);
    // matrix.writeDisplay();
    // delay(10);

    // Serial.println("just finished displaying");


  //   Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
  //   while(1);
  // }
  // file = SD.open("log.txt", FILE_WRITE);


  // accel.begin();
  // gyro.begin();

  // pinMode(24, INPUT_PULLUP);
	// pinMode(25, INPUT_PULLUP);

  // Wire2.begin();
  // if (myGNSS.begin(Wire2) == false) //Connect to the u-blox module using Wire port {
	// 	Serial.println(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
	// 	while (1);
	// }
  // myGNSS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
	// myGNSS.setNavigationFrequency(10); //Produce two solutions per second
	// myGNSS.setAutoPVT(true); //Tell the GNSS to "send" each solution

  // for (int i: SHIFT_GREEN) {pinMode(i, OUTPUT);digitalWrite(i, HIGH);}
  // for (int i: SHIFT_YELLOW) {pinMode(i, OUTPUT);digitalWrite(i, HIGH);}
  // for (int i: SHIFT_RED) {pinMode(i, OUTPUT);digitalWrite(i, HIGH);}
  // pinMode(CHECK_ENGINE, OUTPUT);

  // Serial.begin(9600);

  // selector.initialize();
  // display1.initialize();
  // // this->callback = callback;

  // Can.begin();
  // Can.setBaudRate(500000); //set to 500000 for normal Megasquirt usage - need to change Megasquirt firmware to change MS CAN baud rate
  // Can.setMaxMB(16); //sets maximum number of mailboxes for FlexCAN_T4 usage
  // Can.enableFIFO();
  // Can.enableFIFOInterrupt();
  // Can.mailboxStatus();
  // Can.onReceive(handler); //when a CAN message is received, runs the canMShandler function
// }
// CAN_message_t msg;

// void loop() {
//   ecu.data.rpm = ecu.data.rpm + 20;
//   ecu.data.clt = ecu.data.clt + 20;
//   ecu.data.sensors1 = ecu.data.sensors1 + 20;
//   writting(ecu);
//   Serial.println("this is the rpm");

//   if (ecu.data.clt > 250) {
//     ecu.data.clt = 0;
//   }

//   if (ecu.data.sensors1 > 100) {
//     ecu.data.sensors1 = -1;
//   }

//   //iterate("ECU");
//   // flash();
//   //writting(ecu);

//   // display1.show(selector.get());
//   Can.events();
// }




void setup() {
  Serial.begin(9600);
  //  intro();
    #ifndef __AVR_ATtiny85__
    Serial.begin(9600);
    Serial.println("7 Segment Backpack Test");
    #endif
    matrix1.begin(0x70, &Wire);
    matrix2.begin(0x70, &Wire1);
   Serial.println("no connection");

   lightSequence();

  if (is_dashboard) {
    for (int i = 0; i < 12; i++) {
      pinMode(ALL_LEDS[i], OUTPUT);
    }
    pinMode(CHECK_ENGINE, OUTPUT);

    Serial.begin(9600);

    selector.initialize();
    display1.initialize();
       Serial.println("F");
    // display1.initialize();
       Serial.println("G");
  } else {
    if (!SD.begin(BUILTIN_SDCARD)) {
      Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
      while(1);
    }
    Serial.println("@@@@@@@@@@@@@@@@@@");
    accel.begin();
    gyro.begin();

    pinMode(24, INPUT_PULLUP);
    pinMode(25, INPUT_PULLUP);

    Wire2.begin();
    if (myGNSS.begin(Wire2) == false) { //Connect to the u-blox module using Wire port {
      // Serial.println(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
      // while (1);
    }

    myGNSS.checkUblox();
    String filename = String(myGNSS.getYear()) + "-" + String(myGNSS.getMonth()) + "-" + String(myGNSS.getDay()) +\
                    "-" + String(myGNSS.getHour()) + ":" + String(myGNSS.getMinute()) + ":" + String(myGNSS.getSecond() + ".bin");
    // file = SD.open(filename.c_str(), FILE_WRITE);
    file = SD.open("bb.txt", FILE_WRITE);
    file.write("hello\n", 6);
    // file.close();
    Serial.println(filename);
  }

  Can.begin();
  Can.setBaudRate(500000); //set to 500000 for normal Megasquirt usage - need to change Megasquirt firmware to change MS CAN baud rate
  Can.setMaxMB(16); //sets maximum number of mailboxes for FlexCAN_T4 usage
  Can.enableFIFO();
  Can.enableFIFOInterrupt();
  Can.mailboxStatus();
  Can.onReceive(handler); //when a CAN message is received, runs the canMShandler function
}
CAN_message_t msg;

// void loop(){
//   set_rpm(7000);
// }
void set_rpm(int i) {


  if (i <= 6500) {
    digitalWrite(ALL_LEDS[0], HIGH);
    digitalWrite(ALL_LEDS[1], HIGH);
    // delay(500);
    digitalWrite(ALL_LEDS[0], LOW);
    digitalWrite(ALL_LEDS[1], LOW);
    // delay(500);
  } 
  else if (i > 6500 && i < 9500) {
    int numLeds = (i - 6500) / 429;  
    for (int j = 0; j <= (numLeds*2) && j < 12; j = j+2) {  
      digitalWrite(ALL_LEDS[j], HIGH);
   
      digitalWrite(ALL_LEDS[j+1], HIGH);
    }
   
  } 
  else {
    for (int j = 0; j < 12; j++) {
      digitalWrite(ALL_LEDS[j], HIGH);
    }
    // delay(500);
    for (int j = 0; j < 12; j++) {
      digitalWrite(ALL_LEDS[j], LOW);
    }
    // delay(500);
    for (int j = 0; j < 12; j++) {
      digitalWrite(ALL_LEDS[j], HIGH);
    }
  }

  // Adafruit_7segment matrix1 = Adafruit_7segment();
  Serial.println("done");
}


void loop(){

  // matrix1.print(100, DEC);
  // matrix1.writeDisplay();
  // delay(500);
  // Serial.println("kk");
  // matrix2.print(10, DEC);
  // matrix2.writeDisplay();
  // delay(500);
  // Serial.println("kk");


  ecu.data.rpm = ecu.data.rpm + 5;
  ecu.data.clt = ecu.data.clt + 25;
  ecu.data.sensors1 = ecu.data.sensors1 + 25;
  re = displaying(ecu, matrix1, matrix2, re);
  Serial.println("this is the rpm");

  if (ecu.data.clt > 250) {
    ecu.data.clt = 0;
  }

  if (ecu.data.sensors1 > 100) {
    ecu.data.sensors1 = -1;
  }

  // set_rpm(7000);
}

