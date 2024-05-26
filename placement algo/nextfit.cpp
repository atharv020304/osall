#include<iostream>
using namespace std;

void nextfit(int m,int n,int block[],int process[]){

int allocation[n];
for(int i=0;i<n;i++){
    allocation[i] = -1;
}

for(int i=0;i<n;i++){
    int count = 0;
    int j=0;
    while(count < m){
         
      if(block[j] >= process[i]){
        allocation[i] = j;
        block[j] -= process[i];
        break;
      }
      j = (j+1) % m;
      count++;
    }
}


printf("\nProcess No.\tProcess size\tblock no\n");
for(int i=0;i<n;i++){
    printf(" %d\t\t",i+1);
    printf("%d\t\t",process[i]);
    if(allocation[i] != -1){
        printf("%d\n",allocation[i]+1);
    }else{
        printf("not allocated");
    }
    printf("\n");
}
}



int main(){
int m,n;
printf("enter number of blocks ");
scanf("%d",&m);
printf("enter number of processes ");
scanf("%d",&n);

int block[m];
int process[n];

for(int i=0;i<m;i++){
    printf("enter size of block :");
    scanf("%d",&block[i]);
}

for(int i=0;i<n;i++){
    printf("enter size of process :");
    scanf("%d",&process[i]);
}


nextfit(m,n,block,process);   

}