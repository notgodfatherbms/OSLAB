#include <stdio.h>
#include <stdbool.h>

#define MAX 10

void bankers() {
    int n, m;
    int allocation[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int available[MAX];

    printf("\n--- Banker's Algorithm ---\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&allocation[i][j]);

    printf("Enter Max Matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&max[i][j]);

    printf("Enter Available Resources:\n");
    for(int i=0;i<m;i++)
        scanf("%d",&available[i]);

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            need[i][j] = max[i][j] - allocation[i][j];

    bool finish[MAX] = {false};
    int work[MAX], safeSeq[MAX];

    for(int i=0;i<m;i++)
        work[i] = available[i];

    int count = 0;

    while(count < n) {
        bool found = false;

        for(int i=0;i<n;i++) {
            if(!finish[i]) {
                int j;
                for(j=0;j<m;j++)
                    if(need[i][j] > work[j])
                        break;

                if(j == m) {
                    for(int k=0;k<m;k++)
                        work[k] += allocation[i][k];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found) {
            printf("System is NOT in safe state\n");
            return;
        }
    }

    printf("System is in SAFE state\nSafe sequence: ");
    for(int i=0;i<n;i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
}

void deadlock_detection() {
    int n, m;
    int allocation[MAX][MAX], request[MAX][MAX];
    int available[MAX];

    printf("\n--- Deadlock Detection ---\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&allocation[i][j]);

    printf("Enter Request Matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&request[i][j]);

    printf("Enter Available Resources:\n");
    for(int i=0;i<m;i++)
        scanf("%d",&available[i]);

    bool finish[MAX] = {false};
    int work[MAX];

    for(int i=0;i<m;i++)
        work[i] = available[i];

    while(1) {
        bool found = false;

        for(int i=0;i<n;i++) {
            if(!finish[i]) {
                int j;
                for(j=0;j<m;j++)
                    if(request[i][j] > work[j])
                        break;

                if(j == m) {
                    for(int k=0;k<m;k++)
                        work[k] += allocation[i][k];

                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found)
            break;
    }

    printf("Deadlocked processes: ");
    bool deadlock = false;

    for(int i=0;i<n;i++) {
        if(!finish[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }

    if(!deadlock)
        printf("None");

    printf("\n");
}

int main() {
    int choice;

    do {
        printf("\n1. Banker's Algorithm");
        printf("\n2. Deadlock Detection");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: bankers(); break;
            case 2: deadlock_detection(); break;
            case 3: printf("Exiting...\n"); break;
            default: printf("Invalid choice\n");
        }
    } while(choice != 3);

    return 0;
}
