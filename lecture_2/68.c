#include <stdio.h>
#include <assert.h>

// 如果不加unsigned就是算术右移，加了就是逻辑右移
int lower_one_mask(int n)
{
    int size = sizeof(int) << 3;
    return (unsigned)-1 >> (size - n);
}

int main()
{
    assert(lower_one_mask(6) == 0x3F);
    assert(lower_one_mask(17) == 0x1FFFF);
}