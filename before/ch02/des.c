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
