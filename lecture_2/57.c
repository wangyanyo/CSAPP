// 实验结果：小端存储
// long 类型是8字节的？这个有点出乎我意料啊

#include<stdio.h>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for(i = 0; i < len; ++i) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer)&x, sizeof(x));
}

void show_float(float x) {
    show_bytes((byte_pointer)&x, sizeof(x));
}

void show_short(short x) {
    show_bytes((byte_pointer)&x, sizeof(x));
}

void show_long(long x) {
    show_bytes((byte_pointer)&x, sizeof(x));
}

void show_double(double x) {
    show_bytes((byte_pointer)&x, sizeof(x));
}

void show_longlong(long long x) {
    show_bytes((byte_pointer)&x, sizeof(x));
}

signed main() {
    show_int(100);
    show_float(100.0f);
    show_short(100);
    show_long(100l);
    show_double(100.0);
    show_longlong(100);
}
