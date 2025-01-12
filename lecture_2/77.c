#include <stdio.h>
#include <assert.h>

// 方法是找两个2的幂的组合，是其能算出目标数，比如 -7 = 1 - 8, -112 = 16 - 128

int main()
{
    int x = 0x1234;

    // A
    assert(x * 17 == x + (x << 4));

    // B ?
    assert(x * -7 == x - (x << 3));

    // C
    assert(x * 60 == (x << 6) - (x << 2));

    // D
    assert(x * -112 == (x << 4) - (x << 7));
}