#include "des.h"
#include "outputHelper.h"

#include <iostream>

using namespace std;

uint32_t rotl(uint32_t input, uint8_t count) {
  uint32_t overflow = input >> (28 - count);
  uint32_t result = (0b1111111111111111111111111111ul & ((uint64_t) input << count)) | overflow;

  return result;
}

uint64_t permutate(uint64_t input, uint8_t inputSize, uint8_t outputSize, uint8_t lut[]) {
  uint64_t output = 0;

  for (uint8_t i = 0; i < outputSize; i++) {
    uint8_t offset = inputSize-lut[i];
    bool newBit = 1 & (input >> offset);
    output |= (uint64_t) newBit << outputSize-1-i;
  }

  return output;
}

void generateSubkeys(uint64_t key, uint64_t subkeys[]) {
  uint64_t kp = permutate(key, 64, 56, subkeyPermutateLUT_1);
  uint64_t kpC = 0b11110000110011001010101011110101010101100110011110001111;

  // Split into halves
  uint32_t c[16], d[16];
  c[0] = 0b1111111111111111111111111111 & (kp >> 28);
  d[0] = 0b1111111111111111111111111111 & kp;
  uint64_t cd = ((uint64_t) c[0] << 28) | d[0];

  /*
  dumpBits64("K", key);
  dumpBits56("K+", kp);
  dumpBits56("KC", kpC);
  dumpBits28("C0", c[0]);
  dumpBits28("D0", d[0]);
  cout << endl;
  */

  for (int i = 0; i < 16; i++) {
    c[i+1] = rotl(c[i], subkeyRotateLUT[i]);
    d[i+1] = rotl(d[i], subkeyRotateLUT[i]);
    uint64_t cd = ((uint64_t) c[i+1] << 28) | d[i+1];

    subkeys[i] = permutate(cd, 56, 48, subkeyPermutateLUT_2);

    /*
    cout << "C" << i+1;
    dumpBits28("", c[i+1]);
    cout << "D" << i+1;
    dumpBits28("", d[i+1]);
    cout << "CD" << i+1;
    dumpBits56("", cd);
    cout << "K" << i+1;
    dumpBits48("", subkeys[i]);
    cout << endl;
    */
  }
}
