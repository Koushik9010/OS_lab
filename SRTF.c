#include<stdio.h>
#include<limits.h>

struct process
{
    int id;
    int at;
    int bt;
    int tat;
    int ct;
    int wt;
    int rt; //remaining time
};

void srtf(int n)
{
    int i;
    struct process p[n];
    int current_time = 0;
    int completed = 0;

    for(i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        printf("\nEnter the arrival time for p%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("\nEnter the burst time for process p%d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
    }
    printf("p\tAT\tBT\tCT\tTAT\tWT\n");
    for(current_time = 0; completed < n; current_time++)
    //The loop iterates until all processes have completed. 
    //At each iteration, the loop finds the process with the shortest remaining time.
    {
        int min_rt = INT_MAX;
        int min_rt_index = -1;

        for(i = 0; i < n; i++)
        {
            if(p[i].at <= current_time && p[i].rt < min_rt && p[i].rt > 0)
            /*This line checks if a process i has arrived, has a shorter remaining time 
            than the current shortest, and still has work to do. 
            If all conditions are met, it selects process 
            i as the next candidate for execution.*/
            {
                min_rt = p[i].rt;
                min_rt_index = i;
            }
        }
        if(min_rt_index != -1)
        {
            //Decrement the remaining time of the selected process.
            p[min_rt_index].rt--;

            //Check if the remaining time of the selected process has become zero.
            if(p[min_rt_index].rt == 0)
            {
                completed++;
                p[min_rt_index].ct = current_time + 1;
                p[min_rt_index].tat = p[min_rt_index].ct - p[min_rt_index].at;
                p[min_rt_index].wt = p[min_rt_index].tat - p[min_rt_index].bt;
            }
        }
    }
    float total_tat = 0;
    float total_wt = 0;

    for(i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, 
        p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;
    printf("\nAverage TAT: %.2f", avg_tat);
    printf("\nAverage WT: %.2f\n", avg_wt);
}

int main()
{
    int n;
    printf("\nEnter the number of process: ");
    scanf("%d", &n);

    srtf(n);

    return 0;
}
