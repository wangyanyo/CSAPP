#include <stdio.h>
#include <assert.h>

// 因为优先级更高的幂数在更高位，优先级更低的基数在更低位，因此可以直接比较
// 可见该书对二进制理解之深，而我却过于依赖答案，但又不能没有答案
// 按照星级来决定做题时间，*->5分钟，**->20分钟，***->2小时，****->10小时
// 如果提前做完并感觉没问题可以提前看答案，不再强加每天5题的限制，以质量为优先
// 并且我有疑惑的题都是要在二周目再做一遍的
// 本书的四星题不多，那要改变一下策略:
// 如果有四星题，那么今天只做四星题
// 如果没有四星题，那么每天最多做两道三星题
// 其余情况按每天5题来算

unsigned f2u(float x)
{
    // 精彩，归根结底x只是一堆二进制，那么怎么强制更改这个二进制的解释方式呢？
    // 答案是指针，指针就是(解释 + 地址)，void类型指针只有地址
    // 只要使用(unsigned *)类型的指向x就可以了
    return *(unsigned*)&x;
}

int float_le(float x, float y)
{
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    return (ux << 1 == 0 && uy << 1 == 0) ||
        (sx && !sy) ||
        (sx && sy && ux >= uy) || 
        (!sx && !sy && ux <= uy);
}

int main()
{
    assert(float_le(-0, +0));
    assert(float_le(+0, -0));
    assert(float_le(0, 4));
    assert(float_le(1, 4));
    assert(float_le(-8, -2));

    return 0;
}