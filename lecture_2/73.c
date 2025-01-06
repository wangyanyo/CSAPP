#include <stdio.h>
#include <assert.h>
#include <limits.h>

// 优雅，把INT_MIN当作mask，用逻辑表达式的短路来代替if else
// 可见对补码和二进制理解之深
int saturating_add(int x, int y)
{
    int sum = x + y;
    int sig_mask = INT_MIN;

    int pos_over = !(x & sig_mask) && !(y & sig_mask) && (sum & sig_mask);
    int neg_over = (x & sig_mask) && (y & sig_mask) && !(sum & sig_mask);

    (pos_over && (sum = INT_MAX)) || (neg_over && (sum = INT_MIN));

    return sum;
}

int main()
{
    assert(saturating_add(0x7FFFFFFF, 0x7FFFFFFF) == INT_MAX);
    assert(saturating_add(0x80000000, 0x80000000) == INT_MIN);
    assert(saturating_add(1, 1) == 2);
}