#include "outputHelper.h"

using namespace std;

// TODO: Why tho?
void dumpBits28(string name, uint64_t input) {
  cout << name << " = ";
  for(int i = 4; i < 8; i++) {
    cout << bitset<7>(0b1111111 & (input >> ((7-i)*7))) << " ";
  }
  cout << endl;
}

void dumpBits32(string name, uint64_t input) {
  cout << name << " = ";
  for(int i = 0; i < 8; i++) {
    cout << bitset<4>(0b1111 & (input >> ((7-i)*4))) << " ";
  }
  cout << endl;
}

void dumpBits48(string name, uint64_t input) {
  cout << name << " = ";
  for(int i = 0; i < 8; i++) {
    cout << bitset<6>(0b111111 & (input >> ((7-i)*6))) << " ";
  }
  cout << endl;
}

void dumpBits56(string name, uint64_t input) {
  cout << name << " = ";
  for(int i = 0; i < 8; i++) {
    cout << bitset<7>(0b1111111 & (input >> ((7-i)*7))) << " ";
  }
  cout << endl;
}

void dumpBits64(string name, uint64_t input) {
  cout << name << " = ";
  for(int i = 0; i < 8; i++) {
    cout << bitset<8>(0b11111111 & (input >> ((7-i)*8))) << " ";
  }
  cout << endl;
}
