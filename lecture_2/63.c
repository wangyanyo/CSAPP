#include <stdio.h>
#include <assert.h>

// 假如k==8
// 首先制作出 mask = 0xFFFFFF00，如果x符号位是1(负数)，则 mask = 0xFFFFFF00 & (!(1) - 1) = 0xFFFFFF00，若x符号位是0，则
// mask = 0xFFFFFF00 & (!(0) - 1) = 0x00000000。那算术->逻辑就是 x & ~mask，把前面的1消掉，正数不变；逻辑->算术就是
// x | mask，给前面加上1，正数不变。

// 用算术右移实现逻辑右移
unsigned sr1(unsigned x, int k)
{
    unsigned xsra = (int) x >> k;

    int w = sizeof(int) << 3;
    int mask = (int) -1 << (w - k);
    
    int flag = x >> (w - 1);
    mask &= !flag - 1;

    return xsra & ~mask;
}

// 用逻辑右移实现算术右移
int sra(int x, int k)
{
    int xsr1 = (unsigned) x >> k;
    
    int w = sizeof(int) << 3;
    int mask = (unsigned) -1 << (w - k);

    int flag = x >> (w - 1);
    mask &= !flag - 1;

    return xsr1 | mask;
}

int main()
{
    // 一个16进制位相当于4个二进制位
    int x = 1, y = -1;
    assert(y == 0xFFFFFFFF);
    assert(sr1(x, 1) == 0);
    assert(sra(x, 1) == 0);
    assert(sr1(y, 1) == 0x7FFFFFFF);
    assert(sra(y, 1) == 0xFFFFFFFF);
}