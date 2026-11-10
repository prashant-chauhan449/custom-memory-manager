#include<stdio.h>
#include<stdlib.h>

#include "memory_operations.h"

int initialize_memory(struct MemoryManager * manager){
    if(manager->initialized==1){
        printf("Memory pool is already initialized\n");
        return 0;
    }

    manager->memory_pool = malloc(MEMORY_POOL_SIZE);
    if(manager->memory_pool == NULL){
        printf("Memory Allocation Failed.\n");
        return 0;
    }

    manager->blocks[0].start = 0;
    manager->blocks[0].size = MEMORY_POOL_SIZE;
    manager->blocks[0].is_free = 1;
    manager->blocks[0].allocation_id = 1;

    manager->block_count = 1;
    manager->next_allocation_id = 1;
    manager->initialized = 1;
    manager->strategy = FIRST_FIT;

    printf("Memory pool initialized successfully\n");

    return 1;
}


void destroy_memory(struct MemoryManager *manager)
{
    if (manager->memory_pool != NULL)
    {
        free(manager->memory_pool);
        manager->memory_pool = NULL;

        printf("Memory pool destroyed successfully.\n");
    }

    manager->block_count = 0;
    manager->initialized = 0;
}


void select_strategy(struct MemoryManager *manager)
{
    if (manager == NULL || manager->initialized == 0)
    {
        printf("Memory pool is not initialized.\n");
        return;
    }

    int choice;

    printf("\n========== ALLOCATION STRATEGY ==========\n");
    printf("1. First Fit\n");
    printf("2. Best Fit\n");
    printf("3. Worst Fit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case FIRST_FIT:
            manager->strategy = FIRST_FIT;
            printf("First Fit selected successfully.\n");
            break;

        case BEST_FIT:
            manager->strategy = BEST_FIT;
            printf("Best Fit selected successfully.\n");
            break;

        case WORST_FIT:
            manager->strategy = WORST_FIT;
            printf("Worst Fit selected successfully.\n");
            break;

        default:
            printf("Invalid strategy choice.\n");
            break;
    }
}