#ifndef WEB_H
#define WEB_H

#include <csapp.h>
#include <stdint.h>
#include <stddef.h>

struct addrinfo {
    int             ai_flags;
    int             ai_family;
    int             ai_socktype;    // 3种类型，连接、数据报、原始套接字，我们只用到连接
    int             ai_protocol;
    char            *ai_canonname;
    size_t          ai_addrlen;
    struct sockaddr *ai_addr;
    struct addrinfo *ai_next;
};

#endif