#include<stdio.h>
#include<string.h>
#include<stdlib.h>


char t[28], cs[28],g[28];
int a, e, c;

// Function to perform XOR operation
void xorFunction() {
    for (c = 1; c < strlen(g); c++)
        cs[c] = ((cs[c] == g[c]) ? '0' : '1');
}

// Function to calculate CRC (Cyclic Redundancy Check)
void crc() {
    for (e = 0; e < strlen(g); e++)
        cs[e] = t[e];
    do {
        if (cs[0] == '1')
            xorFunction();
        for (c = 0; c < strlen(g) - 1; c++)
            cs[c] = cs[c + 1];
        cs[c] = t[e++];
    } while (e <= a + strlen(g) - 1);
}

void performCRC() {
    printf("Enter data: ");
    scanf("%s", t);
    printf("----------------------------------------\n");
    printf("Enter divisor: ");
    scanf("%s", g);
    for(int i=0;i<strlen(t);i++){
        if(t[i]!='0' || t[i]!='1') {
            printf("Not valid\n");
            return;
        }
    }
    for(int i=0;i<strlen(g);i++){
        if(g[i]!='0' || g[i]!='1') {
            printf("Not valid\n");
            return;
        }
    }
    a = strlen(t);
    for (e = a; e < a + strlen(g) - 1; e++)
        t[e] = '0';
    printf("----------------------------------------\n");
    crc();
    printf("Sender Side\n");
    printf("CRC: %s\n", cs);
    for (e = a; e < a + strlen(g) - 1; e++)
        t[e] = cs[e - a];
    printf("----------------------------------------\n");
    printf("Final data to be sent: %s\n", t);
    printf("----------------------------------------\n");
}

int main() {
    int choice;
    while (1) {
        printf("Menu:\n");
        printf("1. CRC method\n");
        printf("2. Checksum Method\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
        case 1:
            performCRC();
            break;

        case 2:
            //performChecksum();
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