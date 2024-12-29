#include <stdio.h>
#include <assert.h>

// 只要有任意一个偶数位是1就返回1，其他返回0
int any_odd_one(unsigned x) 
{
    return !!(x & 0xAAAAAAAA);
}

signed main()
{
    assert(any_odd_one(0x2));
    assert(!any_odd_one(0x4));

    return 0;
}

