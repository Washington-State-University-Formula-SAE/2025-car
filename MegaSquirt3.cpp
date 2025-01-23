#include "MegaSquirt3.h"


void MegaSquirt3::initialize() {

}

void MegaSquirt3::eventloop() {
  // Can.events();
}

bool MegaSquirt3::decode(const CAN_message_t &msg) {
  if (!msg.flags.extended) {
    megaCAN.getBCastData(msg.id, msg.buf, data);
    if (msg.id <= 900000) {
          Serial.println(data.batt);

    // Serial.println(data.map);
      return true;
    }
  }
  return false;
}