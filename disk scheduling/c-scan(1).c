#include <stdio.h>
#include <stdlib.h>

void cScan(int n, int headPosition, int tracks, int direction, int requests[])
{
    float tso = 0;
    int headCopy = headPosition;
    if (direction == 1)
    {
        for (int i = headPosition; i < tracks; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (requests[j] == i)
                {
                    tso += abs(requests[j] - headPosition);
                    headPosition = requests[j];
                    printf("%d ", requests[j]);
                }
            }
        }
        if (headPosition != tracks - 1)
        {
            tso += (tracks - 1) - headPosition;
            headPosition = tracks - 1;
        }
        tso += (headPosition - 0);
        headPosition = 0;
        for (int i = 0; i < headCopy; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (requests[j] == i)
                {
                    tso += abs(requests[j] - headPosition);
                    headPosition = requests[j];
                    printf("%d ", requests[j]);
                }
            }
        }
    }
    else if (direction == 2)
    {
        for (int i = headPosition; i >= 0; i--)
        {
            for (int j = 0; j < n; j++)
            {
                if (requests[j] == i)
                {
                    tso += abs(requests[j] - headPosition);
                    headPosition = requests[j];
                    printf("%d ", requests[j]);
                }
            }
        }
        if (headPosition != 0)
        {
            tso += headPosition;
            headPosition = 0;
        }
        tso += (tracks - 1) - 0; // tracks - 0
        headPosition = tracks - 1;
        for (int i = tracks - 1; i > headCopy; i--)
        {
            for (int j = 0; j < n; j++)
            {
                if (requests[j] == i)
                {
                    tso += abs(requests[j] - headPosition);
                    headPosition = requests[j];
                    printf("%d ", requests[j]);
                }
            }
        }
    }
    printf("\nTotal Seek operations : %.2f\n", tso);
    printf("Average Seek Length : %.2f\n", tso / n);
}

void main()
{
    int n, headPosition, tracks, dirction;
    printf("Enter number of requests : ");
    scanf("%d", &n);
    printf("Enter number of tracks : ");
    scanf("%d", &tracks);
    printf("Enter head position : ");
    scanf("%d", &headPosition);
    printf("Enter direction (1 - Right or 2 - Left ) : ");
    scanf("%d", &dirction);
    int requests[n];
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter request : ");
        scanf("%d", &requests[i]);
    }
    printf("\nSeek sequence : ");
    cScan(n, headPosition, tracks, dirction, requests);
}