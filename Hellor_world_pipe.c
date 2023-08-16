#include <stdio.h>
#include <stdlib.h>
int main()
{
int pipefd[2], n, pid;
char buff[100];
pipe(pipefd);
printf("\n readfd = %d", pipefd[0]);
printf("\n writefd = %d", pipefd[1]);

pid = fork();
if (pid == 0)
{
close(pipefd[0]);
printf("\n CHILD PROCESS SENDING DATA.\n");
write(pipefd[1], "hello world", 12);
}
else
{
close(pipefd[1]);
printf("\n PARENT PROCESS RECIEVES DATA\n");
n = read(pipefd[0], buff, sizeof(buff));
printf("\n size of data %d", n);
printf("\n data recieved from child through pipe : %s\n", buff);
}
}