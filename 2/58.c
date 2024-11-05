#include<stdio.h>

int is_little_endian() {
    int test_num = 0xFF;
    unsigned char* byte_start = (unsigned char*)&test_num;

    if(byte_start[0] == 0xFF) {
        return 1;
    }
    else return 0;
}

signed main() {
    printf("%d\n", is_little_endian());
}
