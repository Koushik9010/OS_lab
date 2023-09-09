#include<stdio.h>

void fcfs(int process[], int at[], int bt[], int ct[], int tat[], int wt[], int n)
{
    int current_time  = 0;
    float total_tat = 0;
    float total_wt = 0;

    printf("Process\t\tArrival_time\t\tBurst_time\t\tCompletion_time\t\tTurn_around_time\t\tWaiting_time\n");
    for(int i = 0; i < n; i++)
    {
        //waiting for the process to arrive if needed
        if(current_time < at[i])
        {
            current_time = at[i];
        }

        //update ct
        ct[i] = current_time + bt[i];

        //update tat and wt
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_tat += tat[i];
        total_wt += wt[i];

        //print the processes
        printf("%2d\t\t%7d\t%19d\t%22d\t%25d\t%15d\n", process[i], bt[i], at[i], ct[i], tat[i], wt[i]);

        //update current time
        current_time = ct[i];
    }

    //avg tat & wt
    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;

    printf("\nAverage turn arround time: %.2f", avg_tat);
    printf("\nAverage waiting time: %.2f", avg_wt);
}

int main()
{
    int n, i, j;
    printf("Enter the number of process: ");
    scanf("%d", &n);

    int process[n];
    int at[n];
    int bt[n];
    int ct[n];
    int tat[n];
    int  wt[n];

    printf("Enter the arival time and  burst time for each process: ");
    for(i = 0; i < n; i++)
    {
        process[i] = i + 1;
        printf("\nProcess p%d: \n", i + 1);
        printf("Enter the arrival time: ");
        scanf("%d", &at[i]);
        printf("Enter the burst time: ");
        scanf("%d", &bt[i]);
    }

    //sorting the processes by arrival time
    for(i = 0; i < n ; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(at[i] > at[j])
            {
                //swaping process to sync with ct
                int temp = process[i];
                process[i] = process[j];
                process[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
            }
        }
    }

    fcfs(process, at, bt, ct, tat, wt, n);

    return 0;
}