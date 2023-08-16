#include <stdio.h>

// Define a structure to represent a process
struct Process {
    int process_id;
    int burst_time;
    int arrival_time;
    int remaining_time;
};

// Function to calculate waiting time for each process using Round Robin scheduling
void calculateWaitingTime(struct Process processes[], int n, int time_quantum, int waiting_time[]) {
    int remaining_burst_time[n];
    int i, complete_count = 0, current_time = 0;

    // Initialize arrays
    for (i = 0; i < n; i++) {
        remaining_burst_time[i] = processes[i].burst_time;
        waiting_time[i] = 0;
    }

    while (complete_count != n) {
        for (i = 0; i < n; i++) {
            if (remaining_burst_time[i] > 0) {
                if (remaining_burst_time[i] <= time_quantum) {
                    current_time += remaining_burst_time[i];
                    waiting_time[i] += current_time - processes[i].burst_time - processes[i].arrival_time;
                    remaining_burst_time[i] = 0;
                    complete_count++;
                } else {
                    current_time += time_quantum;
                    remaining_burst_time[i] -= time_quantum;
                    waiting_time[i] += current_time - processes[i].arrival_time;
                }
            }
        }
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(struct Process processes[], int n, int waiting_time[], int turnaround_time[]) {
    int i;

    for (i = 0; i < n; i++)
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
}

// Function to calculate and print average waiting and turnaround times
void calculateAverageTimes(struct Process processes[], int n, int time_quantum) {
    int waiting_time[n], turnaround_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;
    int i;

    // Calculate waiting time and turnaround time for each process
    calculateWaitingTime(processes, n, time_quantum, waiting_time);
    calculateTurnaroundTime(processes, n, waiting_time, turnaround_time);

    // Calculate total waiting and turnaround times
    for (i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Calculate average waiting and turnaround times
    double avg_waiting_time = (double)total_waiting_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;

    // Print the Gantt Chart
    printf("Gantt Chart:\n");
    for (i = 0; i < n; i++) {
        printf("P%d ", processes[i].process_id);
    }
    printf("\n");

    // Print average times
    printf("\nAverage Waiting Time: %.2lf\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2lf\n", avg_turnaround_time);
}

int main() {
    int n, i, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input arrival time and burst time for each process
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].process_id = i + 1;
    }

    // Input time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    // Calculate and print average times using Round Robin scheduling
    calculateAverageTimes(processes, n, time_quantum);

    return 0;
}
