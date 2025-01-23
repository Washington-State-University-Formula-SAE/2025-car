#include "MegaSquirt3.h"

#include "SevenSegment.h"
#include "Selector.h"

const int SELECTOR_PINS[] = {35, 36, 37, 38, 39, 40};
const int CHECK_ENGINE = 27;
const int SHIFT_GREEN[] = {4, 5, 6, 7, 8, 9};
const int SHIFT_YELLOW[] = {2, 3, 10, 11};
const int SHIFT_RED[] = {0, 1, 12, 26};
const int ALL_LEDS[] = {7,8,9,10,11,12,26,    1,0,2,3,4,5,6};

SevenSegment display1(0x70, &Wire);
// SevenSegment display2(0x70, &Wire1);
Selector selector(SELECTOR_PINS);
MegaSquirt3 ecu;
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can;

void handler(const CAN_message_t &msg) {
  
  if (ecu.decode(msg)) {
      // Serial.println(msg.id);

    // check engine
    bool engine_bad = true;
    digitalWrite(CHECK_ENGINE, engine_bad ? HIGH : LOW);

    // shift lights
    // if (rpm > 7000) digitalWrite(SHIFT_GREEN, HIGH)//......

    // show displays
    display1.show(ecu.data.map);
    // Serial.println(ecu.data.map);
    // DASHBOARD_STATE v = (DASHBOARD_STATE)2;
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

    double maxled = a * 14;

    for (int i=0;i<14;i++) {
      int pin = ALL_LEDS[i];
      if (i+1 <= maxled + 0.2) digitalWrite(pin, HIGH);
      else digitalWrite(pin, LOW);
    }
  }
}

void setup() {
  for (int i: SHIFT_GREEN) {pinMode(i, OUTPUT);digitalWrite(i, HIGH);}
  for (int i: SHIFT_YELLOW) {pinMode(i, OUTPUT);digitalWrite(i, HIGH);}
  for (int i: SHIFT_RED) {pinMode(i, OUTPUT);digitalWrite(i, HIGH);}
  pinMode(CHECK_ENGINE, OUTPUT);

  Serial.begin(9600);

  selector.initialize();
  display1.initialize();
  // this->callback = callback;

  Can.begin();
  Can.setBaudRate(500000); //set to 500000 for normal Megasquirt usage - need to change Megasquirt firmware to change MS CAN baud rate
  Can.setMaxMB(16); //sets maximum number of mailboxes for FlexCAN_T4 usage
  Can.enableFIFO();
  Can.enableFIFOInterrupt();
  Can.mailboxStatus();
  Can.onReceive(handler); //when a CAN message is received, runs the canMShandler function
}
CAN_message_t msg;

void loop() {
  // Serial.println("loop...");

  // display1.show(selector.get());
  Can.events();
}