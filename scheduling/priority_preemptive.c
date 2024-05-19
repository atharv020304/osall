#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
struct node
{
    int process, AT, BT, WT, TAT, vis, tempBT, FT, oBT, priority;
};

struct link
{
    struct node data;
    struct link *next;
};

struct link *head = NULL;

void insert(struct node t)
{
    struct link *temp = head;
    struct link *newnode = (struct link *)malloc(sizeof(struct link));
    newnode->data = t;
    newnode->next = NULL;
    if (head == NULL)
    {
        head = newnode;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

void Delete(int p)
{
    struct link *temp = head, *prevnode = head;
    while (temp->data.process != p)
    {
        prevnode = temp;
        temp = temp->next;
    }
    if (temp == head)
    {
        head = head->next;
        free(temp);
    }
    else
    {
        prevnode->next = temp->next;
        free(temp);
    }
}

bool isArrived(struct node arr[], int n, int t)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i].AT <= t && arr[i].vis == 0)
        {
            return true;
            break;
        }
    }
    return false;
}

void priorityBased(struct node arr[], struct node gChart[], int n, int t)
{
    float totalWT = 0, totalTAT = 0;
    printf("PID\tAT\tBT\tFT\tTAT\tWT\n");
    int done = 0, m, k = -1, time;
    for (int i = 0; i < n; i++)
    {
        if (arr[i].AT <= t && arr[i].vis == 0)
        {
            insert(arr[i]);
            arr[i].vis = 1;
        }
    }
    struct link *temp, *min;
    while (done != n)
    {
        m = 0;
        min = head, temp = head;
        while (temp != NULL)
        {
            if (temp->data.priority < min->data.priority)
            {
                min = temp;
            }
            temp = temp->next;
        }
        temp = min;
        t++;
        m++;
        if (isArrived(arr, n, t) == true)
        {
            k++;
            temp->data.BT = temp->data.BT - m;
            time = temp->data.BT;
            m = 0;
            gChart[k].process = temp->data.process;
            gChart[k].tempBT = temp->data.BT;
            if (time == 0)
            {
                temp->data.FT = t;
                totalWT = totalWT + temp->data.FT - temp->data.AT - temp->data.oBT;
                totalTAT = totalTAT + temp->data.FT - temp->data.AT;
                printf("%d\t%d\t%d\t%d\t%d\t%d\n", temp->data.process, temp->data.AT,
                       temp->data.oBT, temp->data.FT,
                       temp->data.FT - temp->data.AT,
                       temp->data.FT - temp->data.AT - temp->data.oBT);
                Delete(temp->data.process);
                done++;
            }
            for (int i = 0; i < n; i++)
            {
                if (arr[i].AT <= t && arr[i].vis == 0)
                {
                    insert(arr[i]);
                    arr[i].vis = 1;
                }
            }
        }
        else
        {
            temp->data.BT = temp->data.BT - m;
            if (temp->data.BT == 0)
            {
                k++;
                gChart[k].process = temp->data.process;
                gChart[k].tempBT = temp->data.BT;
                temp->data.FT = t;
                totalWT = totalWT + temp->data.FT - temp->data.AT - temp->data.oBT;
                totalTAT = totalTAT + temp->data.FT - temp->data.AT;
                printf("%d\t%d\t%d\t%d\t%d\t%d\n", temp->data.process, temp->data.AT,
                       temp->data.oBT, temp->data.FT,
                       temp->data.FT - temp->data.AT,
                       temp->data.FT - temp->data.AT - temp->data.oBT);
                Delete(temp->data.process);
                done++;
            }
        }
    }
    printf("\nGant Chart : ");
    for (int i = 0; i <= k; i++)
    {
        printf("%d ", gChart[i].process);
    }
    printf("\nAverage WT : %.2f\n", totalWT / n);
    printf("Average TAT : %.2f\n", totalTAT / n);
}

void main()
{
    int n;
    printf("Enter number of process : ");
    scanf("%d", &n);
    struct node arr[n];
    for (int i = 0; i < n; i++)
    {

        arr[i].process = i;
        printf("Enter AT , BT and Priority of process %d : ", i);
        scanf("%d %d %d", &arr[i].AT, &arr[i].BT, &arr[i].priority);
        arr[i].vis = 0;
        arr[i].oBT = arr[i].BT;
    }
    int t = 0;
    struct node gChart[20];
    priorityBased(arr, gChart, n, t);
}
