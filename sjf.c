#define MAX 1000

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void swap(int *a,int *b ){
    int temp = *a;
    *a = *b;
    *b =temp;
}
int main()
{
    int n, position,burst_t[MAX], p[MAX], waiting_t[MAX], turn_around_t[MAX];
    printf("Enter total number of processes : ");
    scanf("%d", &n);
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter Burst Time for process %d: ", i + 1);
        scanf("%d", &burst_t[i]);
    }

    for (int i = 0; i < n; i++)
    {
        position = i;
        for (int j = i + 1; j < n; j++)
        {
            if (burst_t[j] < burst_t[position])
                position = j;
        }
        swap(&burst_t[i],&burst_t[position]);
        swap(&p[i],&p[position]);
    }

    waiting_t[0] = 0;

    int total_wait_time = 0 ;
    for (int i = 1; i < n; i++)
    {
        waiting_t[i] = 0;
        for (int j = 0; j < i; j++)
            waiting_t[i] += burst_t[j];

       total_wait_time += waiting_t[i];
    }

    float avg_waiting_t = total_wait_time / n;
    float total_turnaround_time = 0;

    printf("\nProcess\t\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for (int i = 0; i < n; i++)
    {
        turn_around_t[i] = burst_t[i] + waiting_t[i];
        total_turnaround_time += turn_around_t[i];
        printf("\nProcess %d\t\t  %d\t\t    %d\t\t\t%d", i+1, burst_t[i], turn_around_t[i],waiting_t[i]);
    }

    float avg_turnaround_t = total_turnaround_time / n;
    printf("\n\nAverage Waiting Time =%0.1f\n", avg_waiting_t);
    printf("Average Turnaround Time = %0.1f", avg_turnaround_t);
}
