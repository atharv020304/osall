import java.util.*;

class Process {
    int at;
    int bt;
    int ct;
    int pid;
    int priority;
    int tat;
    int wt;
    int rt;

    Process(int pid, int at, int bt, int priority) {
        this.pid = pid;
        this.at = at;
        this.bt = bt;
        this.priority = priority;
        this.rt = bt;
    }
}

public class PrioPCPU {
    public static void main(String[] args) {
        ArrayList<Process> processes = new ArrayList<>();
        processes.add(new Process(1, 0, 4, 1));
        processes.add(new Process(2, 1, 5, 3));
        processes.add(new Process(3, 2, 9, 1));
        processes.add(new Process(4, 5, 8, 2));
        Collections.sort(processes, Comparator.comparingInt((Process p) -> p.at).thenComparingInt(p -> p.priority));
        int currentTime = 0;
        int completedProcesses = 0;
        int n = processes.size();
        Process currentProcess = null;
        Queue<Process> readyQueue = new LinkedList<>();
        while (completedProcesses < n) {
            for (int i = 0; i < n; i++) {
                Process p = processes.get(i);
                if (p.at == currentTime) {
                    readyQueue.add(p);
                }
            }
            Process highestPriority = null;
            for (Process p : readyQueue) {
                if (highestPriority == null || p.priority < highestPriority.priority) {
                    highestPriority = p;
                }
            }
            if (highestPriority != null) {
                if (currentProcess == null || currentProcess.priority > highestPriority.priority) {
                    currentProcess = highestPriority;
                }
                currentProcess.rt--;
                currentTime++;
                if (currentProcess.rt == 0) {
                    currentProcess.ct = currentTime;
                    currentProcess.tat = currentProcess.ct - currentProcess.at;
                    currentProcess.wt = currentProcess.tat - currentProcess.bt;
                    completedProcesses++;
                    readyQueue.remove(currentProcess);
                    currentProcess = null;
                }
            } else {
                currentTime++;
            }
        }
        System.out.println("PID\tAT\tBT\tPriority\tCT\tTAT\tWT");
        for (Process p : processes) {
            System.out.println(
                    p.pid + "\t" + p.at + "\t" + p.bt + "\t" + p.priority + "\t\t" + p.ct + "\t" + p.tat + "\t" + p.wt);
        }
    }
}
