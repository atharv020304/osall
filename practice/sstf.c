#include<stdio.h>
#include<stdlib.h>

int sstf(int headposition,int request[],int n){
int visited[n];
for(int i=0;i<n;i++){
    visited[i] = 0;
}
float seektime = 0;
int count= 0;

for(int i=0;i<n;i++){
    int min = 9999;
    int index;
    for(int j=0;j<n;j++){
        if(visited[j] == 0){
            if(abs(headposition - request[j]) < abs(headposition - min)){
                min =  request[j];
                index = j;
            }
        }
    }
        seektime += abs(headposition - min);
        headposition = min;
        count++;
        visited[index] = 1;
        if(count == n){
            printf("%d ",min);
        }else{
            printf("%d ->",min);
        }
    
}

printf("total seek time : %f",seektime);
printf("avg : %f", seektime/n);
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
    sstf(headPosition,requests,n);

}