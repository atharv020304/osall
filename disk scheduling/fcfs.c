#include <stdio.h>
#include <stdlib.h>

void main()
{
    int n, done = 0, headPosition;
    float tso = 0;
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
    for (int i = 0; i < n; i++)
    {
        tso = tso + abs(headPosition - requests[i]);
        headPosition = requests[i];
        done++;

        if (done == n)
        {
            printf("%d\n", requests[i]);
        }
        else
        {
            printf("%d -> ", requests[i]);
        }
    }
    printf("\nTotal Seek operations : %.2f\n", tso);
    printf("Average Seek Length : %.2f\n", tso / n);
}