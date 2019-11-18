#include "desInternal.h"
#include "outputHelper.h"

using namespace std;

// Handle special case where input and output size are identical
uint64_t permutate(uint64_t input, uint8_t size, uint8_t *lut) {
  permutate(input, size, size, lut);
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

uint32_t sbox(uint64_t input) {
  uint32_t output = 0;

  // Split input into 8 parts
  for (uint8_t i = 0; i < 8; i++) {
    uint8_t in = 0b111111 & (input >> ((7-i)*6)); // Get relevant 6-bit chunk

    // Get the two components
    uint8_t x = ((0b100000 & in) >> 4) | (0b000001 & in);
    uint8_t y = 0b1111 & (in >> 1);

    // Look it up
    uint8_t out = sboxLUT[i][x][y];

    output |= out << ((7-i)*4);
  }

  return output;
}

uint32_t roundFunction(uint32_t right, uint64_t subkey) {
  uint64_t expandedBlock = permutate(right, 32, 48, expandLUT);
  uint64_t xoredBlock = expandedBlock ^ subkey;
  uint32_t sboxed = sbox(xoredBlock);
  uint32_t result = permutate(sboxed, 32, roundPermutateLUT);

  /*
  dumpBits48("K1", subkey);
  dumpBits32("R0", right);
  dumpBits48("E(R0)", expandedBlock);
  dumpBits48("K1+E(R0) = B", xoredBlock);
  dumpBits32("S(B)", sboxed);
  dumpBits32("S(B)", 0b11111111111111111111111111111111 >> 31);
  dumpBits32("P(S(B)) = f", result);
  */

  return result;
}

uint64_t des(uint64_t block, uint64_t key, bool decrypt) {
  uint64_t subkeys[16];
  uint32_t left[32], right[32];
  uint64_t initialPermutation;

  cout << "################################################################################" << endl;
  cout << "# DES" << endl;

  cout << "## Inputs" << endl;
  cout << "Key   = " << hex << key << endl;
  cout << "Block = " << hex << block << endl;
  cout << endl;

  cout << "## Subkey Generation" << endl;
  generateSubkeys(key, subkeys);
  cout << endl;

  // Perform Permutation
  initialPermutation = permutate(block, 64, ipLUT);
  left[0] = initialPermutation >> 32;
  right[0] = initialPermutation;

  // Dump Permutation Info
  cout << "## Initial Permutation" << endl;
  cout << "Data Block          = " << hex << block << endl;
  cout << "                    = ";
  dumpBits64(block);
  cout << endl;

  cout << "Initial Permutation = ";
  dumpBits64(initialPermutation);
  cout << endl;
  cout << "                    = " << hex << initialPermutation << endl;

  // Run the Rounds
  cout << endl;
  cout << "## Rounds" << endl;
  for (int i = 1; i <= 16; i++) {
    uint32_t result;

    cout << "### Round " << dec << i << endl;

    // Invert subkey order for decryption
    if (decrypt) {
      cout << "Subkey = " << hex << subkeys[16-i] << endl;
      result = roundFunction(right[i-1], subkeys[16-i]);
    } else {
      cout << "Subkey = " << hex << subkeys[i-1] << endl;
      result = roundFunction(right[i-1], subkeys[i-1]);
    }

    right[i] = left[i-1] ^ result;
    left[i] = right[i-1];

    cout << endl;
  }

  // Perform Final Permutation
  uint64_t round16_combined = ((uint64_t) right[16] << 32) | left[16];
  uint64_t finalPermutation = permutate(round16_combined, 64, fpLUT);

  // Dump Final Permutation
  cout << "## Final Permutation" << endl;
  cout << "left[16]  = " << hex << left[16] << endl;
  cout << "right[16] = " << hex << right[16] << endl;
  cout << endl;

  cout << "Round 16 Combined  = " << hex << round16_combined << endl;
  cout << "Final Permutation  = " << hex << finalPermutation << endl;


  cout << "################################################################################" << endl;

  return finalPermutation;
}
