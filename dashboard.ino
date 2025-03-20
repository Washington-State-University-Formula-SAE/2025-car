#include "MegaSquirt3.h"
#include "BMI088.h"
#include <Wire.h>
#include <SD.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include "SevenSegment.h"
#include "Selector.h"
#include "Display.h"

bool is_dashboard = true;

const int WRITE_FREQ = 5000; // ms

const int SELECTOR_PINS[] = {35, 36, 37, 38, 39, 40};
const int CHECK_ENGINE = 27;
const int ALL_LEDS[14] = {4, 26, 5, 8, 6, 7, 3, 10, 2, 11, 1, 12, 0, 9};
// const int ALL_LEDS[14] = {4, 4,4,4,4,4,4,4,4,4,4,4,4,4};


Bmi088Accel accel(Wire,0x18);
Bmi088Gyro gyro(Wire,0x68);
SFE_UBLOX_GNSS myGNSS;
SevenSegment display1(0x70, &Wire);
SevenSegment display2(0x70, &Wire1);
Selector selector(SELECTOR_PINS);
MegaSquirt3 ecu;
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can;

File file;
ROW tosend;
uint32_t lastwrite = 0;


void handler(const CAN_message_t &msg) {
  Serial.println("message");
  // log directly wired sensors:
  if (!is_dashboard) {
    // log accelerometer
    accel.readSensor();
    tosend.ax = accel.getAccelX_mss();
    tosend.ay = accel.getAccelY_mss();
    tosend.az = accel.getAccelZ_mss();
    tosend.accel_millis = millis();

    // log gyro
    gyro.readSensor();
    tosend.imu_x = gyro.getGyroX_rads();
    tosend.imu_y = gyro.getGyroY_rads();
    tosend.imu_z = gyro.getGyroZ_rads();
    tosend.imu_millis = millis();

    // log GPS
    myGNSS.checkUblox();
    tosend.hour = myGNSS.getHour();
    tosend.minute = myGNSS.getMinute();
    tosend.second = myGNSS.getSecond();
    tosend.lat = myGNSS.getLatitude();
    tosend.lon = myGNSS.getLongitude();
    tosend.elev = myGNSS.getAltitude();
    tosend.ground_speed = myGNSS.getGroundSpeed();	
    tosend.gps_millis = millis();
  }

  if (ecu.decode(msg)) {
    // read ecu data
    // =============
    if (is_dashboard) {
      set_rpm(ecu.data.rpm);
    }
    tosend.rpm = ecu.data.rpm;
    tosend.time = ecu.data.seconds;
    tosend.afr = ecu.data.AFR1;
    tosend.spark_advance = ecu.data.adv_deg;
    tosend.baro = ecu.data.baro;
    tosend.map = ecu.data.map;
    tosend.mat = ecu.data.mat;
    tosend.clnt_temp = ecu.data.clt;
    tosend.tps = ecu.data.tps;
    tosend.batt = ecu.data.batt;
    tosend.oil_press = ecu.data.sensors1;
    tosend.syncloss_count = ecu.data.synccnt;
    tosend.syncloss_code = ecu.data.syncreason;
    tosend.ltcl_timing = ecu.data.launch_timing;
    tosend.ve1 = ecu.data.ve1;
    tosend.ve2 = ecu.data.ve2;
    tosend.egt = ecu.data.egt1;
    tosend.maf = ecu.data.MAF;
    tosend.in_temp = ecu.data.airtemp;
    tosend.ecu_millis = millis();
  } else if (msg.id == 935444) {
    // This is for all of the AnalogX stuff (one `if` statment per ID):
    // =====================================================
    tosend.analogx1_millis = millis();
    double a = ((msg.buf[0]) + (msg.buf[1]<<8))/5024.0;
    double b = ((msg.buf[2]) + (msg.buf[3]<<8))/5024.0;
    double c = ((msg.buf[4]) + (msg.buf[5]<<8))/5024.0;
    double d = ((msg.buf[6]) + (msg.buf[7]<<8))/5024.0;
  }

  // write to SD card if time in time
  if (!is_dashboard && millis() > lastwrite + WRITE_FREQ) {
    tosend.write_millis = millis();
    file.write((byte*) &tosend, sizeof(tosend));
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

void setup() {
  // intro();
  Serial.begin(9600);

   Serial.println("A");

  if (is_dashboard) {
       Serial.println("B");
    for (int i = 0; i < 14; i++) {
      pinMode(ALL_LEDS[i], OUTPUT);
    }
       Serial.println("C");
    pinMode(CHECK_ENGINE, OUTPUT);
       Serial.println("D");

       Serial.println("E");

    selector.initialize();
       Serial.println("F");
    display1.initialize();
       Serial.println("G");
  } else {
    if (!SD.begin(BUILTIN_SDCARD)) {
      Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
      while(1);
    }

    accel.begin();
    gyro.begin();

    pinMode(24, INPUT_PULLUP);
    pinMode(25, INPUT_PULLUP);

    Wire2.begin();
    if (myGNSS.begin(Wire2) == false) { //Connect to the u-blox module using Wire port {
      Serial.println(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
      while (1);
    }

    myGNSS.checkUblox();
    String filename = String(myGNSS.getYear()) + "-" + String(myGNSS.getMonth()) + "-" + String(myGNSS.getDay()) +\
                    "-" + String(myGNSS.getHour()) + ":" + String(myGNSS.getMinute()) + ":" + String(myGNSS.getSecond() + ".bin");
    file = SD.open(filename.c_str(), FILE_WRITE);
  }

   Serial.println("H");

  Can.begin();
  Can.setBaudRate(500000); //set to 500000 for normal Megasquirt usage - need to change Megasquirt firmware to change MS CAN baud rate
  Can.setMaxMB(16); //sets maximum number of mailboxes for FlexCAN_T4 usage
  Can.enableFIFO();
  Can.enableFIFOInterrupt();
  Can.mailboxStatus();
  Can.onReceive(handler); //when a CAN message is received, runs the canMShandler function

   Serial.println("started can B");
}
CAN_message_t msg;

int i = 0;
void loop() {
  // // Serial.println(99);
  // // writting(ecu);
  // // // set_rpm(7000);
  // i += 1;
  // if (i > 14) {
  //   i = 0;
  // }
  // digitalWrite(ALL_LEDS[i], HIGH);
  // delay(1000);
  // for (int j = 0; j < 14; j++) {  
  //     digitalWrite(ALL_LEDS[j], LOW);
  //   }
  //  Serial.println("started can 2");
  Can.events(); 
}
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
    for (int j = 0; j <= (numLeds*2) && j < 14; j = j+2) {  
      digitalWrite(ALL_LEDS[j], HIGH);
   
      digitalWrite(ALL_LEDS[j+1], HIGH);
    }
   
  } 
  else {
    for (int j = 0; j < 14; j++) {
      digitalWrite(ALL_LEDS[j], HIGH);
    }
    // delay(500);
    for (int j = 0; j < 14; j++) {
      digitalWrite(ALL_LEDS[j], LOW);
    }
    // delay(500);
    for (int j = 0; j < 14; j++) {
      digitalWrite(ALL_LEDS[j], HIGH);
    }
  }
}