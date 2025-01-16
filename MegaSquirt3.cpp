#include "MegaSquirt3.h"


void MegaSquirt3::initialize(_MB_ptr callback) {
  // this->callback = callback;

  Can.begin();
  Can.setBaudRate(500000); //set to 500000 for normal Megasquirt usage - need to change Megasquirt firmware to change MS CAN baud rate
  Can.setMaxMB(16); //sets maximum number of mailboxes for FlexCAN_T4 usage
  Can.enableFIFO();
  Can.enableFIFOInterrupt();
  Can.onReceive(callback); //when a CAN message is received, runs the canMShandler function
  Can.mailboxStatus();
}

void MegaSquirt3::eventloop() {
  Can.events();
}

bool MegaSquirt3::decode(const CAN_message_t &msg, MegaCAN_broadcast_message_t& data) {
  if (!msg.flags.extended) {
    megaCAN.getBCastData(msg.id, msg.buf, data);
    if (msg.id == 1513) {
      return true;
    }
  }
  return false;
}