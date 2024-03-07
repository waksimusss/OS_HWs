#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int received_number = 0;
int bit_position = 0;

void receive_bit(int signum) {
    if (signum == SIGUSR1) {
        received_number |= (0 << bit_position);
    }
    else if (signum == SIGUSR2) {
        received_number |= (1 << bit_position);
    }
    ++bit_position;
    // Send acknowledgment
    kill(getppid(), SIGUSR1);
}

void print_received_number(int signum) {
    printf("Received number: %d\n", received_number);
    exit(0);
}

int main() {
    printf("Receiver PID: %d\n", getpid());
    signal(SIGUSR1, SIG_IGN); // Ignore SIGUSR1 to prevent termination
    signal(SIGUSR2, receive_bit);
    signal(SIGINT, print_received_number); // End of transmission signal
    printf("Waiting for data...\n");
    while (1) {
        pause(); // Wait for signals
    }
    return 0;
}
