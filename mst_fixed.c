#include <stdio.h>

// Global variables
int i, total_memory, total_process, block_size, total_used_memory = 0, total_wastage = 0;

// Function to calculate the block size for each process
int calculateBlock(int total_memory, int total_process) {
  return total_memory / total_process;
}

// Function to allocate memory for each process
void allocateMemory() {
  int original_block_size = block_size; // Store the original block size

  int memory;

  // Loop through each process
  for (i = 0; i < total_process; i++) {
    block_size = original_block_size; // Reset block_size to its original value

    printf("Enter the required memory size for process P%d: ", i);
    scanf("%d", &memory);

    // Check if there's enough memory for the current process
    if (memory <= block_size) {
      block_size -= memory; // Update the remaining block size after allocation
      total_used_memory += memory; // Update the total used memory
    } else {
      printf("Not enough memory for process P%d. Try again.\n", i);
      i--; // Decrement i to repeat the current process
    }

    // Print the current block size after allocation for each process
    printf("Current block size after allocating memory for process P%d: %d\n", i, block_size);
  }
}

// Main function
int main() {
  // Input: total memory size
  printf("Enter the total memory size: ");
  scanf("%d", &total_memory);

  // Input: total number of processes
  printf("Enter the total number of processes: ");
  scanf("%d", &total_process);

  // Calculate the block size
  block_size = calculateBlock(total_memory, total_process);

  // Allocate memory for each process
  allocateMemory();

  // Calculate total wastage
  total_wastage = total_memory - total_used_memory;

  // Print results
  printf("Memory allocation successful.\n");
  printf("Total memory used: %d\n", total_used_memory);
  printf("Total wastage: %d\n", total_wastage);

  return 0;
}
