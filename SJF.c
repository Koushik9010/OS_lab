#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct Process {
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

void swap(struct Process* a, struct Process* b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void sjf(struct Process processes[], int n) {
    int time = 0;
    int total_ct = 0;
    int total_tat = 0;
    int total_wt = 0;
    bool executed[n];

    for (int i = 0; i < n; i++) {
        executed[i] = false;
    }

    printf("Process\t\tArrival_time\t\tBurst_time\t\tCompletion_time\t\tTurn_around_time\t\tWaiting_time\n");

    while (total_ct < n) {
        int min_bt = INT_MAX;
        int min_burst_index = -1;

        for (int i = 0; i < n; i++) {
            if (!executed[i] && processes[i].at <= time && processes[i].bt < min_bt) {
                min_bt = processes[i].bt;
                min_burst_index = i;
            }
        }

        if (min_burst_index == -1) {
            time++;
        } else {
            int i = min_burst_index;
            executed[i] = true;
            time += processes[i].bt;
            processes[i].ct = time;
            processes[i].tat = processes[i].ct - processes[i].at;
            processes[i].wt = processes[i].tat - processes[i].bt;

            total_ct++;
            total_tat += processes[i].tat;
            total_wt += processes[i].wt;

            printf("P%2d\t\t%7d\t%19d\t%22d\t%25d\t%22d\n", processes[i].id, processes[i].at,
                   processes[i].bt, processes[i].ct,
                   processes[i].tat, processes[i].wt);
        }
    }

    float avg_tat = (float)total_tat / n;
    float avg_wt = (float)total_wt / n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process P%d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].at);
        printf("Burst Time: ");
        scanf("%d", &processes[i].bt);
    }

    sjf(processes, n);

    return 0;
}
