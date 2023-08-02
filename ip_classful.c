#include <stdio.h>
#include <stdint.h>
int a,b,c,d;


void calculate_network_details(uint32_t ip_address, int prefix_length) {
    
    uint32_t subnet_mask = (0xFFFFFFFF << (32 - prefix_length)) & 0xFFFFFFFF;

    
    uint32_t network_address = ip_address & subnet_mask;

    
    int num_hosts = (1 << (32 - prefix_length)) ;

    
    uint32_t starting_ip = network_address;
    
    uint32_t ending_ip = network_address + num_hosts-1;

    
    uint32_t limited_broadcast = 0xFFFFFFFF;

    
    uint32_t directed_broadcast = network_address | ~subnet_mask;

    
    printf("Reserved bits for Network: %d\n", prefix_length);
    printf("Reserved bits for Host: %d\n", 32 - prefix_length);
    printf("Total number of hosts in that network: %d\n", num_hosts);
    printf("Starting IP: %d.%d.%d.%d\n", (starting_ip >> 24) & 0xFF, (starting_ip >> 16) & 0xFF, (starting_ip >> 8) & 0xFF, starting_ip & 0xFF);
    printf("Ending IP: %d.%d.%d.%d\n", (ending_ip >> 24) & 0xFF, (ending_ip >> 16) & 0xFF, (ending_ip >> 8) & 0xFF, ending_ip & 0xFF);
    printf("Lmited braodcast address: 255.255.255.255\n");
    printf("Directed broadcast address: %d.%d.%d.%d\n", (directed_broadcast >> 24) & 0xFF, (directed_broadcast >> 16) & 0xFF, (directed_broadcast >> 8) & 0xFF, directed_broadcast & 0xFF);
}

int main() {
    
    char ip_str[16];
    int prefix_length;

    
    fgets(ip_str, sizeof(ip_str), stdin);
    sscanf(ip_str, "%d.%d.%d.%d/%d", &a, &b, &c, &d, &prefix_length);

    
    uint32_t ip_address = (a << 24) | (b << 16) | (c << 8) | d;

   
    calculate_network_details(ip_address, prefix_length);

    return 0;
}