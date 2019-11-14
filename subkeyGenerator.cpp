#include "des.h"

void generateSubkeys(uint64_t key, uint64_t subkeys[]) {
  uint64_t stubkeys[] = {
    0b000110110000001011101111111111000111000001110010,
    0b011110011010111011011001110110111100100111100101,
    0b010101011111110010001010010000101100111110011001,
    0b011100101010110111010110110110110011010100011101,
    0b011111001110110000000111111010110101001110101000,
    0b011000111010010100111110010100000111101100101111,
    0b111011001000010010110111111101100001100010111100,
    0b111101111000101000111010110000010011101111111011,
    0b111000001101101111101011111011011110011110000001,
    0b101100011111001101000111101110100100011001001111,
    0b001000010101111111010011110111101101001110000110,
    0b011101010111000111110101100101000110011111101001,
    0b100101111100010111010001111110101011101001000001,
    0b010111110100001110110111111100101110011100111010,
    0b101111111001000110001101001111010011111100001010,
    0b110010110011110110001011000011100001011111110101,
  };

  for(int i = 0; i < 16; i++) {
    subkeys[i] = stubkeys[i];
  }
}
