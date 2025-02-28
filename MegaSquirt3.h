#ifndef MegaSquirt3_h
#define MegaSquirt3_h

#include "Arduino.h"
#include <FlexCAN_T4.h>
#include <MegaCAN.h>

#define CAN_BASE_ID 1512
#define CAN_ID CAN_BASE_ID + 1




typedef struct row {
  uint32_t write_millis;
  uint32_t ecu_millis;
  uint32_t gps_millis;
  uint32_t imu_millis;
  uint32_t accel_millis;
  uint32_t analogx1_millis;
  int rpm;
  int time;
  int afr;
  int spark_advance;
  int baro;
  int map;
  int mat;
  int clnt_temp;
  int tps;
  int batt;
  int oil_press;
  int syncloss_count;
  int syncloss_code;
  int ltcl_timing;
  int ve1;
  int ve2;
  int egt;
  int maf;
  int in_temp;
  int lat;
  int lon;
  int elev;
  int hour;
  int minute;
  int second;
  int ground_speed;
  int ax;
  int ay;
  int az;
  int imu_x;
  int imu_y;
  int imu_z;
} ROW;


class MegaSquirt3 {
  MegaCAN megaCAN;

public:
  MegaCAN_broadcast_message_t data;

  MegaSquirt3() : megaCAN(CAN_BASE_ID) {}
  void initialize();
  void eventloop();
  bool decode(const CAN_message_t &msg);
};

#endif