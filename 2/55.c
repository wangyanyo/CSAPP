//实验结果：小端存储

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

signed main() {
    show_int(100);
    show_float(100.0f);
}
