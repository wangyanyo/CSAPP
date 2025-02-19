#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void *another_calloc(size_t nmemb, size_t size)
{
    if(nmemb == 0 || size == 0) {
        return NULL;
    }

    size_t buf_size = nmemb * size;
    if(nmemb == buf_size / size) {
        void *ptr = malloc(buf_size);
        if(ptr != NULL) {
            memset(ptr, 0, buf_size);
        }
        return ptr;
    }

    return NULL;
}

int main()
{
    void *p;
    p = another_calloc(0x1234, 1);
    assert(p != NULL);
    free(p);

    p = another_calloc(SIZE_MAX, 2);
    assert(p == NULL);
    free(p);

    return 0;
}