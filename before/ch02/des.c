#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "des.h"
#include "hex.h"

#define GET_BIT(array, bit) \
(array[(int) (bit / 8)] & (0x80 >> (bit % 8)))
#define SET_BIT(array, bit) \
(array[(int) (bit / 8)] |= (0x80 >> (bit % 8)))
#define CLEAR_BIT(array, bit) \
(array[(int) (bit / 8)] &= ~(0x80 >> (bit % 8)))

static void xor(unsigned char *target, const unsigned char *src, int len) {
    while (len--) {
        *target++ ^= *src++;
    }
}

static void permute(unsigned char target[], const unsigned char src[], const int permute_table[], int len) {
    int i;
    for (i = 0; i < len * 8; i++) {
        if (GET_BIT(src, (permute_table[i] - 1))) {
            SET_BIT(target, i);
        } else {
            CLEAR_BIT(target, i);
        }
    }
}

// terse initial permutation
static void terse_initial_permute(unsigned char input[], unsigned char output[]) {
    int i;
    for (i = 1; i != 8; i = (i + 2) % 9) {
        for (int j = 7; j >= 0; j--) {
            output[(i % 2) ? ((i - 1) >> 1) : ((4 + (i >> 1)))] |=
                    ((input[j] & (0x80 >> i)) >> (7 - i)) << j;
        }
    }
}

// initial permutation table
static const int ip_table[] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9,  1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7 };
