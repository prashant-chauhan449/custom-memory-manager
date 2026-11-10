#include "memory_operations.h"
#include<stdio.h>5
int find_free_block(struct MemoryManager * manager,unsigned int requested_size){
    int selected_index = -1;
    unsigned int selected_size = 0;

    for(int i =0;i< manager->block_count;i++){
        if(manager->blocks[i].is_free == 1 && manager->blocks[i].size>=requested_size){
            if(manager->strategy == FIRST_FIT){
                return i;
            }
            if(manager->strategy == BEST_FIT){
                if(selected_index == -1 || manager->blocks[i].size<selected_size){
                    selected_index = i;
                    selected_size = manager->blocks[i].size;
                }
            }
            if (manager->strategy == WORST_FIT){
                if (selected_index == -1 ||
                    manager->blocks[i].size > selected_size)
                {
                    selected_index = i;
                    selected_size = manager->blocks[i].size;
                }
            }
        }
    }
    return selected_index;
}

int split_block(struct MemoryManager *manager,
                int block_index,
                unsigned int requested_size)
{
    unsigned int original_start = manager->blocks[block_index].start;
    unsigned int original_size = manager->blocks[block_index].size;

    unsigned int remaining_size = original_size - requested_size;
    unsigned int remaining_start = original_start + requested_size;

    manager->blocks[block_index].size = requested_size;
    manager->blocks[block_index].is_free = 0;
    manager->blocks[block_index].allocation_id =
        manager->next_allocation_id;

    if (remaining_size > 0 &&
        manager->block_count >= MAX_BLOCKS)
    {
        return 0;
    }
    for (int i = manager->block_count;
         i > block_index + 1;
         i--)
    {
        manager->blocks[i] = manager->blocks[i - 1];
    }

    manager->blocks[block_index + 1].start = remaining_start;
    manager->blocks[block_index + 1].size = remaining_size;
    manager->blocks[block_index + 1].is_free = 1;
    manager->blocks[block_index + 1].allocation_id = -1;

    manager->block_count++;

    return 1;
}

void *allocate_memory(struct MemoryManager *manager,
                      unsigned int requested_size)
{
    if (manager == NULL || manager->initialized == 0 ||
        manager->memory_pool == NULL)
    {
        printf("Memory pool is not initialized.\n");
        return NULL;
    }

    if (requested_size == 0)
    {
        printf("Invalid memory request.\n");
        return NULL;
    }

    int block_index = find_free_block(manager, requested_size);

    if (block_index == -1)
    {
        printf("Not enough free memory available.\n");
        return NULL;
    }

    if (split_block(manager, block_index, requested_size) == 0)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    void *allocated_address =
        manager->memory_pool + manager->blocks[block_index].start;

    manager->next_allocation_id++;

    printf("Memory allocated successfully.\n");
    printf("Allocation ID: %d\n",
           manager->blocks[block_index].allocation_id);

    return allocated_address;
}