#include <stdio.h>

// A
// ~x

// B
// x

// C
// ~(x & 0xFF)

// D
// get_msb(x);

int get_msb(int x)
{
    int shift_val = (sizeof(int) - 1) << 3;
    int xright = x >> shift_val;
    return xright & 0xFF;
}