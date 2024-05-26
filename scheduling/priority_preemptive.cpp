// #include<iostream>
// #include<vector>
// #include<algorithm>
// #include<queue>
// using namespace std;

// class Process {
//     public:
//           int pid;
//           int at;
//           int bt;
//           int ct;
//           int priority;
//           int wt;
//           int tat;
//           int rt;

//           Process(int pid,int at,int bt,int priority){
//             this->pid=pid;
//             this->at = at;
//             this->bt = bt;
//             this->priority = priority;
//             this->rt = bt;
//           }

// };


// int main(){

// vector<Process> processes ;

// processes.push_back(Process(1,0,5,10));
// processes.push_back(Process(2,1,4,20));
// processes.push_back(Process(3,2,2,30));
// processes.push_back(Process(4,4,1,40));


//  std::sort(processes.begin(), processes.end(), [](Process &p1, Process &p2) {
//         if (p1.at == p2.at) {
//             return p1.priority < p2.priority;
//         }
//         return p1.at < p2.at;
//     });
    
// int n =  processes.size();
// int currentTime = 0;
// int completedProcess = 0;

// queue<Process> readyqueue ;

// vector<Process> arrivedProcess = processes;

// while(completedProcess < n){

//    for(int i=0;i<arrivedProcess.size();i++){
//     Process p = arrivedProcess[i];

//     if(p.at <= currentTime){
//         readyqueue.push(p);
//         arrivedProcess.erase(arrivedProcess.begin()+i);
//         i--;
//     }
//    }

//    if(!readyqueue.empty()){

//     Process current = readyqueue.top();
//     readyqueue.pop();

//     currentTime = current.at;
//     current.rt =
//    }

// }
     

// }







#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<deque>
using namespace std;

class Process {
    public:
          int pid;
          int at;
          int bt;
          int ct;
          int priority;
          int wt;
          int tat;
          int rt;

          Process(int pid,int at,int bt,int priority){
            this->pid=pid;
            this->at = at;
            this->bt = bt;
            this->priority = priority;
            this->rt = bt;
          }

};




int main(){

vector<Process> processes ;

processes.push_back(Process(1,0,5,10));
processes.push_back(Process(2,1,4,20));
processes.push_back(Process(3,2,2,30));
processes.push_back(Process(4,4,1,40));


 std::sort(processes.begin(), processes.end(), [](Process &p1, Process &p2) {
        if (p1.at == p2.at) {
            return p1.priority < p2.priority;
        }
        return p1.at < p2.at;
    });
    
int n =  processes.size();
int currentTime = 0;
int completedProcess = 0;
Process* currentProcess =  nullptr;
std::queue<Process, std::deque<Process>> readyqueue;


vector<Process> arrivedProcess = processes;

while(completedProcess < n){

   for(int i=0;i<arrivedProcess.size();i++){
    Process p = arrivedProcess[i];
     if(p.at == currentTime){
      readyqueue.push(p);
   }
   }
    
    Process* highestPriority =  nullptr;

    for(Process p : processes){
        if(highestPriority == nullptr || p.priority > highestPriority->priority){
            highestPriority = &p;
        }
    }

    if(highestPriority !=nullptr){
        if(currentProcess == nullptr || currentProcess->priority > highestPriority->priority){
            currentProcess = highestPriority;
        }
        currentProcess->rt = currentProcess->rt -1;
        currentTime++;
        if(currentProcess->rt == 0){
            currentProcess->ct = currentTime;
            currentProcess->tat = currentProcess->ct - currentProcess->at;
            currentProcess->wt = currentProcess->tat - currentProcess->bt;
            completedProcess++;
            readyqueue.pop();
            currentProcess = NULL;

        }

    }else{

        currentTime++;
    }
     
   }

 cout << "PID\tAT\tBT\tPriority\tCT\tTAT\tWT\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.at << "\t" << p.bt << "\t" << p.priority << "\t\t" << p.ct << "\t" << p.tat << "\t" << p.wt << "\n";
    }
   
}





