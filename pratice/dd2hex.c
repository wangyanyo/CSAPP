#include <csapp.h>

#define MAX(x, y) (x > y) ? x : y

char i2h(int x) 
{
    if(x >= 10) {
        return x - 10 + 'a';
    }
    else {
        return x + '0';
    }
}
void print_i2h(int res)
{
    int cnt = 0;
    char tmp[8];

    while(res) {
        tmp[cnt++] = i2h(res % 16);
        res /= 16;
    }

    for(int i = 1; i >= cnt; --i) {
        printf("0");
    }
    for(int i = cnt - 1; i >= 0; --i) {
        printf("%c", tmp[i]);
    }
}
int main(int argc, char* argv[])
{
    if(argc != 2) {
        printf("error1\n");
        return 0;
    }

    char* str = argv[1];
    int n = strlen(str), res = 0;

    printf("0x");
    for(int i = 0; i < n; ++i) {
        if(str[i] == '.') {
            print_i2h(res);
            res = 0;
            continue;
        }

        res = res * 10 + (str[i] - '0');
    }
    print_i2h(res);
    printf("\n");

    return 0;
}