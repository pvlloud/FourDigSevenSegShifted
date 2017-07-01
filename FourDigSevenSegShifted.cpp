#include "FourDigSevenSegShifted.h"

static const uint8_t digits[10] {
    0b00000011,
    0b10011111,
    0b00100101,
    0b00001101,
    0b10011001,
    0b01001001,
    0b01000001,
    0b00011111,
    0b00000001,
    0b00001001
  };

uint8_t digitPins[4];

static int positionIndecies[4][4] {
  {0, -1, -1, -1},
  {1, 0, -1, -1},
  {2, 0, 1, -1},
  {3, 0, 1, 2}
};

FourDigSevenSegShifted::FourDigSevenSegShifted(uint8_t latch_in, uint8_t clock_in, uint8_t data_in, uint8_t* pins) {
  latch = latch_in;
  clock = clock_in;
  data = data_in;
  for (int i = 0; i < 4; i++) {
    digitPins[i] = pins[i];
  }
}

void FourDigSevenSegShifted::pinsInitiate() {
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
}

void FourDigSevenSegShifted::displayPositionDigit(uint8_t position, uint8_t rawDigit) {
  int digit = rawDigit % 10;
  byte digitBytes = digits[digit];

  digitalWrite(digitPins[position], HIGH);
  digitalWrite(latch, LOW);
  shiftOut(data, clock, MSBFIRST, digitBytes);
  digitalWrite(latch, HIGH);
  digitalWrite(digitPins[position], LOW);
}

unsigned int FourDigSevenSegShifted::calcDigits(int number) {
  int outcome = 0;
  do {
    outcome++;
    number /= 10;
  } while (number != 0);
  return outcome;
}

void FourDigSevenSegShifted::displayNumber(int number) {
  int digitsCount = calcDigits(number);
  if (digitsCount > 4) {
    displayNumber(9999);
  }
  int *positionPins = positionIndecies[digitsCount - 1];
  for (int i = 0; i < digitsCount; i++) {
    displayPositionDigit(positionPins[i], number % 10);
    number /= 10;
  }
}
