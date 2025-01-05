#include <stdio.h>
#include <assert.h>

// A
// 左移位数超过了类型长度

// B
int int_size_is_32_B()
{
    int set_msb = 1 << 31;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

// C
int int_size_is_32_C()
{
    int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = set_msb << 1;
    
    return set_msb && !beyond_msb;
}

int main()
{
    assert(int_size_is_32_B());
    assert(int_size_is_32_C());
}