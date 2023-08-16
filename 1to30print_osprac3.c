#include <stdio.h>
void main()
{
int pid1, i;
pid1 = fork();
if (pid1 == 0)
{
printf("I am the child process\n");
for (i = 0; i < 30; i++)
{
printf("%d\n", i);
sleep(1);
// system("ps -el");
}
exit(0);
}
else
{
wait(0);
sleep(10);
printf("I am the Parent Process\n");
wait(0);
// sleep(10);
printf("I am the Parent Process\n");
// wait(0);
}
}