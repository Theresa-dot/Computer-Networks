#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int WINDOW_SIZE;

typedef struct {
    int sequence_number;
    char data;
} Packet;

void send(Packet packet) {
    printf("Sending packet with sequence number: %d\n", packet.sequence_number);
    // Send packet to receiver
}

void receive_acknowledgment(int* window_start, int* window_end) {
    // Simulating the acknowledgment reception
    int received_ack[WINDOW_SIZE];
    int i;
    for (i = *window_start; i < *window_end; i++) {
        received_ack[i - *window_start] = i;
        printf("Received acknowledgment for packet with sequence number: %d\n", i);
    }
    
    *window_start += i - *window_start;
    *window_end += i - *window_start;
}

void sender(int buffer_length, char* buffer) {
    int window_start = 0;
    int window_end = 0;

    srand(time(NULL)); // Initialize random number generator
    
    while (window_end < buffer_length) {
        while (window_end < window_start + WINDOW_SIZE && window_end < buffer_length) {
            Packet packet;
            packet.sequence_number = window_end;
            packet.data = buffer[window_end];
            send(packet);
            window_end++;
        }
        
        // Simulate missing packets randomly
        if (rand() % 3 == 0) {
            int num_missing = rand() % 3 + 1; // Number of missing packets (1-3)
            int i;
            for (i = 0; i < num_missing; i++) {
                int missing_seq = rand() % WINDOW_SIZE + window_start;
                printf("Simulating missing packet with sequence number: %d\n", missing_seq);
            }
        }
        
        // Wait for acknowledgment
        receive_acknowledgment(&window_start, &window_end);
    }
}

int main() {
    char buffer[] = "Hello, world!"; // Example data buffer
    int buffer_length = sizeof(buffer) - 1; // Length of the buffer
    printf("Enter window size: ");
    scanf("%d",&WINDOW_SIZE);
    
    sender(buffer_length, buffer);
    
    return 0;
}