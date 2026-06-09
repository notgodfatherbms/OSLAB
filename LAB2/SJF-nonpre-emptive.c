#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int wt;
    int tat;
    int resp;
    int started;
    int completed;
    struct process *next;
};

struct process *head = NULL;

void insert(int id, int arrival, int burst) {
    struct process *newnode = (struct process*)malloc(sizeof(struct process));
    newnode->pid = id;
    newnode->at = arrival;
    newnode->bt = burst;
    newnode->rt = burst;
    newnode->completed = 0;
    newnode->wt = 0;
    newnode->tat = 0;
    newnode->ct = 0;
    newnode->resp = -1;
    newnode->started = 0;
    newnode->next = NULL;

    if (head == NULL) {
        head = newnode;
    } else {
        struct process *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newnode;
    }
}

void sort_by_arrival() {
    struct process *i, *j;
    int temp_pid, temp_at, temp_bt, temp_rt;

    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->at > j->at) {
                temp_at = i->at; i->at = j->at; j->at = temp_at;
                temp_bt = i->bt; i->bt = j->bt; j->bt = temp_bt;
                temp_rt = i->rt; i->rt = j->rt; j->rt = temp_rt;
                temp_pid = i->pid; i->pid = j->pid; j->pid = temp_pid;
            }
        }
    }
}

void non_preemptive_sjf(int n) {
    int completed_count = 0;
    int current_time = 0;

    while (completed_count < n) {
        struct process *temp = head;
        struct process *shortest = NULL;
        int min_bt = 1000000;

        while (temp != NULL) {
            if (temp->at <= current_time && temp->completed == 0) {
                if (temp->bt < min_bt) {
                    min_bt = temp->bt;
                    shortest = temp;
                } else if (temp->bt == min_bt && shortest != NULL && temp->at < shortest->at) {
                    shortest = temp;
                }
            }
            temp = temp->next;
        }

        if (shortest == NULL) {
            temp = head;
            int earliest = 1000000;
            while (temp != NULL) {
                if (temp->completed == 0 && temp->at < earliest) {
                    earliest = temp->at;
                }
                temp = temp->next;
            }
            current_time = earliest;
            continue;
        }

        if (shortest->resp == -1) {
            shortest->resp = current_time - shortest->at;
            if (shortest->resp < 0) shortest->resp = 0;
        }

        shortest->wt = current_time - shortest->at;
        if (shortest->wt < 0) shortest->wt = 0;
        current_time += shortest->bt;
        shortest->ct = current_time;
        shortest->tat = shortest->ct - shortest->at;
        shortest->completed = 1;
        completed_count++;
    }
}

void preemptive_sjf(int n) {
    int completed = 0;
    int current_time = 0;

    while (completed < n) {
        struct process *temp = head;
        struct process *shortest = NULL;
        int min_rt = 1000000;

        while (temp != NULL) {
            if (temp->at <= current_time && temp->completed == 0 && temp->rt < min_rt) {
                min_rt = temp->rt;
                shortest = temp;
            }
            temp = temp->next;
        }

        switch (shortest != NULL) {
            case 1:
                if (shortest->resp == -1) {
                    shortest->resp = current_time - shortest->at;
                    if (shortest->resp < 0) shortest->resp = 0;
                }

                shortest->rt -= 1;
                current_time++;

                if (shortest->rt == 0) {
                    shortest->completed = 1;
                    shortest->ct = current_time;
                    shortest->tat = shortest->ct - shortest->at;
                    shortest->wt = shortest->tat - shortest->bt;
                    completed++;
                }
                break;

            case 0:
                current_time++;
                break;
        }
    }
}

void display() {
    struct process *temp = head;
    float total_wt = 0, total_tat = 0, total_rt = 0;
    int n = 0;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    while (temp != NULL) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               temp->pid, temp->at, temp->bt, temp->ct, temp->tat, temp->wt, temp->resp);
        total_wt += temp->wt;
        total_tat += temp->tat;
        total_rt += temp->resp;
        n++;
        temp = temp->next;
    }
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Response Time = %.2f\n", total_rt / n);
}

int main() {
    int n, i, at, bt, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        printf("\nProcess P%d\n", i);
        printf("Arrival Time: ");
        scanf("%d", &at);
        printf("Burst Time: ");
        scanf("%d", &bt);
        insert(i, at, bt);
    }

    sort_by_arrival();

    printf("\nSelect Scheduling Type:\n");
    printf("1. Non-Preemptive SJF\n");
    printf("2. Preemptive SJF (SRTF)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            non_preemptive_sjf(n);
            break;
        case 2:
            preemptive_sjf(n);
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }

    display();

    return 0;
}
