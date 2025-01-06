// A
// 因为表达式里有size_t，因此计算结果自动升级为无符号数，而无符号数>=0恒成立

// B
// if(maxbytes >= (int)sizeof(val))
// 不用加(int)也可以，因为两边正常来说都是正数，但是使用(int)更稳妥，万一maxbytes是负数呢？
