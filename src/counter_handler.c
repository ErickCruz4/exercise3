#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_COUNTERS 5

/**
 * @brief Prints the menu for counter_handler.
 *
 * Displays all options
 */
void print_menu() {
  printf("\nCounter Handler Menu:\n");
  printf("1. Stop a specific infinite-counter process\n");
  printf("2. Continue a specific infinite-counter process\n");
  printf(
      "3. Change the counting direction of a specific infinite-counter "
      "process\n");
  printf("4. Kill a specific infinite-counter process\n");
  printf("5. Exit the counter handler\n");
  printf("Select an option (1-5): ");
}

/**
 * @brief Sends a signal to a process.
 *
 * Sends the signal to the process with the given PID.
 */
void send_signal(int pid, int sig) {
  if (kill(pid, sig) == -1) {
    perror("Failed to send signal");
  } else {
    printf("Signal sent successfully.\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2 || argc > MAX_COUNTERS + 1) {
    fprintf(stderr, "Usage: %s <pid1> <pid2> ... <pidN> (up to %d PIDs)\n",
            argv[0], MAX_COUNTERS);
    exit(EXIT_FAILURE);
  }

  int pids[MAX_COUNTERS];
  int count = argc - 1;
  /**
   * @brief The main function for the counter_handler program.
   *
   * Convert PIDs from command line arguments to integers
   *
   * @param argc The number of command-line arguments.
   * @param argv The array of command-line arguments.
   * @return int Returns EXIT_SUCCESS upon successful execution.
   */
  for (int i = 0; i < count; i++) {
    pids[i] = atoi(argv[i + 1]);
    if (kill(pids[i], 0) == -1) {
      perror("Invalid PID or no permission to control the process");
      exit(EXIT_FAILURE);
    }
  }

  int choice, index;
  while (1) {
    print_menu();
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        printf("Enter the process number to stop (1-%d): ", count);
        scanf("%d", &index);
        if (index < 1 || index > count) {
          printf("Invalid process number.\n");
        } else {
          send_signal(pids[index - 1], SIGSTOP);
        }
        break;

      case 2:
        printf("Enter the process number to continue (1-%d): ", count);
        scanf("%d", &index);
        if (index < 1 || index > count) {
          printf("Invalid process number.\n");
        } else {
          send_signal(pids[index - 1], SIGCONT);
        }
        break;

      case 3:
        printf("Enter the process number to change counting direction (1-%d): ",
               count);
        scanf("%d", &index);
        if (index < 1 || index > count) {
          printf("Invalid process number.\n");
        } else {
          send_signal(pids[index - 1], SIGUSR2);
        }
        break;

      case 4:
        printf("Enter the process number to kill (1-%d): ", count);
        scanf("%d", &index);
        if (index < 1 || index > count) {
          printf("Invalid process number.\n");
        } else {
          send_signal(pids[index - 1], SIGKILL);
          // Remove the killed process from the list
          for (int i = index - 1; i < count - 1; i++) {
            pids[i] = pids[i + 1];
          }
          count--;
          if (count == 0) {
            printf("No infinite-counter processes are alive. Exiting.\n");
            exit(EXIT_SUCCESS);
          }
        }
        break;

      case 5:
        printf("Exiting counter handler.\n");
        exit(EXIT_SUCCESS);

      default:
        printf("Invalid option. Please select a number between 1 and 5.\n");
        break;
    }
  }

  return 0;
}
