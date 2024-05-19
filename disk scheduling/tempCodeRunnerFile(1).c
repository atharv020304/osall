// may be correct or not
#include <stdio.h>
#include <stdlib.h>

void sort(int n, int *arr)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void scan(int n, int headPosition, int direction, int requests[])
{
    float tso = 0;
    int ans[n], index = 0, done = 0;
    int startIndex = -1;
    sort(n, requests);
    if (direction == 1)
    {
        for (int i = 0; i < n; i++)
        {
            if (requests[i] >= headPosition)
            {
                if (startIndex == -1)
                {
                    startIndex = i;
                }
                ans[index] = requests[i];
                index++;
            }
        }
        for (int i = startIndex - 1; i >= 0; i--)
        {
            ans[index] = requests[i];
            index++;
        }
    }
    else if (direction == 2)
    {
        for (int i = 0; i < n; i++)
        {
            if (requests[i] >= headPosition)
            {
                if (startIndex == -1)
                {
                    startIndex = i;
                }
            }
        }

        for (int i = startIndex - 1; i >= 0; i--)
        {
            ans[index] = requests[i];
            index++;
        }

        for (int i = startIndex; i < n; i++)
        {
            ans[index] = requests[i];
            index++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        tso = tso + abs(headPosition - ans[i]);
        headPosition = ans[i];
        done++;

        if (done == n)
        {
            printf("%d\n", ans[i]);
        }
        else
        {
            printf("%d -> ", ans[i]);
        }
    }
    printf("\nTotal Seek operations : %.2f\n", tso);
    printf("Average Seek Length : %.2f\n", tso / n);
}

void main()
{
    int n, headPosition, direction;
    printf("Enter number of requests : ");
    scanf("%d", &n);
    printf("Enter head position : ");
    scanf("%d", &headPosition);
    printf("Direction : (1 - large value or 2 - small value) : ");
    scanf("%d", &direction);
    int requests[n];
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter request : ");
        scanf("%d", &requests[i]);
    }
    scan(n, headPosition, direction, requests);
}