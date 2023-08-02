#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char ip_address[16]; // Assuming IPv4 address (XXX.XXX.XXX.XXX)
    printf("Enter an IP address (e.g., 192.168.0.1): ");
    scanf("%15s", ip_address);
    int flag=0;

    // Splitting the IP address into octets
    char *octet_str;
    int octets[4];
    int i = 0;
    octet_str = strtok(ip_address, ".");
    while (octet_str != NULL && i < 4) {
        octets[i] = atoi(octet_str);
        if(octets[i]>255) {
            printf("Invalid"); //octets must lie in range 0-255 to be a valid ip address
            flag=1;
        }
        octet_str = strtok(NULL, ".");
    }

    //to find class of networks from the first
    if (flag == 0) {
        if (octets[0] >= 0 && octets[0] <= 127) {
            printf("Class A network");
        } else if (octets[0] >= 128 && octets[0] <= 191) {
            printf("Class B network");
        } else if (octets[0] >= 192 && octets[0] <= 223) {
            printf("Class C network");
        } else if (octets[0] >= 224 && octets[0] <= 239) {
            printf("Class D network");
        } else if (octets[0] >= 240 && octets[0] <= 255) {
            printf("Class E network");
        }
    }

    return 0;
}
