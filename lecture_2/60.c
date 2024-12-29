#include <stdio.h>
#include <assert.h>

unsigned replace_byte(unsigned x, int i, unsigned char b) 
{
    unsigned mask = ((unsigned) 0xFF) << (i << 3);
    unsigned pos_byte = ((unsigned) b) << (i << 3);

    return (x & ~mask) | pos_byte;
}

int main()
{
    unsigned rep_0 = replace_byte(0x12345678, 0, 0xAB);
    unsigned rep_2 = replace_byte(0x12345678, 2, 0xAB);

    assert(rep_0 == 0x123456AB);
    assert(rep_2 == 0x12AB5678);
    return 0;
}
