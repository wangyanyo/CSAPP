#include <stdio.h>
#include <assert.h>
#include <limits.h>

// 没说要遵守那个规则
int tsub_ok(int x, int y)
{
    int sub = x - y;

    int pos_over = x > 0 && y < 0 && sub < 0;
    int neg_over = x < 0 && y > 0 && sub > 0;

    return !(pos_over || neg_over);
}

int main()
{
    assert(tsub_ok(INT_MAX, INT_MIN) == 0);
    assert(tsub_ok(INT_MIN, INT_MAX) == 0);
    assert(tsub_ok(1, 1) == 1);
}
