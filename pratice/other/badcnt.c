#include <csapp.h>

void *thread(void *vargp);
sem_t mutex;        // sem_t 本质上是一个union，它要么是一个size为32的字节数组，要么是一个long int类型的变量

volatile long cnt = 0;

int main(int argc, char *argv[])
{
    long niters;
    pthread_t tid1, tid2;       // pthread_t 其实就是 unsigned long int

    if(argc != 2) {
        printf("usage: %s <niters>\n", argv[0]);
        exit(0);
    }

    sem_init(&mutex, 0, 1);

    niters = atoi(argv[1]);

    Pthread_create(&tid1, NULL, thread, niters);    // thread例程只是给线程的上下文提供了IP值，最后一个参数是例程的参数
    Pthread_create(&tid2, NULL, thread, niters);
    Pthread_join(tid1, NULL);
    Pthread_join(tid2, NULL);

    if(cnt != (2 * niters)) {
        printf("BOOM! cnt = %ld\n", cnt);
    }
    else {
        printf("OK cnt = %ld\n", cnt);
    }

    exit(0);
}

void *thread(void *vargp)
{
    long i, niters = (long)vargp;

    for(int i = 0; i < niters; ++i) {
        P(&mutex);      // 看不到sem_wait()和sem_post()的定义，但我猜应该是用原子操作+sigsuspend()+信号实现的。
        cnt++;
        V(&mutex);
    }

    return NULL;
}