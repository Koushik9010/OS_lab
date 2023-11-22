#include <stdio.h>
#include <stdbool.h>

#define max_process 10
#define max_resource 10
int i, n;

void safetyalgorithm(int process, int available[max_resource], int max[max_process][max_resource], int allocation[max_process][max_resource])
{
    // Array to keep track of the remaining resources
    int work[max_resource];
    // Array to track whether a process has finished or not
    bool finish[max_process] = {false};
    // Array to store the safe sequence of processes
    int safe_sequence[max_process];
    // Counter for the number of processes in the safe sequence
    int safe_count = 0;

    // Initializing the work array with the available resources
    for (i = 0; i < n; i++)
    {
        work[i] = available[i];
    }

    // Loop until all processes are included in the safe sequence
    while (safe_count < process)
    {
        // Flag to check if a process is found in the current iteration
        bool found = false;

        // Iterate through each process
        for (i = 0; i < process; i++)
        {
            // Check if the process is not finished
            if (!finish[i])
            {
                // Flag to check if resources can be allocated to the process
                bool canAllocate = true;

                // Iterate through each resource type
                for (int j = 0; j < n; j++)
                {
                    // Check if the remaining resources are sufficient for the process
                    if (max[i][j] - allocation[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                /*If resources can be allocated, update the work array, 
                mark the process as finished, and add it to the safe sequence*/
                if (canAllocate)
                {
                    for (int j = 0; j < n; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    finish[i] = true;
                    safe_sequence[safe_count++] = i;
                    found = true;
                }
            }
        }

        // If no process is found in the current iteration, the system is not in a safe state
        if (!found)
        {
            printf("\nSystem is not in a safe state.\n");
            return;
        }
    }

    // If the loop completes, the system is in a safe state. Print the safe sequence.
    printf("\nSystem is in a safe state. Safe sequence: ");
    for (i = 0; i < process - 1; i++)
    {
        printf("P%d -> ", safe_sequence[i]);
    }
    printf("P%d\n", safe_sequence[process - 1]);
}

int main()
{
    int process;
    printf("Enter the number of processes: ");
    scanf("%d", &process);

    printf("Enter the number of resources: ");
    scanf("%d", &n);

    int max[max_process][max_resource];
    int allocation[max_process][max_resource];
    int available[max_resource];

    // Input the available resources
    printf("Enter the resources: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &available[i]);
    }

    // Input the need and allocation for each process
    printf("\nEnter the need and allocation for each process:\n");
    for (i = 0; i < process; i++)
    {
        printf("Process P%d:\n", i);
        printf("Need: ");
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &max[i][j]);
        }
        printf("Allocation: ");
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Call the safety algorithm function
    safetyalgorithm(process, available, max, allocation);

    return 0;
}
