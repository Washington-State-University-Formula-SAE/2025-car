#ifndef Selector_h
#define Selector_h

#include "Arduino.h"

// typedef enum dboard_state {
//   OFF,
//   RPM,
//   BATTERY,
//   THROTTLE_POS,
//   GEAR,
//   MAP,
//   BAROMETER,
//   COOLANT
// } DASHBOARD_STATE;

class Selector {
  const int* pins;
public:
  Selector(const int* pins) : pins(pins) {}
  
  void initialize();
  DASHBOARD_STATE get();
};

#endif