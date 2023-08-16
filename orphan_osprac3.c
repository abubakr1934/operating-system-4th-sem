#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == 0) {
        // Child process
        printf("Child process (PID %d) is running.\n", getpid());
        sleep(5); // Simulate some work
        printf("Child process (PID %d) is exiting.\n", getpid());
    } else if (child_pid > 0) {
        // Parent process
        printf("Parent process (PID %d) is running.\n", getpid());
        printf("Parent process (PID %d) is exiting.\n", getpid());
    } else {
        // Error handling
        fprintf(stderr, "Fork failed.\n");
        return 1;
    }

    return 0;
}
