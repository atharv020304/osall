#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Process {
public:
    int at; 
    int ct = 0; 
    int bt; 
    int pid; 
    int priority; 
    int tat = 0; 
    int wt = 0; 

    Process(int pid, int at, int bt, int priority) {
        this->pid = pid;
        this->at = at;
        this->bt = bt;
        this->priority = priority;
    }
    
};

int main() {

    vector<Process> processes;

    processes.push_back(Process(1, 0, 4, 1));
    processes.push_back(Process(2, 1, 5, 3));
    processes.push_back(Process(3, 2, 9, 1));
    processes.push_back(Process(4, 5, 8, 2));

    std::sort(processes.begin(), processes.end(), [](Process &p1, Process &p2) {
        if (p1.at == p2.at) {
            return p1.priority < p2.priority;
        }
        return p1.at < p2.at;
    });

    int currentTime = 0;
    int completedProcess = 0;
    int n = processes.size();

    while (completedProcess < n) {
        Process* highestPriority = nullptr;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= currentTime && processes[i].ct == 0) { 
                if (highestPriority == nullptr || processes[i].priority < highestPriority->priority) {
                    highestPriority = &processes[i];
                }
            }
        }

        if (highestPriority != nullptr) {
            currentTime = max(currentTime, highestPriority->at);
            currentTime += highestPriority->bt;
            highestPriority->ct = currentTime;
            highestPriority->tat = highestPriority->ct - highestPriority->at;
            highestPriority->wt = highestPriority->tat - highestPriority->bt;
            completedProcess++;
        } else {
            currentTime++;
        }
    }

    cout << "PID\tAT\tBT\tPriority\tCT\tTAT\tWT\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.at << "\t" << p.bt << "\t" << p.priority << "\t\t" << p.ct << "\t" << p.tat << "\t" << p.wt << "\n";
    }

    return 0;
}





