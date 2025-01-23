# wazzu racing fsae CAN software

## wiring
CAN:
  - ECU: green H, purple L
  - Breadboarding: green H, red L
  - AnalogX: green H, white L

AnalogX Sensors:
  - 5V: pink and lighter pink
  - GND: brown and green
  - Device 1: white
  - Device 2: yellow
  - Device 3: blue
  - Device 4: grey

## data
AnalogX:
  - CAN id of `935444`
  - data is little endian:
    - 8 values: `a, A, b, B, c, C, d, D`
    - device 1 value (0-1) is `(a + (A<<8))/5024.0` (have to bitshift big byte)

ECU:
  - who knows... currently in "dashboard" mode I think. can id of maybe `1514` for now?
  - https://www.msextra.com/doc/pdf/Megasquirt_CAN_Broadcast.pdf
