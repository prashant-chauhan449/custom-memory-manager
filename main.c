#include <stdio.h>
#include "memory_operations.h"

int main()
{
    int choice;
    unsigned int requested_size;
    int allocation_id;

    struct MemoryManager manager = {0};

    do
    {
        printf("\n=====================================\n");
        printf("       CUSTOM MEMORY MANAGER\n");
        printf("=====================================\n");

        printf("1. Initialize Memory Pool\n");
        printf("2. Allocate Memory\n");
        printf("3. Free Memory\n");
        printf("4. Display Memory Layout\n");
        printf("5. Memory Statistics\n");
        printf("6. Select Allocation Strategy\n");
        printf("7. Display Allocation Details\n");
        printf("8. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                initialize_memory(&manager);
                break;

            case 2:
                printf("Enter memory size to allocate: ");
                scanf("%zu", &requested_size);

                allocate_memory(&manager, requested_size);
                break;

            case 3:
                printf("Enter Allocation ID: ");
                scanf("%d", &allocation_id);

                free_memory(&manager, allocation_id);
                break;

            case 4:
                display_memory(&manager);
                break;

            case 5:
                display_statistics(&manager);
                break;

            case 6:
                select_strategy(&manager);
                break;

            case 7:
                display_allocations(&manager);
                break;

            case 8:
                destroy_memory(&manager);
                printf("Exiting Memory Manager...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }

    } while (choice != 8);

    return 0;
}