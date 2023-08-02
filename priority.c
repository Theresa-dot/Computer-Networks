#define MAX 100

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <String.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int main()
{
    int n, burst[MAX], priority[MAX], index[MAX];
    printf("Enter total number of processes : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter burst Time and priority for the process %d : ", i + 1);
        scanf("%d %d", &burst[i], &priority[i]);
        index[i] = i + 1;
    }
    for (int i = 0; i < n; i++)
    {
        int a = priority[i], m = i;
        for (int j = i; j < n; j++)
        {
            if (priority[j] < a)
            {
                a = priority[j];
                m = j;
            }
        }
        swap(&priority[i], &priority[m]);
        swap(&burst[i], &burst[m]);
        swap(&index[i], &index[m]);
    }

    int t = 0;

    printf("Order of Execution of processes\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d is executed from %d to %d\n", index[i], t, t + burst[i]);
        t += burst[i];
    }
    printf("\n");
    printf("Process Id     Burst Time   Wait Time    TurnAround Time\n");
    int wait_time = 0;
    for (int i = 0; i < n; i++)
    {
        printf("Process %d          %d          %d          \t%d\n", index[i], burst[i], wait_time, wait_time + burst[i]);
        wait_time += burst[i];
    }
    return 0;
}
