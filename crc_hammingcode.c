#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>


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

int isValidInput(const char *input)
{
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] != '0' && input[i] != '1')
        {
            return 0;
        }
    }
    return 1;
}

void performCRC() {
    printf("Enter data: ");
    scanf("%s", t);
    if(isValidInput(t)==0){
        printf("Invalid\n");
        return;
    } 
    printf("Enter divisor: ");
    scanf("%s", g);
    if(isValidInput(g)==0){
        printf("Invalid\n");
        return;
    } 
    printf("----------------------------------------\n");
    a = strlen(t);
    for (e = a; e < a + strlen(g) - 1; e++)
        t[e] = '0';
    printf("----------------------------------------\n");
    crc();
    printf("Sender Side\n");
    printf("CRC: %s\n", cs);
    for (e = a; e < a + strlen(g) - 1; e++)
        t[e] = cs[e - a];
    printf("Final data to be sent: %s\n", t);
    printf("----------------------------------------\n");
    printf("Receiver Side\n");
    printf("Enter received data: ");
    scanf("%s", t);
    if(isValidInput(t)==0) {
        printf("Invalid\n");
        return;
    } 
    for(int i=0;i<strlen(t);i++){
        if(t[i]!='0' && t[i]!='1') {
            printf("Not valid\n");
            return;
        }
    }
    crc();
    printf("CRC: %s\n", cs);
    for(e=0;(e<strlen(g)-1) && (cs[e]!='1');e++);
    if(e<strlen(g)-1)
        printf("\nError detected\n\n");
    else
        printf("\nNo error detected\n\n");
    printf("\n----------------------------------------\n");
}

int calculateRedundancyBits(int m)
{
    int r = 0;
    while (pow(2, r) < (m + r + 1))
        r++;
    return r;
}

void calculateParityBits(int *data, int m, int r)
{
    int i, j, k, sum = 0;

    printf("Redundancy bits (position):\n");
    for (i = 0; i < r; i++)
    {
        k = pow(2, i) - 1;
        for (j = k; j < m;)
        {
            for (int l = 0; l <= k; l++)
            {
                sum += data[j];
                j++;
                if (j >= m)
                    break;
            }

            if (j >= m)
                break;

            for (int l = 0; l <= k; l++)
            {
                j++;
                if (j >= m)
                    break;
            }

            if (j >= m)
                break;
        }
        data[k] = sum % 2;
        sum = 0;
        printf("%d (%d)\n", data[k], k + 1);
    }
}

void receiveData(int *receivedData, int m, int n)
{
    printf("Enter the received data: ");
    char input[m+1];
    scanf("%s", input);
    if(isValidInput(input)==0){
        printf("Invalid\n");
        return;
    } 

    for (int i = 0; i < m; i++)
    {
        receivedData[i] = input[m - i - 1] - '0';
    }
}

void calculateSyndrome(int *receivedData, int m, int n)
{
    int i, j, k, sum = 0, errorPos = 0;
    int r = n - 1;
    int *syndrome = (int *)malloc(sizeof(int) * n);

    printf("Syndrome bits (position):\n");
    for (k = 0; k < n; k++)
    {
        j = pow(2, k) - 1;
        for (i = j; i < m;)
        {
            for (int l = 0; l <= j; l++)
            {
                sum += receivedData[i];
                i++;
                if (i >= m)
                    break;
            }

            if (i >= m)
                break;

            for (int l = 0; l <= j; l++)
            {
                i++;
                if (i >= m)
                    break;
            }

            if (i >= m)
                break;
        }
        syndrome[r] = sum % 2;
        sum = 0;
        printf("%d (%d)\n", syndrome[r], j + 1);
        r--;
    }

    for (int m = 0; m < n; m++)
    {
        errorPos += syndrome[n - m - 1] * pow(2, m);
    }

    if (errorPos != 0)
    {
        printf("Error position: %d\n", errorPos);
        receivedData[errorPos - 1] ^= 1;
        printf("Corrected data: ");
        for (int i = m - 1; i >= 0; i--)
        {
            printf("%d", receivedData[i]);
        }
        printf("\n");
    }
    else printf("No error detected\n");
    
}

void performHammingCode(){
    int maxp = 6;
    int temp[70], temp2[70];
    int a[50];
    int t, i, j, k, nd, n, nh;
    
    printf("Enter Data String: ");
    char input[50];
    scanf("%s", input);
    if(isValidInput(input)==0) {
        printf("Invalid\n");
        return;
    } 
    
    nd=strlen(input);

    for (i = nd - 1; i >= 0; i--)
    {
        a[i] = input[nd - i - 1] - '0';
    }
    printf("-----------------------------------\n");

    for (i = 0, j = 0; i < nd; i++)
    {
        for (k = 0; k < maxp; k++)
        {
            t = pow(2, k) - 1;
            if (j == t)
            {
                temp[j] = 0;
                j++;
            }
        }
        temp[j] = a[i];
        j++;
    }

    printf("Length of Data String (m): %d bits\n", nd);
    nh = j;
    printf("Length of Hamming code (n): %d bits\n", nh);
    n = nh - nd;
    printf("Number of Parity Bits (r): %d \n", n);

    calculateParityBits(temp, nh, n);

    printf("\nHamming code: Sender side:   ");
    for (i = nh - 1; i >= 0; i--)
    {
        printf("%d", temp[i]);
    }
    printf("\n");

    printf("Hamming code: Receiver side\n");
    receiveData(temp2, nh, nd);

    calculateSyndrome(temp2, nh, n);

    printf("-----------------------------------\n");
}

int main() {
    int choice;
    while (1) {
        printf("Menu:\n");
        printf("1. CRC method\n");
        printf("2. Hamming Code Method\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
        case 1:
            performCRC();
            break;

        case 2:
            performHammingCode();
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
