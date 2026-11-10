
#ifndef MEMORY_OPERATIONS_H
#define MEMORY_OPERATIONS_H

#include "memory_manager.h"

/* Memory Initialization */
int initialize_memory(struct MemoryManager *manager);

/* Memory Allocation */
void *allocate_memory(struct MemoryManager *manager, unsigned int requested_size);

/* Memory Deallocation */
int free_memory(struct MemoryManager *manager, int allocation_id);

/* Allocation Strategy */
void select_strategy(struct MemoryManager *manager);

/* Memory Display */
void display_memory(struct MemoryManager *manager);

void display_statistics(struct MemoryManager *manager);

void display_allocations(struct MemoryManager *manager);

/* Memory Block Operations */
int find_free_block(struct MemoryManager *manager, unsigned int requested_size);

int split_block(struct MemoryManager *manager, int block_index, unsigned int requested_size);

void merge_free_blocks(struct MemoryManager *manager);

/* Memory Cleanup */
void destroy_memory(struct MemoryManager *manager);

#endif
