#include "counter.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counter = 0;
int increment = 1;
/**
 * @brief Handles the SIGUSR1 signal.
 * @param sig The signal number (unused).
 */
void handle_sigusr1(int sig) {
  counter = 0;  // Reset the counter
  printf("Counter reset to 0.\n");
}
/**
 * @brief Handles the SIGUSR2 signal.
 *
 * Changes the direction of the counting by inverting the increment value
 */
void handle_sigusr2(int sig) {
  increment = -increment;  // Change counting direction
  printf("Counter direction changed.\n");
}
/**
 * @brief Starts the infinite counting process.
 *
 * Sets signals for SIGUSR1 and SIGUSR2. Enters the infinite loop
 * that increments or decrements the counter based on direction
 * and prints the current count every second
 */
void start_counting() {
  // Sets up signal handlers
  signal(SIGUSR1, handle_sigusr1);
  signal(SIGUSR2, handle_sigusr2);

  // Infinite counting loop
  while (1) {
    printf("I'm counting, and my count is %d\n", counter);
    counter += increment;
    sleep(1);
  }
}
