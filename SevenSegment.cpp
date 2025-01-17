#include "SevenSegment.h"

void SevenSegment::initialize() {
  matrix.begin(reg, wire);
  matrix.print("----");
  matrix.writeDisplay();
}

void SevenSegment::show(int x, int base) {
  matrix.print(x, base);
  matrix.writeDisplay();
}

void SevenSegment::show(double x, int prec) {
  matrix.print(x, prec);
  matrix.writeDisplay();
}

void SevenSegment::show(const char* c) {
  matrix.print(c);
  matrix.writeDisplay();
}