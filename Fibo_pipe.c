#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
int pip[2], n;
pid_t pid;
int b;
int result = pipe(pip);
if (result < 0)
{
perror("pipe ");

exit(1);
}
int fib[100];
pid = fork();
if (pid == -1)
{
printf("Fork Failed!!\n");
}
else if (pid == 0)
{ // CHILD PROCESS
close(pip[0]);
printf("Enter a limit for Fibonacci numbers between 1 and 50:\n");
scanf("%d", &n);
fib[0] = 0;
fib[1] = 1;
for (int i = 2; i < n; i++)
{
fib[i] = fib[i - 1] + fib[i - 2];
}
write(pip[1], &n, sizeof(int));
write(pip[1], fib, n * sizeof(int));
close(pip[1]);
}
else
{ // PARENT PROCESS
close(pip[1]);
read(pip[0], &n, sizeof(int));
b = read(pip[0], fib, 100 * sizeof(int));
close(pip[0]);
printf("Fibonacci numbers are:\n");
for (int i = 0; i < n; i++)
{
printf("%d ", fib[i]);
}
printf("\n");
printf("Now separating Fibonacci numbers based on even and odd:\n");
printf("Even Numbers:\n");
for (int i = 0; i < n; i++)
{
if (fib[i] % 2 == 0)
printf("%d ", fib[i]);
}
printf("\n");

printf("Odd Numbers:\n");
for (int i = 0; i < n; i++)
{
if (fib[i] % 2 != 0)
printf("%d ", fib[i]);
}
printf("\n");
}
return 0;
}