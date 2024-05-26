#include <stdio.h>

void fifo(int numOfFrames, int numOfPages, int pages[])
{
    int frame[numOfFrames];
    for (int i = 0; i < numOfFrames; i++)
    {
        frame[i] = -1;
    }

    int hit = 0, miss = 0, index = -1;
    for (int i = 0; i < numOfPages; i++)
    {
        int flag = 0;
        for (int j = 0; j < numOfFrames; j++)
        {
            if (frame[j] == pages[i])
            {
                flag = 1;
                break;
            }
        }

        if (flag)
        {
            printf("\nSymbol: %d  Frame: ", pages[i]);
            for (int k = 0; k < numOfFrames; k++)
            {
                printf("%d ", frame[k]);
            }
            hit++;
        }
        else
        {
            index = (index + 1) % numOfFrames;
            frame[index] = pages[i];
            miss++;
            printf("\nSymbol: %d  Frame: ", pages[i]);
            for (int k = 0; k < numOfFrames; k++)
            {
                printf("%d ", frame[k]);
            }
        }
    }
    printf("\n\nPage hits: %d", hit);
    printf("\nPage misses: %d", miss);
}

void main()
{
    int p, f;
    printf("Enter number of frames : ");
    scanf("%d", &f);
    printf("Enter number of pages : ");
    scanf("%d", &p);

    int pages[p];
    for (int i = 0; i < p; i++)
    {
        printf("Enter page : ");
        scanf("%d", &pages[i]);
    }
    fifo(f, p, pages);
}

