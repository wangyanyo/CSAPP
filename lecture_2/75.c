#include <stdio.h>
#include <assert.h>
#include <stdint.h>

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
    uint64_t mul = (uint64_t)x * y;
    return mul >> 32;
}

int signed_high_prod(int x, int y)
{
    int sig_x = (unsigned)x >> 31;
    int sig_y = (unsigned)y >> 31;

    return unsigned_high_prod(x, y) - (sig_x * y + sig_y * x) + sig_x * sig_y * (1 << 31);
}

// unsigned unsigned_high_prod(unsigned x, unsigned y)
// {
//     int sig_x = x >> 31;
//     int sig_y = y >> 31;
//     return signed_high_prod(x, y) + (sig_x * y + sig_y * x) + sig_x * sig_y * (1 << 31);
// }

int another_signed_high_prod(int x, int y)
{
    int64_t mul = (int64_t)x * y;
    return mul >> 32;
}

int main()
{
    int x = 0x12345678;
    int y = 0xFFFFFFFF;

    assert(signed_high_prod(x, y) == another_signed_high_prod(x, y));

    return 0;
}