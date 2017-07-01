#ifndef FourDigSevenSegShifted_h
#define FourDigSevenSegShifted_h

#include <Arduino.h>

class FourDigSevenSegShifted {
private:
  uint8_t latch;
  uint8_t clock;
  uint8_t data;

public:
  FourDigSevenSegShifted(uint8_t latch_in, uint8_t clock_in, uint8_t data_in, uint8_t* pins);
  void pinsInitiate();
  void displayPositionDigit(uint8_t position, uint8_t rawDigit);
  unsigned int calcDigits(int number);
  void displayNumber(int number);
};

#endif
