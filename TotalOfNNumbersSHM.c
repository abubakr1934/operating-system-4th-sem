#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#define buf_size 100
int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
20};
int main(void)
{
pid_t pid;
int i;
int *total;
char b[buf_size];
// Get the segment
int segment_id = shmget(IPC_PRIVATE, sizeof(int), S_IRUSR | S_IWUSR);
// Attach the segment with variable to be used by process
total = (int *)shmat(segment_id, NULL, 0);
*total = 0;
// Create new child
pid = fork();
if (pid == 0)
{
// Child Process
for (i = 10; i < 20; i++)
{
*total += a[i];
}

sprintf(b, "\nChild Total = %d\n\n", *total);
write(1, b, strlen(b));
}
else
{
// Parent Process
for (i = 0; i < 10; i++)
{
*total += a[i];
}
sprintf(b, "\nParent Total = %d\n\n", *total);
write(1, b, strlen(b));
pid = wait(NULL);
if (pid != -1)
{
printf("\nTotal of all Numbers = %d\n\n", *total);
}
shmdt(total);
// shmctl(segment_id, IPC_RMID, NULL); // Remove the shared memory
segment
}
return 0;
}