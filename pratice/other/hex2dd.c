#include <csapp.h>


int h2i(char c)
{
    if(c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }    
    else {
        return c - '0';
    }
}

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("error\n");
        return 0;
    }

    char *str = argv[1];
    int n = strlen(str);
    if(str[0] != '0' || str[1] != 'x') {
        printf("error\n");
        return 0;
    }

    for(int i = 2; i < n; i += 2) {
        if(i != 2) {
            printf(":");
        }
        
        int res = (h2i(str[i]) * 16 + h2i(str[i + 1]));
        printf("%d", res);
    }
    printf("\n");

    return 0;
}