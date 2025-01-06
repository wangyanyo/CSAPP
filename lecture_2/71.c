#include <stdio.h>
#include <assert.h>

// A
// 如果抽出的字节是负数，没有补全前面的1

// B
// 一开始，我假设通过移位获得了目标字节0xAA，现在要给它前3个字节都赋值为0xFF
// 但是要用减法和移位来实现这一点，那就必须要用到-1，并且减法用来收尾，但没想法
// 硬要搞的话也行，但是我没注意到这个问题的环境，即packed_t最大4字节和算术右移
// 可以把目标字节移到最右边，然后用算术右移补全前面的1
typedef unsigned packed_t;
int xbyte(packed_t word, int bytenum)
{
    int max_bytenum = 3;
    return (int)word << ((max_bytenum - bytenum) << 3) >> (max_bytenum << 3);
}

int main()
{
    assert(xbyte(0x80FFFFFF, 3) == 0xFFFFFF80);
    assert(xbyte(0xFF80FFFF, 2) == 0xFFFFFF80);
}