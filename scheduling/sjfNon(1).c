#include <stdio.h>

int main()
{
    int total_BT = 0, smallest, n;
    int tat = 0;
    int wt = 0;
    printf("enter the no of processes : ");
    scanf("%d", &n);
    int burst_time[n + 1], at[n];
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter arrival time for process P%d : ", i);
        scanf("%d", &at[i]);
        printf("Enter burst time for process P%d : ", i);
        scanf("%d", &burst_time[i]);
        total_BT += burst_time[i];
    }
    printf("\nProcess  \tTAT\t\tWT\n");
    burst_time[n] = 9999;
    for (int time = 0; time < total_BT;)
    {
        smallest = n;
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && burst_time[i] > 0 && burst_time[i] < burst_time[smallest])
                smallest = i;
        }

        printf("P%d\t|\t%d\t|\t%d\n", smallest, time + burst_time[smallest] - at[smallest], time - at[smallest]);

        tat += time + burst_time[smallest] - at[smallest];
        wt += time - at[smallest];
        time += burst_time[smallest];
        burst_time[smallest] = 0;
    }

    printf("\n\nAverage waiting time = %.2f", wt * 1.0 / n);
    printf("\nAverage turnaround time = %.2f", tat * 1.0 / n);
    return 0;
}
