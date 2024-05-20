#include<iostream>
#include<cstdio>
using namespace std;

int main(){
 int count;
 int n;
 int headposition;
 int seektime = 0;
 printf("enter number of requests");
 scanf("%d",&n);
 int request[n];

 for(int i=0;i<n;i++){
    printf("enter the request: ");
    scanf("%d ",&request[i]);
 }

 printf("enter the head position: ");\
 scanf("%d",&headposition);

 for(int i =0;i<n;i++){
    int temp = abs(headposition - request[i]);
    seektime += temp;
    headposition =  request[i];

    if(count == n){
        printf("%d ",request[i]);
    }else{
        printf("%d -> ",request[i]);
    }
 }

 printf("Total seek time : %d",seektime);
 printf("avg seel time :%d",seektime/n);

 return 0;
}