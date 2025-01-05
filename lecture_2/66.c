#include <stdio.h>
#include <assert.h>

// 使用了类似倍增的思路，最左边的1的左边都是0，因此可以把右边都设置成1，然后右移加一
int leftmost_one(unsigned x)
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return (x >> 1) + (x && 1);
}

int main()
{
    assert(leftmost_one(0xFF00) == 0x8000);
    assert(leftmost_one(0x6600) == 0x4000);
}