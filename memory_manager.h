
#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stddef.h>
#include "memory_blocks.h"

#define MEMORY_POOL_SIZE 1024

#define FIRST_FIT 1
#define BEST_FIT  2
#define WORST_FIT 3

struct MemoryManager
{
    unsigned char *memory_pool;
    struct MemoryBlock blocks[MAX_BLOCKS];
    unsigned int block_count;
    int next_allocation_id;
    int initialized;
    int strategy;
};

#endif
