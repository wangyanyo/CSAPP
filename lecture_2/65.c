#include <stdio.h>
#include <assert.h>

// 思路是尽量让一次异或操作计算更多位，方法就是折半异或，这样就能让每一位都参与了异或
// odd是奇数的意思
int odd_ones(unsigned x)
{
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    
    return x & 0x1;
}

signed main()
{
    assert(odd_ones(0x10101011));
    assert(!odd_ones(0x10101010));

    return 0;
}