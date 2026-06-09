#include <stdio.h>

int main() {
    int n, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], wt[n], tat[n], rt[n];
    int temp;

    for(i = 0; i < n; i++) {
        pid[i] = i + 1;

        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(at[i] > at[j]) {

                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    int current_time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    for(i = 0; i < n; i++) {

        if(current_time < at[i]) {
            current_time = at[i];
        }

        rt[i] = current_time - at[i];
        current_time += bt[i];

        ct[i] = current_time;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i],
               ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Response Time = %.2f\n", total_rt / n);

    return 0;
}
