#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int prio;       // Priority
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
    int isDone;  
    int rt;   // Flag to check if process is completed
};

int main() {
    int n = 3;
    struct Process p[3];

    // Input the processes
    p[0].pid = 1; p[0].at = 0; p[0].bt = 5; p[0].prio = 2;
    p[1].pid = 2; p[1].at = 1; p[1].bt = 3; p[1].prio = 1;
    p[2].pid = 3; p[2].at = 2; p[2].bt = 4; p[2].prio = 3;

    // Mark all processes as not done
    for (int i = 0; i < n; i++) {
        p[i].isDone = 0;
    }

    int completed = 0;
    int currentTime = 0;

    while (completed < n) {
        int idx = -1;
        int highestPriority = 9999;

        // Find the process with the highest priority that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].isDone == 0) {
                if (p[i].prio < highestPriority) {
                    highestPriority = p[i].prio;
                    idx = i;
                } else if (p[i].prio == highestPriority) {
                    // If priorities are same, choose the one with earlier arrival
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        //premptive priority scheduling

        if (idx != -1) {
            currentTime += p[idx].bt;
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].isDone = 1;
            completed++;
        } else {
            // No process has arrived yet, move time forward
            currentTime++;
        }

        // non premptive priority scheduling

        if (idx != -1) {
            p[idx].rt--;
            currentTime++;

            if (p[idx].rt == 0) {
                p[idx].ct = currentTime;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].isDone = 1;
                completed++;
            }
        } else {
            currentTime++; // No process ready, idle time
        }
    }

    // Print the result
    printf("PID\tAT\tBT\tPRIO\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].prio, p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}
