#include <stdio.h>
#include <limits.h>

void priority(int n, int at[], int bt[], int pri[], int ct[], int tat[], int wt[]) {
    int rt[n];
    for (int i = 0; i < n; i++) 
    {
        rt[i] = bt[i];
    }

    int current_time = 0;
    int completed = 0;

    while (completed < n) 
    {
        int highest_priority = INT_MAX;
        int index = -1;

        for (int i = 0; i < n; i++) 
        {
            if (at[i] <= current_time && pri[i] < highest_priority && rt[i] > 0)
            {
                highest_priority = pri[i];
                index = i;
            }
        }

        //If a process with the highest priority is found 
        if (index != -1) 
        {
            /*It decrements the remaining burst time of the currently executing 
            process as a unit of time has been allocated to it.*/
            rt[index]--;

            if (rt[index] == 0)
            {
                current_time++;
                ct[index] = current_time;
                tat[index] = ct[index] - at[index];
                wt[index] = tat[index] - bt[index];
                completed++;
            } 
            else 
            {
                /*Increment the current time to allocate one unit of time to the currently executing process.*/
                current_time++;
            }
        } 
        //If no process with a higher priority was found in the initial condition 
        else 
        {
            /*Increment the current time to move forward in time
             as there are no processes to execute at this moment.*/
            current_time++;
        }
    }
}

int main() 
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n];
    int bt[n]; 
    int pri[n]; // Priority
    int ct[n]; 
    int tat[n]; 
    int wt[n]; 

    for (int i = 0; i < n; i++) 
    {
        printf("Process P%d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority: ");
        scanf("%d", &pri[i]);
    }

    priority(n, at, bt, pri, ct, tat, wt);

    printf("Process\t\tPriority\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    float total_tat = 0;
    float total_wt = 0;

    for (int i = 0; i < n; i++) 
    {
        printf("P%d\t\t  %d\t\t  %d\t\t  %d\t\t  %d\t\t  %d\t\t  %d\n", i + 1, pri[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        total_tat += tat[i];
        total_wt += wt[i];
    }

    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);

    return 0;
}
