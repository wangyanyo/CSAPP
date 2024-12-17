#include <csapp.h>

/************************************************************************/

// 20个页的堆空间
#define MAX_HEAP 4096 * 20

#define WSIZE       4
#define DSIZE       8
#define CHUNKSIZE  (1<<12)

// #define 定义操作的话要注意加括号
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

// 如果是我写的话，我不会加上(char *)，但那是错的。因为指针的运算规则和它的类型有关
// 若想要按照正常的运算规则，那就要把指针转成(char *)
#define HDRP(bp) ((char *)bp - WSIZE)
#define FTRP(bp) ((char *)bp + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp) ((char *)bp + GET_SIZE((char *)bp - WSIZE))
#define PREV_BLKP(bp) ((char *)bp - GET_SIZE((char *)bp - DSIZE))

#define PACK(size, flag) ((size) & ~0x7) | ((flag) & 0x7)

static void *extend_heap(size_t words);
static void *coalesce(void* bp);

/************************************************************************/

static char *mem_heap;
static char *mem_brk;
static char *mem_max_addr;

void mem_init(void)
{
    mem_heap = (char *)Malloc(MAX_HEAP);
    mem_brk = mem_heap;
    mem_max_addr = (char *)(mem_heap + MAX_HEAP);
}

void *mem_sbrk(int incr)
{
    char *old_brk = mem_brk;
    if((incr < 0) || ((mem_brk + incr) > mem_max_addr)) {
        errno = ENOMEM;
        fprintf(stderr, "ERROR: mem_sbrk failed. Ran out of memory...\n");
        return (void *)-1;
    }
    mem_brk += incr;
    return (void*)old_brk;
}

/************************************************************************/

static char* heap_listp;

int mm_init(void)
{
    if((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1) {
        return -1;
    }

    PUT(heap_listp, 0);
    PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (3*WSIZE), PACK(0, 1));

    heap_listp += (2*WSIZE);

    if(extend_heap(CHUNKSIZE) == NULL) {
        return -1;
    }

    return 0;
}

static void *extend_heap(size_t words) 
{
    char* bp;
    size_t size;

    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
    if((long)(bp = mem_sbrk(size)) == -1)
        return NULL;

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

    return coalesce(bp);
}

static void *coalesce(void* bp)
{
    // 处理四种情况
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    // 情况1
    if(prev_alloc && next_alloc) {
        return bp;
    }
    // 情况2
    else if(prev_alloc && !next_alloc) {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    }
    // 情况3
    else if(!prev_alloc && next_alloc) {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    // 情况4
    else {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp))) +
            GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    return bp;
}

void mm_free(void *bp)
{
    if(bp == NULL) return;

    void* tmp_bp = HDRP(bp);
    size_t size = GET_SIZE(tmp_bp);

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));

    coalesce(bp);
}

static void place(void *bp, size_t size) {
    size_t blk_size = GET_SIZE(HDRP(bp));

    if(blk_size - size >= DSIZE * 2) {
        size_t tmp_size = blk_size - size;
        PUT(HDRP(bp), PACK(size, 1));
        PUT(FTRP(bp), PACK(size, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(tmp_size, 0));
        PUT(FTRP(bp), PACK(tmp_size, 0));
    }
    else {
        PUT(HDRP(bp), PACK(blk_size, 1));
        PUT(FTRP(bp), PACK(blk_size, 1));
    }
}

static void *find_fit(size_t size)
{
    for(void* bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if(!GET_ALLOC(HDRP(bp)) && GET_SIZE(HDRP(bp)) >= size) {
            return bp;
        }
    }

    return NULL;
}

void *mm_malloc(size_t size)
{
    size_t asize;
    size_t extend_size;
    char *bp;

    if (size == 0) {
        return NULL;
    }

    if(size <= DSIZE) 
        asize = 2 * DSIZE;
    else
        asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE);

    if((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    extend_size = MAX(asize, CHUNKSIZE);
    if((bp = extend_heap(extend_size / WSIZE)) == NULL) 
        return NULL;

    place(bp, asize);
    return bp;
}

int main()
{
    mem_init();
    mm_init();

    void* p1 = mm_malloc(16);
    void* p2 = mm_malloc(16);

    mm_free(p1);
    mm_free(p2);

    void* p3 = mm_malloc(32);
    printf("%x %x %x\n", p1, p2, p3);

    // 分配块 和 合并空闲块 都没问题
}