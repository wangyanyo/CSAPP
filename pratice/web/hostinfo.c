#define __USE_XOPEN2K

#include "web.h"

int main(int argc, char *argv[])
{
    struct addrinfo *p, *listp, hint;
    char buf[MAXLINE];
    int rc, flags;

    if(argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    memset(&hint, 0x00, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    if(rc = getaddrinfo(argv[1], NULL, &hint, &listp) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
    }

    flags = 1;
    for(p = listp; p; p = p->ai_next) {
        // getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        printf("%d\n", p->ai_addr);
    }

    freeaddrinfo(listp);

    exit(0);
}