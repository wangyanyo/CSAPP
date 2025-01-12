#include <stdio.h>
#include <assert.h>
#include <limits.h>

// 正数向下舍入，负数向上舍入
// 向上舍入加一个偏置值，加(1 << k)然后减1，如果低k位有值，则加的(1 << k)有效，否则无效，这样就向上舍入了1位
// 10000000 + 10000 - 1 = 10001111 >> 4 = 1000 取消向上舍入
// 10000100 + 10000 - 1 = 10010011 >> 4 = 1001 成功向上舍入

int divide_power2(int x, int k)
{
    int is_neg = x & INT_MIN;
    (is_neg && (x = x + (1 << k) - 1));
    return x >> k;
}

int main()
{
    int x = 0x80000007;
    assert(divide_power2(x, 1) == x / 2);
    assert(divide_power2(x, 2) == x / 4);
    return 0;
}