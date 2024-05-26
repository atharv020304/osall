#include <stdio.h>

void main()
{
    int p;
    printf("Enter number of processes : ");
    scanf("%d", &p);
    int at[p], bt[p], temp[p], ft[p], tat[p], wt[p], visited[p], pp[p], small;
    int count = 0, curTime = 0, totalTime = 0;
    float t = 0, w = 0;
    for (int i = 0; i < p; i++)
    {
        printf("Enter AT of process %d : ", i);
        scanf("%d", &at[i]);
        printf("Enter BT of process %d : ", i);
        scanf("%d", &bt[i]);
        printf("Enter prioirty of process %d : ", i);
        scanf("%d", &pp[i]);
        printf("\n");
        totalTime += bt[i];
        temp[i] = bt[i];
        visited[i] = 0;
    }

    small = at[0];
    for (int i = 0; i < p; i++)
    {
        if (at[i] < small)
        {
            small = at[i];
        }
    }

    curTime = small;
    totalTime += small;

    while (curTime < totalTime)
    {
        for (int i = 0; i < p; i++)
        {
            if (visited[i] == 0 && at[i] <= curTime)
            {
                small = i;
                break;
            }
        }

        for (int i = 0; i < p; i++)
        {
            if (visited[i] == 0 && at[i] <= curTime && pp[i] < pp[small])
            {
                small = i;
            }
            else if (visited[i] == 0 && at[i] <= curTime && pp[i] == pp[small] && at[i] < at[small])
            {
                small = i;
            }
        }

        curTime++;
        bt[small]--;
        if (bt[small] == 0)
        {
            ft[small] = curTime;
            visited[small] = 1;
        }
    }

    printf("\nprocess\tAT\tBT\tFT\tTAT\tWT\n");
    for (int i = 0; i < p; i++)
    {
        tat[i] = ft[i] - at[i];
        wt[i] = tat[i] - temp[i];
        t += tat[i];
        w += wt[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, at[i], temp[i], ft[i], tat[i], wt[i]);
    }

    printf("\nAvg. TAT : %.2f", t / p);
    printf("\nAvg. WT : %.2f", w / p);
}