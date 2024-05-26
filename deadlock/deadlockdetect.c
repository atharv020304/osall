#include <stdio.h>

int main()
{
    int m = 3, n = 5;

    int work[3], finish[5];

    int allocation[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 3}, {2, 1, 1}, {0, 0, 2}};

    int req[5][3] = {{0, 0, 0}, {2, 0, 2}, {0, 0, 0}, {1, 0, 0}, {0, 0, 2}};

    int avail[3] = {0, 0, 0};

    for (int i = 0; i < m; i++)
    {

        work[i] = avail[i];
        
    }

    for (int i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int flag = 1;
            for (int k = 0; k < m; k++)
            {
                if (req[j][k] > work[k])
                {
                    flag = 0;
                    break;
                }
            }

            if (finish[j] == 0 && flag == 1)
            {
                for (int k = 0; k < m; k++)
                {
                    work[k] += allocation[j][k];
                }
                finish[j] = 1;
                break;
            }
        }
    }

    int flag1 = 1;
    for (int i = 0; i < n; i++)
    {
        if (finish[i] == 0)
        {
            printf("Deadlock is present in P%d\n", i);
            flag1 = 0;
        }
    }

    if (flag1 == 1)
    {
        printf("no deadlockis present ");
    }

    return 0;
}
