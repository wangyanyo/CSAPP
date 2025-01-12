#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <limits.h>

// 感觉这题出的有问题，因为(x << 1) + x 和 x * 3 没区别，除法也都是补码除法
// 因此就是复现了一遍 x * 3 / 4

// 补码除法，正数向下舍入，负数向上舍入
int divide_power2(int x, int k)
{
    int is_neg = x & INT_MIN;
    (is_neg && (x = x + (1 << k) - 1));
    return x >> k;
}

int mul3div4(int x)
{
    // 这样就不会溢出了吗？感觉和x*3没区别
    int mul3 = (x << 1) + x;
    return divide_power2(mul3, 2);
}

int main()
{
    int x = 0x3f3f3f3f;
    assert(mul3div4(x) == x * 3 / 4);
    return 0;
}