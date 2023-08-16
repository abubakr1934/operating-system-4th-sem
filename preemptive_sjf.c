#include <stdio.h>
#include <limits.h>

// Define a structure to represent a process
struct Process {
    int process_id;
    int burst_time;
    int arrival_time;
    int remaining_time;
};

// Function to calculate waiting time for each process
void calculateWaitingTime(struct Process processes[], int n, int waiting_time[]) {
    int shortest_remaining_time;
    int complete_count = 0;
    int current_time = 0;
    int i, shortest;

    // Initialize remaining_time for each process
    for (i = 0; i < n; i++)
        processes[i].remaining_time = processes[i].burst_time;

    // Loop until all processes are complete
    while (complete_count != n) {
        shortest = -1;
        shortest_remaining_time = INT_MAX;

        // Find the process with the shortest remaining time that has arrived
        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time &&
                processes[i].remaining_time < shortest_remaining_time &&
                processes[i].remaining_time > 0) {
                shortest = i;
                shortest_remaining_time = processes[i].remaining_time;
            }
        }

        if (shortest == -1) {
            current_time++; // No eligible process, increment time
            continue;
        }

        processes[shortest].remaining_time--; // Decrement remaining time
        current_time++; // Increment current time

        if (processes[shortest].remaining_time == 0) {
            // If process is complete, calculate waiting time
            waiting_time[shortest] = current_time -
                processes[shortest].burst_time - processes[shortest].arrival_time;
            complete_count++;
        }
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(struct Process processes[], int n, int waiting_time[], int turnaround_time[]) {
    int i;

    // Calculate turnaround time for each process
    for (i = 0; i < n; i++)
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
}

// Function to calculate and print average waiting and turnaround times
void calculateAverageTimes(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;
    int i;

    // Calculate waiting time and turnaround time for each process
    calculateWaitingTime(processes, n, waiting_time);
    calculateTurnaroundTime(processes, n, waiting_time, turnaround_time);

    // Calculate total waiting and turnaround times
    for (i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Calculate average waiting and turnaround times
    double avg_waiting_time = (double) total_waiting_time / n;
    double avg_turnaround_time = (double) total_turnaround_time / n;

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

    // Calculate and print average times
    calculateAverageTimes(processes, n);

    return 0;
}
