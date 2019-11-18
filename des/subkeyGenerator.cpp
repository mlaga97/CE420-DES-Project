#include "desInternal.h"
#include "outputHelper.h"

#include <iostream>

using namespace std;

uint32_t rotl(uint32_t input, uint8_t count) {
  uint32_t overflow = input >> (28 - count);
  uint32_t result = (0b1111111111111111111111111111ul & ((uint64_t) input << count)) | overflow;

  return result;
}

void generateSubkeys(uint64_t key, uint64_t subkeys[]) {
  uint64_t kp = permutate(key, 64, 56, subkeyPermutateLUT_1);

  // Split into halves
  uint32_t c[16], d[16];
  c[0] = 0b1111111111111111111111111111 & (kp >> 28);
  d[0] = 0b1111111111111111111111111111 & kp;
  uint64_t cd = ((uint64_t) c[0] << 28) | d[0];

  cout << "Key = ";
  dumpBits64(key);

  cout << "Permutated = ";
  dumpBits56(kp);

  cout << "keyLeft[0] = ";
  dumpBits28(c[0]);

  cout << "keyRight[0] = ";
  dumpBits28(d[0]);

  cout << endl;

  for (int i = 0; i < 16; i++) {
    c[i+1] = rotl(c[i], subkeyRotateLUT[i]);
    d[i+1] = rotl(d[i], subkeyRotateLUT[i]);
    uint64_t cd = ((uint64_t) c[i+1] << 28) | d[i+1];

    subkeys[i] = permutate(cd, 56, 48, subkeyPermutateLUT_2);

    cout << "### Subkey Round " << dec << i+1 << " ###########################################################" << endl;
    cout << "left = ";
    dumpBits28(c[i+1]);
    cout << "right = ";
    dumpBits28(d[i+1]);
    cout << "combined = ";
    dumpBits56(cd);
    cout << "subkey[" << i+1 << "] = ";
    dumpBits48(subkeys[i]);
    cout << endl;
  }
}
