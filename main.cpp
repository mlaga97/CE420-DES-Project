#include <regex>
#include <bitset>
#include <string>
#include <iostream>

#include "des.h"
#include "outputHelper.h" //TODO: Remove

// TODO: Remove
using namespace std;

int main() {
  uint64_t key = 0x133457799BBCDFF1;
  uint64_t block = 0x0123456789ABCDEF;

  uint64_t encrypted = des(block, key, false);
  uint64_t decrypted = des(encrypted, key, true);

  cout << hex;
  cout << block << endl;
  cout << encrypted << endl;
  cout << decrypted << endl;
}
