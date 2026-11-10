#include <stdio.h>
#include "memory_operations.h"

int free_memory(struct MemoryManager *manager, int allocation_id)
{
    if (manager == NULL || manager->initialized == 0)
    {
        printf("Memory pool is not initialized.\n");
        return 0;
    }

    if (allocation_id <= 0)
    {
        printf("Invalid allocation ID.\n");
        return 0;
    }

    for (int i = 0; i < manager->block_count; i++)
    {
        if (manager->blocks[i].is_free == 0 &&
            manager->blocks[i].allocation_id == allocation_id)
        {
            manager->blocks[i].is_free = 1;
            manager->blocks[i].allocation_id = -1;

            merge_free_blocks(manager);

            printf("Memory freed successfully.\n");
            return 1;
        }
    }

    printf("Invalid allocation ID or memory already freed.\n");
    return 0;
}

void merge_free_blocks(struct MemoryManager *manager)
{
    int i = 0;

    while (i < manager->block_count - 1)
    {
        if (manager->blocks[i].is_free == 1 &&
            manager->blocks[i + 1].is_free == 1)
        {
            manager->blocks[i].size +=
                manager->blocks[i + 1].size;

            for (int j = i + 1;
                 j < manager->block_count - 1;
                 j++)
            {
                manager->blocks[j] = manager->blocks[j + 1];
            }

            manager->block_count--;
        }
        else
        {
            i++;
        }
    }
}