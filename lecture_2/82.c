#include <stdio.h>
#include <assert.h>

// A
// (x < y) == (-x > -y)
// x==INT_MIN时错误

// B
// ((x + y) << 4) + y - x == 17 * y + 15 * x
// ((x + y) << 4) + y - x == 16 * x + 16 * y + y - x == 17 * y + 15 * x

// C
// ~x + ~y + 1 == ~(x + y)
// ~x + ~y + 1 = ~x + 1 + ~y + 1 - 1 = -x + -y - 1 = -(x + y) - 1 = ~(x + y) + 1 - 1 = ~(x + y)

// D
// (ux - uy) == -(unsigned)(y - x)
// (uy - ux) == (unsigned)(y - x) =>
// -(ux - uy) == (unsigned)(y - x) =>
// (ux - uy) == -(unsigned)(y - x)

// E
// ((x >> 2) << 2) <= x
// 如果x & 0x3 > 0，则((x >> 2) << 2) < x；如果x & 0x3 < 0，则((x >> 2) << 2) == x

int C(int x, int y)
{
    return ~x + ~y + 1 == ~(x + y);
}

int main()
{
    assert(C(0xFFFFFFFF, 0xFFFFFFFF));
}
