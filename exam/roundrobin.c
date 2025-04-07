#include <stdio.h>

struct Process {
    int pid;
    int at; // arrival time
    int bt; // burst time
    int rt; // remaining time
    int ct; // completion time
    int tat; // turnaround time
    int wt;  // waiting time
};

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int i;

    // Taking input
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt; // Initially remaining time = burst time
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int time = 0, done = 0;
    int completed[n];
    for (i = 0; i < n; i++) completed[i] = 0;

    // Loop until all processes are done
    while (done < n) {
        int found = 0;

        for (i = 0; i < n; i++) {
            // If process has arrived and has remaining time
            if (p[i].at <= time && p[i].rt > 0) {
                found = 1;

                if (p[i].rt > tq) {
                    time += tq;
                    p[i].rt -= tq;
                } else {
                    time += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = time;
                    done++;
                }
            }
        }

        // If no process is ready, just increment time
        if (!found) time++;
    }

    // Calculate TAT and WT
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}
