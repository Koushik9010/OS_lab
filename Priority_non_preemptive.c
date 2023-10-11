#include <stdio.h>
#include <limits.h>

void priority(int n, int at[], int bt[], int pri[], int ct[], int tat[], int wt[])
{
    int rt[n];
    for (int i = 0; i < n; i++)
    {
        rt[i] = bt[i];
    }

    int current_time = 0;
    int completed = 0;//count the number of completed processes

    while (completed < n)
    {
        int highest_priority = INT_MAX;
        int index = -1;

        for (int i = 0; i < n; i++)
        {
            //the process with the lowest priority value as having the highest priority//
            if (at[i] <= current_time && pri[i] < highest_priority && rt[i] > 0)
            /*checks the process with the highest priority that has already arrived,
            has remaining burst time, and has a higher priority*/
            {
                highest_priority = pri[i];
                index = i;
            }
        }
        //If a process with the highest priority is found 
        if (index != -1)
        {
            current_time += bt[index];
            ct[index] = current_time;
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];
            rt[index] = 0;
            completed++;
        }
        else //If no process with a higher priority is found
        {
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
    int pri[n]; //priority
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

//if (at[i] <= current_time && pri[i] > highest_priority && rt[i] > 0)
//high value low priority
