#include <stdio.h>
#include <assert.h>

// A
// (-1) << k

// B
// ~(-1 << k) << j

int A(int k)
{
    return (-1) << k;
}

int B(int k, int j)
{
    return ~(-1 << k) << j;
}

int main()
{
    assert(A(8) == 0xFFFFFF00);
    assert(B(16, 8) == 0x00FFFF00);
    return 0;
}