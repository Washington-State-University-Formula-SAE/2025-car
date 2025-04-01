#include "Selector.h"

void Selector::initialize() {
  for (int i=0;i<6;i++) {
    pinMode(pins[i], INPUT);
  }
}

DASHBOARD_STATE Selector::get() {
    for (int i=0;i<6;i++) {
      if (digitalRead(pins[i]) == HIGH) {
        return (DASHBOARD_STATE)i;
      }
    }
    return OFF;
}