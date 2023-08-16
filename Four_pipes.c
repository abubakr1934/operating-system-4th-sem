#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int p1[2], p2[2], p3[2], p4[2]; // Arrays for pipe file descriptors
    int i, j = 0, k = 0, l = 0;
    char r[10], s[10], t[10], u[10]; // Character arrays for strings

    printf("\t PROCESS 1.ENTER THE STRING\n");
    scanf("%s", r); // Read a string from user input

    pipe(p1); // Create pipe 1 for process 1 and process 2 communication
    pipe(p2); // Create pipe 2 for process 1 and process 3 communication
    write(p1[1], r, sizeof(r)); // Write the string to pipe 1
    write(p2[1], r, sizeof(r)); // Write the string to pipe 2

    int a = fork(); // Forking process 2
    if (a == 0) {
        // Child process 2
        printf("\n\t PROCESS 2: it splits the given string\n");
        read(p1[0], r, sizeof(r)); // Read the string from pipe 1

        int n = strlen(r);
        for (i = 0; i < n / 2; i++)
            s[i] = r[i]; // Copy first half of string to s
        for (i = n / 2; i <= n; i++)
            t[j++] = r[i]; // Copy second half of string to t

        pipe(p3); // Create pipe 3 for process 2 and process 4 communication
        pipe(p4); // Create pipe 4 for process 2 and process 5 communication
        write(p3[1], s, sizeof(s)); // Write sub-string s to pipe 3
        write(p4[1], t, sizeof(t)); // Write sub-string t to pipe 4

        int b = fork(); // Forking process 4
        if (b == 0) {
            // Child process 4
            printf("p4 %d\t", getpid());
            printf("p2 %d\n", getppid());
            read(p3[0], s, sizeof(s)); // Read sub-string s from pipe 3
            printf("\t PROCESS 4: sub string \t %s \t\n", s);
            printf("no of char=%d \n", strlen(s));
        } else {
            int c = fork(); // Forking process 5
            if (c == 0) {
                // Child process 5
                printf("p5 %d\t", getpid());
                printf("p2 %d\n", getppid());
                read(p4[0], t, sizeof(t)); // Read sub-string t from pipe 4
                printf("\t PROCESS 5: sub string \t %s \t", t);
                printf("no of char=%d \n", strlen(t));
            } else {
                wait(); // Wait for both process 4 and process 5 to complete
                printf("p2 %d\t", getpid());
                printf("p1 %d\n", getppid());
            }
        }
    } else {
        wait(); // Wait for process 2 to complete
        int d = fork(); // Forking process 3
        if (d == 0) {
            // Child process 3
            printf("p3 %d\t", getpid());
            printf("p1 %d\n", getppid());
            read(p2[0], r, sizeof(r)); // Read the string from pipe 2

            for (i = strlen(r) - 1; i >= 0; i--)
                u[l++] = r[i]; // Reverse the string and store in u

            for (i = 0; i < strlen(r); i++) {
                if (u[i] == r[i])
                    k++; // Count matching characters between u and r
                else
                    continue;
            }
            if (k == strlen(r))
                printf("\t PROCESS 3: the given string is palindrome\n");
            else
                printf("\t PROCESS 3: the given string is not palindrome\n");
        } else {
            printf("p1 %d\t", getpid());
            printf("kernal %d\t\n", getppid());
        }
    }

    return 0;
}
