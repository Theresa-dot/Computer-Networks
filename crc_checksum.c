#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define N strlen(g)

char t[28], cs[28], g[] = "1101";
int a, e, c;

// Function to perform XOR operation
void xorFunction() {
    for (c = 1; c < N; c++)
        cs[c] = ((cs[c] == g[c]) ? '0' : '1');
}

// Function to calculate CRC (Cyclic Redundancy Check)
void crc() {
    for (e = 0; e < N; e++)
        cs[e] = t[e];
    do {
        if (cs[0] == '1')
            xorFunction();
        for (c = 0; c < N - 1; c++)
            cs[c] = cs[c + 1];
        cs[c] = t[e++];
    } while (e <= a + N - 1);
}

// Function to calculate the checksum
char* findChecksum(char* sentMessage, int k) {
    int i;
    int len = strlen(sentMessage);
    char* checksum = (char*)malloc(k + 1);
    for (i = 0; i < len; i += k) {
        char subMessage[k + 1];
        strncpy(subMessage, sentMessage + i, k);
        subMessage[k] = '\0';
        unsigned int sum = strtoul(subMessage, NULL, 2);
        sum = (sum + 1) % (1 << k);
        sprintf(checksum, "%s%0*u", checksum, k, sum);
    }
    return checksum;
}

// Function to check the receiver's checksum
char* checkReceiverChecksum(char* receivedMessage, int k, char* checksum) {
    int i;
    int len = strlen(receivedMessage);
    char* receiverSum = (char*)malloc(k + 1);
    for (i = 0; i < len; i += k) {
        char subMessage[k + 1];
        strncpy(subMessage, receivedMessage + i, k);
        subMessage[k] = '\0';
        unsigned int sum = strtoul(subMessage, NULL, 2);
        sum = (sum + strtoul(checksum, NULL, 2)) % (1 << k);
        sprintf(receiverSum, "%s%0*u", receiverSum, k, sum);
    }
    char* receiverChecksum = (char*)malloc(k + 1);
    for (i = 0; i < k; i++) {
        receiverChecksum[i] = (receiverSum[i] == '1') ? '0' : '1';
    }
    receiverChecksum[k] = '\0';
    return receiverChecksum;
}

// Function to perform the CRC calculation
void performCRC() {
    printf("Enter data: ");
    scanf("%s", t);
    printf("----------------------------------------\n");
    printf("Generating polynomial: %s\n", g);
    a = strlen(t);
    for (e = a; e < a + N - 1; e++)
        t[e] = '0';
    printf("----------------------------------------\n");
    crc();
    printf("CRC: %s\n", cs);
    for (e = a; e < a + N - 1; e++)
        t[e] = cs[e - a];
    printf("----------------------------------------\n");
    printf("Final data to be sent: %s\n", t);
    printf("----------------------------------------\n");
}

// Function to perform the checksum calculation
void performChecksum() {
    char sentMessage[100];
    int k;
    printf("Enter data: ");
    scanf("%s", sentMessage);
    printf("Enter the number of bits for checksum (k): ");
    scanf("%d", &k);
    printf("----------------------------------------\n");
    char* checksum = findChecksum(sentMessage, k);
    printf("Sender side checksum: %s\n", checksum);
    char receivedMessage[100];
    printf("Enter received data: ");
    scanf("%s", receivedMessage);
    char* receiverChecksum = checkReceiverChecksum(receivedMessage, k, checksum);
    printf("Receiver side checksum: %s\n", receiverChecksum);
    printf("----------------------------------------\n");
    char* finalSum = (char*)malloc(k + 1);
    int i;
    for (i = 0; i < k; i++) {
        finalSum[i] = ((checksum[i] - '0') + (receiverChecksum[i] - '0')) % 2 + '0';
    }
    finalSum[k] = '\0';
    if (atoi(finalSum) == 0) {
        printf("Receiver Checksum = 0.\n");
        printf("Data Accepted\n");
    }
    else {
        printf("Receiver Checksum != 0.\n");
        printf("Error\n");
    }
    printf("----------------------------------------\n");
    free(checksum);
    free(receiverChecksum);
    free(finalSum);
}

int main() {
    int choice;
    while (1) {
        printf("Menu:\n");
        printf("1. Calculate CRC\n");
        printf("2. Calculate Checksum\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
        case 1:
            performCRC();
            break;

        case 2:
            performChecksum();
            break;

        case 3:
            exit(0);

        default:
            printf("Invalid choice! Please try again.\n\n");
            break;
        }
    }
    return 0;
}
