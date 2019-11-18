#include "outputHelper.h"

using namespace std;

// TODO: Why tho?
void dumpBits28(uint64_t input) {
  for(int i = 4; i < 8; i++) {
    cout << bitset<7>(0b1111111 & (input >> ((7-i)*7))) << " ";
  }
  cout << " = " << hex << input << endl;
}

void dumpBits32(uint64_t input) {
  for(int i = 0; i < 8; i++) {
    cout << " " << bitset<4>(0b1111 & (input >> ((7-i)*4))) << "  ";
  }
  cout << " = " << hex << input << endl;
}

void dumpBits48(uint64_t input) {
  for(int i = 0; i < 8; i++) {
    cout << bitset<6>(0b111111 & (input >> ((7-i)*6))) << " ";
  }
  cout << " = " << hex << input << endl;
}

void dumpBits56(uint64_t input) {
  for(int i = 0; i < 8; i++) {
    cout << bitset<7>(0b1111111 & (input >> ((7-i)*7))) << " ";
  }
  cout << " = " << hex << input << endl;
}

void dumpBits64(uint64_t input) {
  for(int i = 0; i < 8; i++) {
    cout << bitset<8>(0b11111111 & (input >> ((7-i)*8))) << " ";
  }
  cout << " = " << hex << input << endl;
}
