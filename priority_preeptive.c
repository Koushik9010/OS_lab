#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to perform priority scheduling
void priorityScheduling(int n, int at[], int bt[], int priority[], int rt[], int highest_priority, int lowest_priority, int id[], int ct[], int tat[], int wt[]) {
    int current_time = 0;  // Initialize current_time to 0
    int completed = 0;     // Initialize completed processes to 0

    printf("Gantt Chart:\n");

    // Main scheduling loop
    while (completed < n) {
        int index = -1;                 // Initialize index of selected process to -1
        int selected_priority = INT_MAX; // Initialize selected_priority to maximum value

        // Iterate over processes to find the one with the highest priority
        for (int i = 0; i < n; i++) {
            // Check if the process is ready to execute and has the specified priority range
            if (at[i] <= current_time && rt[i] > 0 && priority[i] >= highest_priority && priority[i] <= lowest_priority) {
                // Update the selected process if it has higher priority
                if (priority[i] < selected_priority) {
                    selected_priority = priority[i];
                    index = i;
                }
            }
        }

        // If a process is found
        if (index != -1) {
            printf("| P%d |", id[index]); // Display Gantt Chart for the selected process
            rt[index]--;

            // Check if the process has completed its execution
            if (rt[index] == 0) {
                completed++;
                ct[index] = current_time + 1;
                tat[index] = ct[index] - at[index];
                wt[index] = tat[index] - bt[index];
            }

            current_time++; // Increment time for the next iteration
        } else {
            // If no process can be scheduled, increment the current_time
            current_time++;
        }
    }

    printf("\n");
}

// Function to display results
void displayResults(int n, int id[], int priority[], int at[], int bt[], int ct[], int tat[], int wt[]) {
    printf("Process\t\tPriority\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    // Display details for each process
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t  %d\t\t  %d\t\t  %d\t\t  %d\t\t  %d\t\t  %d\n", id[i], priority[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    // Calculate and display average turnaround time and average waiting time
    float total_tat = 0;
    float total_wt = 0;

    for (int i = 0; i < n; i++) {
        total_tat += tat[i];
        total_wt += wt[i];
    }

    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int highest_priority, lowest_priority;
    printf("Enter the highest priority: ");
    scanf("%d", &highest_priority);
    printf("Enter the lowest priority: ");
    scanf("%d", &lowest_priority);

    int id[n];
    int at[n];
    int bt[n];
    int priority[n];
    int ct[n];
    int tat[n];
    int wt[n];
    int rt[n];

    // Input details for each process
    for (int i = 0; i < n; i++) {
        id[i] = i + 1;
        printf("Process P%d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority: ");
        scanf("%d", &priority[i]);
        rt[i] = bt[i];
    }

    // Call the priority scheduling function
    priorityScheduling(n, at, bt, priority, rt, highest_priority, lowest_priority, id, ct, tat, wt);

    // Display the results
    displayResults(n, id, priority, at, bt, ct, tat, wt);

    return 0;
}
