#include "MegaSquirt3.h"
#include "SevenSegment.h"
#include "Selector.h"

const int SELECTOR_PINS[] = {1, 2, 3, 4, 5, 6, 7, 8};
const int CHECK_ENGINE = 13;
const int SHIFT_GREEN = 14;
const int SHIFT_YELLOW = 15;
const int SHIFT_RED = 16;

SevenSegment display1(0x70);
// SevenSegment display2;
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
        display1.show("    .");
        break;
      case RPM:
        display1.show(data.rpm);
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
      case MAP:
        display1.show(data.map);
        break;
      case BAROMETER:
        display1.show(data.baro);
        break;
      case COOLANT:
        display1.show(data.clt);
        break;
      default:
        display1.show("8888");
        break;
    }
  }
}

void setup() {
  pinMode(CHECK_ENGINE, OUTPUT);
  pinMode(SHIFT_GREEN, OUTPUT);
  pinMode(SHIFT_YELLOW, OUTPUT);
  pinMode(SHIFT_RED, OUTPUT);

  selector.initialize();
  display1.initialize();
  ecu.initialize(handler);
}

void loop() {
  digitalWrite(CHECK_ENGINE, HIGH);
  // display1.show((int)selector.get());
  ecu.eventloop();
}