#include <stdio.h>
#include "memory_operations.h"

void display_memory(struct MemoryManager *manager)
{
    if (manager == NULL || manager->initialized == 0)
    {
        printf("Memory pool is not initialized.\n");
        return;
    }

    printf("\n========== MEMORY LAYOUT ==========\n\n");

    printf("%-10s %-10s %-10s %-12s\n",
           "Block", "Start", "Size", "Status");

    printf("-----------------------------------------------\n");

    for (int i = 0; i < manager->block_count; i++)
    {
        printf("%-10d %-10zu %-10zu %-12s\n",
               i,
               manager->blocks[i].start,
               manager->blocks[i].size,
               manager->blocks[i].is_free ? "FREE" : "ALLOCATED");
    }

    printf("\n===================================\n");
}

void display_statistics(struct MemoryManager *manager)
{
    if (manager == NULL || manager->initialized == 0)
    {
        printf("Memory pool is not initialized.\n");
        return;
    }

    unsigned int used_memory = 0;
    unsigned int  free_memory = 0;
    unsigned int largest_free_block = 0;

    int allocated_blocks = 0;
    int free_blocks = 0;

    for (int i = 0; i < manager->block_count; i++)
    {
        if (manager->blocks[i].is_free == 0)
        {
            used_memory += manager->blocks[i].size;
            allocated_blocks++;
        }
        else
        {
            free_memory += manager->blocks[i].size;
            free_blocks++;

            if (manager->blocks[i].size > largest_free_block)
            {
                largest_free_block = manager->blocks[i].size;
            }
        }
    }

    float external_fragmentation = 0.0f;

    if (free_memory > 0)
    {
        external_fragmentation =
            (1.0f - (float)largest_free_block / free_memory) * 100.0f;
    }

    printf("\n========== MEMORY STATISTICS ==========\n\n");

    printf("Total Memory           : %d bytes\n", MEMORY_POOL_SIZE);
    printf("Used Memory            : %zu bytes\n", used_memory);
    printf("Free Memory            : %zu bytes\n", free_memory);
    printf("Allocated Blocks       : %d\n", allocated_blocks);
    printf("Free Blocks            : %d\n", free_blocks);
    printf("Largest Free Block     : %zu bytes\n", largest_free_block);
    printf("External Fragmentation : %.2f%%\n",
           external_fragmentation);

    printf("\n=======================================\n");
}

void display_allocations(struct MemoryManager *manager)
{
    if (manager == NULL || manager->initialized == 0)
    {
        printf("Memory pool is not initialized.\n");
        return;
    }

    int found = 0;

    printf("\n========== ALLOCATION DETAILS ==========\n\n");

    printf("%-10s %-12s %-10s\n",
           "ID", "Start", "Size");

    printf("----------------------------------------\n");

    for (int i = 0; i < manager->block_count; i++)
    {
        if (manager->blocks[i].is_free == 0)
        {
            printf("%-10d %-12zu %-10zu\n",
                   manager->blocks[i].allocation_id,
                   manager->blocks[i].start,
                   manager->blocks[i].size);

            found = 1;
        }
    }

    if (found == 0)
    {
        printf("No active allocations found.\n");
    }

    printf("\n========================================\n");
}