#include <stdio.h>
#include <assert.h>

// 题意是判断低n位的补码值与原值相同
int fits_bits(int x, int n)
{
    int w = sizeof(int) << 3;
    int offset = w - n;
    return (x << offset >> offset) == x;
}

int main()
{
    assert(fits_bits(0b00000011, 3));
    assert(!fits_bits(0b00000101, 3));
    assert(fits_bits(0xFFFFFFF8, 4));
    assert(!fits_bits(0xFFFFFFF0, 4));
}