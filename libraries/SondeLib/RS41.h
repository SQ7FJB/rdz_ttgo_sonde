/*
 * RS41.h
 * Functions for decoding RS41 sondes with SX127x chips
 * Copyright (C) 2019 Hansi Reiser, dl9rdz
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef RS41_h
#define RS41_h

#include <stdlib.h>
#include <stdint.h>
#include <Arduino.h>
#ifndef inttypes_h
        #include <inttypes.h>
#endif

/* Main class */
class RS41
{
private:
	uint32_t bits2val(const uint8_t *bits, int len);
	void printRaw(uint8_t *data, int len);
	int bitsToBytes(uint8_t *bits, uint8_t *bytes, int len);
	void decode41(byte *data, int maxlen);

#define B 8
#define S 4
	uint8_t hamming_conf[ 7*B];  //  7*8=56
	uint8_t hamming_dat1[13*B];  // 13*8=104
	uint8_t hamming_dat2[13*B];

	uint8_t block_conf[ 7*S];  //  7*4=28
	uint8_t block_dat1[13*S];  // 13*4=52
	uint8_t block_dat2[13*S];

	uint8_t H[4][8] =  // extended Hamming(8,4) particy check matrix
             {{ 0, 1, 1, 1, 1, 0, 0, 0},
              { 1, 0, 1, 1, 0, 1, 0, 0},
              { 1, 1, 0, 1, 0, 0, 1, 0},
              { 1, 1, 1, 0, 0, 0, 0, 1}};
	uint8_t He[8] = { 0x7, 0xB, 0xD, 0xE, 0x8, 0x4, 0x2, 0x1};  // Spalten von H:
                                                            // 1-bit-error-Syndrome

public:
	RS41();
	int setup();
	int setFrequency(float frequency);
	int receiveFrame();

	int use_ecc = 1;
};

extern RS41 rs41;

#endif