#ifndef MegaSquirt3_h
#define MegaSquirt3_h

#include "Arduino.h"
#include <FlexCAN_T4.h>
#include <MegaCAN.h>

#define CAN_BASE_ID 1512
#define CAN_ID CAN_BASE_ID + 1


class MegaSquirt3 {
  FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can;
  MegaCAN megaCAN;

public:
  MegaSquirt3() : megaCAN(CAN_BASE_ID) {}
  void initialize(_MB_ptr callback);
  void eventloop();
  bool decode(const CAN_message_t &msg, MegaCAN_broadcast_message_t& data);
};

#endif