#include <stdio.h>

void lur(int numOfFrames, int numOfPages, int pages[])
{
    int position;
    int frame[numOfFrames];
    for (int i = 0; i < numOfFrames; i++)
    {
        frame[i] = -1;
    }

    int hit = 0, miss = 0;

    for (int i = 0; i < numOfPages; i++)
    {
        int flag1 = 0, flag2 = 0;

        for (int j = 0; j < numOfFrames; j++)
        {
            if (frame[j] == pages[i])
            {
                hit++;
                flag1 = flag2 = 1;
                break;
            }
        }
        if (flag1 == 0)
        {
            for (int j = 0; j < numOfFrames; j++)
            {
                if (frame[j] == -1)
                {
                    frame[j] = pages[i];
                    miss++;
                    flag2 = 1;
                    break;
                }
            }
        }
        if (flag2 == 0)
        {
            int flag3 = 0;
            int temp[numOfFrames];
            for (int j = 0; j < numOfFrames; j++)
            {
                temp[j] = -1;
                for (int k = i - 1; k >= 0; k--)
                {
                    if (frame[j] == pages[k])
                    {
                        temp[j] = k;
                        break;
                    }
                }
            }

            for (int j = 0; j < numOfFrames; j++)
            {
                if (temp[j] == -1)
                {
                    position = j;
                    flag3 = 1;
                    break;
                }
            }

            if (flag3 == 0)
            {
                int min = temp[0];
                position = 0;
                for (int j = 1; j < numOfFrames; j++)
                {
                    if (temp[j] < min)
                    {
                        min = temp[j];
                        position = j;
                    }
                }
            }
            frame[position] = pages[i];
            miss++;
        }
        printf("\nSymbol: %d  Frame: ", pages[i]);
        for (int j = 0; j < numOfFrames; j++)
        {
            printf("%d ", frame[j]);
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
    lur(f, p, pages);
}