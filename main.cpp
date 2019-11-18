#include <regex>
#include <bitset>
#include <string>
#include <iostream>
#include <cmath>

#include "des/des.h"

int main(int argc, char** argv) {
  uint64_t key, block;
  int option = 1;

  key = 0x133457799BBCDFF1;
  block = 0x57202C6F6C6C6548;

  des(block, key, false);
  return 0;

  while (1) {
    switch(option) {
      case 0:
        return 0;
      case 1:
        std::cout << "Please enter your key: ";
        std::cin >> std::hex >> key;
        break;
      case 2:
        std::cout << "Please enter your block: ";
        std::cin >> std::hex >> block;
        std::cout << std::endl;
        des(block, key, false);
        break;
      case 3:
        std::cout << "Please enter your block: ";
        std::cin >> std::hex >> block;
        std::cout << std::endl;
        des(block, key, true);
        break;
    }
    std::cout << std::endl;

    std::cout << "Please select an option: " << std::endl;
    std::cout << " 1) Change key" << std::endl;
    std::cout << " 2) Encrypt a hex block" << std::endl;
    std::cout << " 3) Decrypt a hex block" << std::endl;
    std::cout << " 0) Exit" << std::endl;

    std::cout << std::endl << "> ";
    std::cin >> std::dec >> option;
    std::cout << std::endl;
  }
}
