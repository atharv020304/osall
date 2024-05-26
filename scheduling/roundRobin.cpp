#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Process
{
public:
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int wt;
    int tat;

    Process(int pid, int at, int bt)
    {
        this->pid = pid;
        this->at = at;
        this->bt = bt;
        this->rt = bt;
        this->ct = 0;
        this->wt = 0;
        this->tat = 0;
    }
};

int main() {
    vector<Process> processes;
    processes.push_back(Process(1, 0, 5));
    processes.push_back(Process(2, 1, 4));
    processes.push_back(Process(3, 2, 2));
    processes.push_back(Process(4, 4, 1));
    int timequantum = 2;
    int currTime = 0;

    queue<Process> readyQ;
    vector<Process> arrivedProcesses = processes;  
    int completedprocesses = 0;
    int n = processes.size();

    while (completedprocesses < n) {
   
        for (int i = 0; i < arrivedProcesses.size(); i++) {
            Process p = arrivedProcesses[i];
            if (p.at <= currTime) {
                readyQ.push(p);
                arrivedProcesses.erase(arrivedProcesses.begin() + i);
                i--;
            }
        }

        if (!readyQ.empty()) {
            Process current = readyQ.front();
            readyQ.pop();  
            int executionTime = min(timequantum, current.rt);
            currTime += executionTime;
            current.rt -= executionTime;

            for (int i = 0; i < arrivedProcesses.size(); i++) {
                Process p = arrivedProcesses[i];
                if (p.at <= currTime) {
                    readyQ.push(p);
                    arrivedProcesses.erase(arrivedProcesses.begin() + i);
                    i--;
                }
            }

            if (current.rt > 0) {
                readyQ.push(current); 
            } else {
                current.ct = currTime;
                current.tat = currTime - current.at;
                current.wt = current.tat - current.bt;
                for (auto &p : processes) {
                    if (p.pid == current.pid) {
                        p = current;
                        break;
                    }
                }
                completedprocesses++;
            }
        } else {
            currTime++;
        }
    }

    cout << "PID\tAT\tBT\tCT\tTAT\tWT" << endl;
    for (Process p : processes) {
        cout << p.pid << "\t" << p.at << "\t" << p.bt << "\t" << p.ct << "\t" << p.tat << "\t" << p.wt << endl;
    }

    return 0;
}
