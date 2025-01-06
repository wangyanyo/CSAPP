#include <stdio.h>
#include <assert.h>

signed rorate_left(unsigned x, int n)
{
    int size = sizeof(unsigned) << 3;
    return (x << n) | (x >> (size - n));
}

int main()
{
    assert(rorate_left(0x12345678, 4) == 0x23456781);
    assert(rorate_left(0x12345678, 20) == 0x67812345);
}