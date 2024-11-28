#include <csapp.h>

void mmapcopy(int fd, int size)
{
    void* bufp = Mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    Write(1, bufp, size);
}

int main(int argc, char* argv[])
{
    struct stat stat;
    int fd;

    if(argc != 2)
    {
        printf("usage: %s <filename>\n", argv[0]);
        exit(0);
    }

    fd = Open(argv[1], O_RDONLY, 0);
    Fstat(fd, &stat);
    mmapcopy(fd, stat.st_size);
    exit(0);
}