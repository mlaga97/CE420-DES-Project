#pragma once

#include "des.h"

uint32_t sbox(uint64_t input);
void generateSubkeys(uint64_t key, uint64_t* subkeys);
uint32_t roundFunction(uint32_t right, uint64_t subkey);
uint64_t permutate(uint64_t input, uint8_t size, uint8_t *lut);
uint64_t permutate(uint64_t input, uint8_t inputSize, uint8_t outputSize, uint8_t lut[]);

// Initial and final permutations
extern uint8_t ipLUT[64];
extern uint8_t fpLUT[64];

// Rounds
extern uint8_t expandLUT[48];
extern uint8_t sboxLUT[8][4][16];
extern uint8_t roundPermutateLUT[32];

// Key generation
extern uint8_t subkeyRotateLUT[16];
extern uint8_t subkeyPermutateLUT_1[56];
extern uint8_t subkeyPermutateLUT_2[48];
