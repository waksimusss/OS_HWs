#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

pid_t receiver_pid;
int bit_to_send;
int ack_received = 0;

void send_bit(int bit) {
    if (bit == 0) {
        kill(receiver_pid, SIGUSR1);
    }
    else if (bit == 1) {
        kill(receiver_pid, SIGUSR2);
    }
}

void sigusr1_handler(int signum) {
    ack_received = 1;
}

void send_number(int number) {
    int i;
    for (i = 0; i < 32; ++i) {
        bit_to_send = (number >> i) & 1;
        ack_received = 0;
        send_bit(bit_to_send);
        while (!ack_received) {
            usleep(1000); // wait until acknowledgment is received
        }
    }
    // Signal end of transmission
    kill(receiver_pid, SIGINT);
}

int main() {
    printf("Transmitter PID: %d\n", getpid());
    printf("Enter receiver PID: ");
    scanf("%d", &receiver_pid);
    printf("Enter a decimal number: ");
    int number;
    scanf("%d", &number);
    signal(SIGUSR1, sigusr1_handler);
    send_number(number);
    return 0;
}
