
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
    }
};

struct CompareRemainingTime
{
    bool operator()(Process *const &p1, Process *const &p2)
    {
        if (p1->rt == p2->rt)
        {
            return p1->at > p2->at;
        }
        return p1->rt > p2->rt;
    }
};

int main()
{

    vector<Process> processes;

    processes.push_back(Process(1, 0, 6));
    processes.push_back(Process(1, 1, 3));
    processes.push_back(Process(3, 2, 3));
    processes.push_back(Process(1, 4, 1));

    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
              { return a.at < b.at; });

    std::priority_queue<Process *, vector<Process *>, CompareRemainingTime> pq;

    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    int i = 0;

    while (completed != n)
    {

        while (i < n && processes[i].at <= currentTime)
        {
            pq.push(&processes[i]);
            i++;
        }

        if (!pq.empty())
        {
            Process *currentProcess = pq.top();
            pq.pop();

            currentProcess->rt--;
            currentTime++;

            // completion of process:->

            if (currentProcess->rt == 0)
            {
                completed++;
                currentProcess->ct = currentTime;
                currentProcess->tat = currentTime - currentProcess->at;
                currentProcess->wt = currentProcess->tat - currentProcess->bt;
            }
            else
            {
                pq.push(currentProcess);
            }
        }
        else
        {
            currentTime++;
        }
    }

    cout << "pid\tat\tbt\tct\ttat\twt" << endl;
    for (const Process &p : processes)
    {
        cout << p.pid << "\t" << p.at << "\t" << p.bt << "\t" << p.ct << "\t" << p.tat << "\t" << p.wt << endl;
    }

    return 0;
}