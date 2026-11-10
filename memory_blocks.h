#ifndef MEMORY_BLOCKS_H
#define MEMORY_BLOCKS_H
#include <stddef.h>


#define MAX_BLOCKS 1024
struct MemoryBlock{
    unsigned int start;
    unsigned int size;
    int is_free;
    int allocation_id;
};

#endif