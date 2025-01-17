#include "MegaSquirt3.h"
#include "SevenSegment.h"
#include "Selector.h"

const int SELECTOR_PINS[] = {35, 36, 37, 38, 39, 40};
const int CHECK_ENGINE = 27;
const int SHIFT_GREEN[] = {4, 5, 6, 7, 8, 9};
const int SHIFT_YELLOW[] = {2, 3, 10, 11};
const int SHIFT_RED[] = {0, 1, 12, 26};

SevenSegment display1(0x70, &Wire);
// SevenSegment display2(0x70, &Wire1);
Selector selector(SELECTOR_PINS);
MegaSquirt3 ecu;

void handler(const CAN_message_t &msg) {
  MegaCAN_broadcast_message_t data;

  if (ecu.decode(msg, data)) {
    // check engine
    bool engine_bad = true;
    digitalWrite(CHECK_ENGINE, engine_bad ? HIGH : LOW);

    // shift lights
    // if (rpm > 7000) digitalWrite(SHIFT_GREEN, HIGH)//......

    // show displays
    switch (selector.get()) {
      case OFF:
        display1.show("....");
        break;
      case RPM:
        display1.show(data.rpm);
        break;
      case COOLANT:
        display1.show(data.clt);
        break;
      case BATTERY:
        display1.show(data.batt);
        break;
      case THROTTLE_POS:
        display1.show(data.tps);
        break;
      case GEAR:
        display1.show(data.gear);
        break;
      default:
        display1.show("    ");
        break;
    }
  }
}

void setup() {
  for (int i: SHIFT_GREEN) pinMode(i, OUTPUT);
  for (int i: SHIFT_YELLOW) pinMode(i, OUTPUT);
  for (int i: SHIFT_RED) pinMode(i, OUTPUT);
  pinMode(CHECK_ENGINE, OUTPUT);

  selector.initialize();
  display1.initialize();
  ecu.initialize(handler);
}

void loop() {
  ecu.eventloop();
}