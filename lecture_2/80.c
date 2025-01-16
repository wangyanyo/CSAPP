#include <stdio.h>
#include <assert.h>
#include <limits.h>

// 3/4 * x，首先将x分为左右两个部分，f = x & ~0x3，l = x & 0x3
// f 可以正常先 >>2，然后 (f << 1) + f，不会有舍入的问题
// 但是l * 3/4后可能会大于1，会有舍入问题，可以先 *3 再 /4
// 为什么会这样呢，因为 l*3/4 = l/4*3 的结果是相同的
// 因为除就是乘，都是乘3/4，但是换个顺序，先乘后除就能解决舍入的问题
// 加减乘除的优先级要大于位运算


int threeforths(int x)
{
    int is_neg = x & INT_MIN;
    int f = ~0x3 & x;
    int l = 0x3 & x;

    int fd4 = f >> 2;
    int fd4m3 = (fd4 << 1) + fd4;

    int lm3 = (l << 1) + l;
    (is_neg && (lm3 += ((1 << 2) - 1)));
    int lm3d4 = lm3 >> 2;

    return fd4m3 + lm3d4;
}

int main()
{
    assert(threeforths(8) == 6);
    assert(threeforths(9) == 6);
    assert(threeforths(10) == 7);
    assert(threeforths(11) == 8);
    assert(threeforths(12) == 9);

    assert(threeforths(-8) == -6);
    assert(threeforths(-9) == -6);
    assert(threeforths(-10) == -7);
    assert(threeforths(-11) == -8);
    assert(threeforths(-12) == -9);
    return 0;
}