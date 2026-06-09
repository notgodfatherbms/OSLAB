#include <stdio.h>

#define MAX 100

void firstFit(int blocks[], int m, int processes[], int n)
{
    int allocation[MAX];

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(blocks[j] >= processes[i])
            {
                allocation[i] = j;
                blocks[j] -= processes[i];
                break;
            }
        }
    }

    printf("\nFIRST FIT ALLOCATION\n");
    printf("Process\tSize\tBlock\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t", i + 1, processes[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blocks[], int m, int processes[], int n)
{
    int allocation[MAX];

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int bestIdx = -1;

        for(int j = 0; j < m; j++)
        {
            if(blocks[j] >= processes[i])
            {
                if(bestIdx == -1 || blocks[j] < blocks[bestIdx])
                    bestIdx = j;
            }
        }

        if(bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blocks[bestIdx] -= processes[i];
        }
    }

    printf("\nBEST FIT ALLOCATION\n");
    printf("Process\tSize\tBlock\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t", i + 1, processes[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blocks[], int m, int processes[], int n)
{
    int allocation[MAX];

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int worstIdx = -1;

        for(int j = 0; j < m; j++)
        {
            if(blocks[j] >= processes[i])
            {
                if(worstIdx == -1 || blocks[j] > blocks[worstIdx])
                    worstIdx = j;
            }
        }

        if(worstIdx != -1)
        {
            allocation[i] = worstIdx;
            blocks[worstIdx] -= processes[i];
        }
    }

    printf("\nWORST FIT ALLOCATION\n");
    printf("Process\tSize\tBlock\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t", i + 1, processes[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main()
{
    int m, n, choice;

    int blocks[MAX], processes[MAX];
    int tempBlocks[MAX];

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter sizes of memory blocks:\n");
    for(int i = 0; i < m; i++)
        scanf("%d", &blocks[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter sizes of processes:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &processes[i]);

    do
    {
        printf("\n----- MEMORY ALLOCATION MENU -----\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        for(int i = 0; i < m; i++)
            tempBlocks[i] = blocks[i];

        switch(choice)
        {
            case 1:
                firstFit(tempBlocks, m, processes, n);
                break;

            case 2:
                bestFit(tempBlocks, m, processes, n);
                break;

            case 3:
                worstFit(tempBlocks, m, processes, n);
                break;

            case 4:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 4);

    return 0;
}
