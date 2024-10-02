#ifndef COUNTER_H
#define COUNTER_H
/**
 * @brief Handles the SIGUSR1 signal
 *
 * Resets the counter to 0
 *
 * @param sig The signal number
 */
void handle_sigusr1(int sig);
/**
 * @brief Handles the SIGUSR2 signal
 *
 * Changes the counting direction
 *
 * @param sig The signal number
 */
void handle_sigusr2(int sig);
/**
 * @brief Starts the infinite counting process
 *
 * Sets up the signal handlers and enters the loop
 */
void start_counting();

#endif  // COUNTER_H