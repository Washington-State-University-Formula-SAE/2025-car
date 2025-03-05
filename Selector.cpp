#include "Selector.h"

void Selector::initialize() {
  for (int i=0;i<6;i++) {
    pinMode(pins[i], INPUT_PULLDOWN);
  }
}

int Selector::get() {
    for (int i=0;i<6;i++) {
      if (digitalRead(pins[i]) == HIGH) {
        return (int)i;
      }
    }
    return 0;
}