#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

class Process{
    public:
        int pid;
        int at;
        int bt;
        int ct;
        int wt;
        int tat;

        Process(int pid,int at,int bt){
            this->pid=pid;
            this->at = at;
            this->bt =bt;
        }
};

int main(){

std::vector<Process>processes;

     processes.push_back(Process(1,0,2));
     processes.push_back(Process(2,1,2));
     processes.push_back(Process(3,5,3));
     processes.push_back(Process(4,6,4));
     

std::sort(processes.begin(),processes.end(),[](const Process &a, const Process &b){
    return a.at < b.at;
});

int currentTime = 0;
for(int i=0;i<processes.size();i++){
    Process &p = processes[i];
    if(currentTime < p.at){
        currentTime = p.at;
    }
    p.ct = currentTime + p.bt;
    currentTime = p.ct;
    p.tat = p.ct - p.at;
    p.wt = p.tat - p.bt;
}

cout <<"pid"<<"\t"<<"at"<<"\t"<<"bt"<<"\t"<<"ct"<<"\t"<<"tat"<<"\t"<<"wt"<<endl;

for(int i=0;i<processes.size();i++){
    Process &p = processes[i];
    cout <<p.pid<<"\t"<<p.at<<"\t"<<p.bt<<"\t"<<p.ct<<"\t"<<p.tat<<"\t"<<p.wt<<endl;
}
}