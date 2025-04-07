#include <stdio.h>

struct process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

int main()
{

    int n;
    printf("Enter the number of process: ");
    scanf("%d", &n);

    struct process p[n];

    for (int i = 0; i < n; i++)
    {
        printf("enter the arrivalTime and burstTime for the process p[%d]: ", i + 1);
        p[i].pid = i + 1;
        scanf("%d%d", &p[i].arrivalTime, &p[i].burstTime);
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; i < n - i - 1; i++)
        {
            if (p[j].arrivalTime > p[j + 1].arrivalTime)
            {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int currentTime = p[0].arrivalTime;
    p[0].waitingTime = 0;
    p[0].turnaroundTime = p[0].burstTime;
    currentTime += p[0].burstTime;

    for (int i = 1; i < n; i++)
    {
        if (currentTime < p[i].arrivalTime)
        {
            currentTime += p[i].arrivalTime;
        }

        p[i].waitingTime = currentTime - p[i].arrivalTime;
        p[i].turnaroundTime = p[i].waitingTime + p[i].burstTime;
        currentTime += p[i].burstTime;
    }

    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
    {
        avg_waiting_time += p[i].waitingTime;
        avg_turnaround_time += p[i].turnaroundTime;
        printf("P[%d]\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime,
               p[i].waitingTime, p[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", avg_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time / n);
}
