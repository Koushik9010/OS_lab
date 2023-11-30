#include<stdio.h>

// Define a structure to represent a process
struct process
{
    int id;     // process ID
    int at;     // arrival time
    int bt;     // burst time
    int tat;    // turnaround time
    int ct;     // completion time
    int wt;     // waiting time
    int rt;     // remaining time
};

// Function to perform Round Robin scheduling
void roundRobin(int n, int time_quantum)
{
    // Declare an array of structures to store process details
    struct process p[n];

    // Initialize variables for current time and completed processes
    int current_time = 0;
    int completed = 0;

    // Input process details
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        printf("Enter the arrival time for p%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter the burst time for process p%d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;  // Remaining time initially equals burst time
    }

    // Perform Round Robin scheduling
    while (completed < n)
    {
        // Iterate through each process
        for (int i = 0; i < n; i++)
        {
            if (p[i].rt > 0)
            {
                // Execute the process for the time quantum
                if (p[i].rt <= time_quantum)
                {
                    current_time += p[i].rt;
                    p[i].rt = 0;
                }
                else
                {
                    current_time += time_quantum;
                    p[i].rt -= time_quantum;
                }

                // Check if the process is completed
                if (p[i].rt == 0)
                {
                    completed++;
                    p[i].ct = current_time;             // Set completion time
                    p[i].tat = p[i].ct - p[i].at;       // Calculate turnaround time
                    p[i].wt = p[i].tat - p[i].bt;       // Calculate waiting time
                }
            }
        }
    }

    // Calculate and display statistics
    float total_tat = 0;
    float total_wt = 0;

    printf("p\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;
    printf("\nAverage TAT: %.2f\n", avg_tat);
    printf("Average WT: %.2f\n", avg_wt);
}

// Main function
int main()
{
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    // Call the Round Robin scheduling function
    roundRobin(n, time_quantum);

    return 0;
}
