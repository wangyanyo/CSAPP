#include<stdio.h>
#include<assert.h>

 void mySolve() {
    unsigned int x, y;
    scanf("%x %x", &x, &y);
    printf("%x\n", (x & 0xFF) | (y & ~(0xFF)));
}

signed main() {
    size_t mask = 0xFF;
    size_t x = 0x89ABCDEF;
    size_t y = 0x76543210;

    size_t res = (x & mask) | (y & ~mask);
    assert(res == 0x765432EF);

    return 0;
}
