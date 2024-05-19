// The basic idea is the tracks that are closer to the current disk head position
// should be serviced first in order to minimize the seek operations is basically known as Shortest Seek Time First (SSTF).
#include <stdio.h>
#include <stdlib.h>

void sstf(int n, int headPosition, int requests[])
{
    int visited[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    float tso = 0;
    int done = 0;
    for (int i = 0; i < n; i++)
    {
        int min = 99999;
        int index;
        for (int j = 0; j < n; j++)
        {
            if (visited[j] == 0)
            {
                if (abs(headPosition - requests[j]) < abs(headPosition - min))
                {
                    min = requests[j];
                    index = j;
                }
            }
        }
        tso += abs(headPosition - min);
        headPosition = min;
        done++;
        visited[index] = 1;
        if (done == n)
        {
            printf("%d\n", min);
        }
        else
        {
            printf("%d -> ", min);
        }
    }
    printf("\nTotal Seek operations : %.2f\n", tso);
    printf("Average Seek Length : %.2f\n", tso / n);
}

void main()
{
    int n, headPosition;
    printf("Enter number of requests : ");
    scanf("%d", &n);
    printf("Enter head position : ");
    scanf("%d", &headPosition);
    int requests[n];
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter request : ");
        scanf("%d", &requests[i]);
    }
    printf("\nSeek sequence : ");
    sstf(n, headPosition, requests);
}