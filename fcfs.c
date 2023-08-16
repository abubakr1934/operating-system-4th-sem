#include <stdio.h>

struct Process
{
    int process_id;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
};

// Calculate waiting time for each process
void calculateWaitingTime(struct Process processes[], int n)
{
    int i;

    // Initialize waiting time for the first process
    processes[0].waiting_time = 0;

    // Calculate waiting time for subsequent processes
    for (i = 1; i < n; i++)
    {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
}

// Calculate turnaround time for each process
void calculateTurnaroundTime(struct Process processes[], int n)
{
    int i;

    // Calculate turnaround time for each process
    for (i = 0; i < n; i++)
    {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

// Calculate and display average waiting and turnaround times
void calculateAverageTimes(struct Process processes[], int n)
{
    int total_waiting_time = 0, total_turnaround_time = 0;
    int i;

    // Calculate waiting and turnaround times for each process
    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);

    // Calculate total waiting and turnaround times
    for (i = 0; i < n; i++)
    {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    // Calculate average waiting and turnaround times
    double avg_waiting_time = (double)total_waiting_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;

    // Print the Gantt Chart
    printf("Gantt Chart:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d ", processes[i].process_id);
    }
    printf("\n");

    // Print average waiting and turnaround times
    printf("\nAverage Waiting Time: %.2lf\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2lf\n", avg_turnaround_time);
}

int main()
{
    int n, i;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input arrival time and burst time for each process
    for (i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].process_id = i + 1;
    }

    // Calculate and display average times
    calculateAverageTimes(processes, n);

    return 0;
}
