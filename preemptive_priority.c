#include <stdio.h>
#include <limits.h>

// Define a structure to represent a process
struct Process {
    int process_id;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int priority;
};

// Function to calculate waiting time for each process using Priority Scheduling
void calculateWaitingTime(struct Process processes[], int n, int waiting_time[]) {
    int complete_count = 0;
    int current_time = 0;
    int i, highest_priority, shortest_arrival;

    // Initialize remaining_time for each process
    for (i = 0; i < n; i++)
        processes[i].remaining_time = processes[i].burst_time;

    while (complete_count != n) {
        highest_priority = INT_MAX;
        shortest_arrival = INT_MAX;

        int selected_process = -1;
        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time &&
                processes[i].remaining_time > 0 && processes[i].priority < highest_priority) {
                selected_process = i;
                highest_priority = processes[i].priority;
            }
        }

        if (selected_process == -1) {
            current_time++;
            continue;
        }

        processes[selected_process].remaining_time--;
        current_time++;

        if (processes[selected_process].remaining_time == 0) {
            waiting_time[selected_process] = current_time -
                processes[selected_process].burst_time - processes[selected_process].arrival_time;
            complete_count++;
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
    int n, i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input arrival time, burst time, and priority for each process
    for (i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].process_id = i + 1;
    }

    calculateAverageTimes(processes, n);

    return 0;
}
