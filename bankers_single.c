#include <stdio.h>
#include <stdbool.h>

#define max_process 10
#define max_resource 10
int i, n;

void safetyalgorithm(int process, int available, int max[max_process], int allocation[max_process])
{
    int work = available;
    bool finish[max_process] = {false};
    int safe_sequence[max_process];
    int safe_count = 0;

    while (safe_count < process)
    //all processes are included in the safe sequence
    {
        bool found = false;

        // Iterate through each process to find one that can be completed
        for (i = 0; i < process; i++)
        {
            // Check if the process is not finished and its maximum need is less than or equal to the available resources
            if (!finish[i] && max[i] <= work)
            //!finish[i]->Checks if the process i is not finished
            {
                // Allocate resources to the process
                work += allocation[i];
                // Mark the process as finished
                finish[i] = true;//The process is finished
                // Add the process to the safe sequence
                safe_sequence[safe_count++] = i;
                found = true;
                //a process has been found in the current iteration.
            }
        }
        // If no process is found in a complete iteration, the system is not in a safe state
        if (!found)
        {
            printf("System is not in safe state.\n");
            return;
        }
    }

    // If the loop completes, the system is in a safe state
    printf("System is in safe state. Safe sequence: ");
    for (i = 0; i < process - 1; i++)
    {
        printf("P%d -> ", safe_sequence[i]);
    }
    printf("P%d\n", safe_sequence[process - 1]);
}

int main()
{
    int process, available;
    printf("Enter the number of processes: ");
    scanf("%d", &process);

    printf("Enter the number of available resources: ");
    scanf("%d", &available);

    int max[max_process];
    int allocation[max_process];

    printf("Enter the need and allocation for each process:\n");
    for (i = 0; i < process; i++)
    {
        printf("Process P%d: \n", i);
        printf("Need: ");
        scanf("%d", &max[i]);
        printf("Allocation: ");
        scanf("%d", &allocation[i]);
    }

    safetyalgorithm(process, available, max, allocation);

    return 0;
}
