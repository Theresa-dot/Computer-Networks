#include <stdio.h>
#include <stdbool.h>

// Function to simulate sending a packet
void sendPacket(int packet) {
    printf("Sending packet %d\n", packet);
}

bool receiveAck(int packet) {
    if (packet == 2 || packet == 5) {
        return false;  
    }
    return true;
}

int main() {
    int totalPackets = 10;
    int windowSize;

    printf("Enter the window size: ");
    scanf("%d", &windowSize);

    int base = 0;
    int nextSeqNum = 0;

    while (base < totalPackets) {
        if (base == totalPackets) {
            printf("All packets sent and acknowledged!\n");
            break;
        }
        if (nextSeqNum < totalPackets && nextSeqNum < base + windowSize) {
            int i;
            for (i = nextSeqNum; i < base + windowSize && i < totalPackets; i++) {
                sendPacket(i);
            }
            printf("Waiting for acknowledgements...\n");
            for (i = nextSeqNum; i < base + windowSize && i < totalPackets; i++) {
                printf("Waiting for acknowledgement of packet %d...\n", i);
                if (receiveAck(i)) {
                    printf("Packet %d acknowledged!\n", i);
                    nextSeqNum++;
                } else {
                    printf("Packet %d lost, retransmitting...\n", i);
                }
            }
        }

        if (nextSeqNum >= base + windowSize) {
            printf("Waiting for acknowledgements...\n");
            int i;
            for (i = base; i < base + windowSize && i < totalPackets; i++) {
                if (receiveAck(i)) {
                    printf("Packet %d acknowledged!\n", i);
                    base++;
                } else {
                    printf("Acknowledgement for packet %d lost, retransmitting...\n", i);
                }
            }
        }
    }

    return 0;
}
