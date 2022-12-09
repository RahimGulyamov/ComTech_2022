#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid, ppid;
  int res;
  int a , b;
  int pid_from_fork = fork();
  if (pid_from_fork == -1) {
    exit(127);
  } else if (pid_from_fork == 0) {
    printf("Дочерний процесс\n a = ");
    scanf("%d", &a);
    printf(" b = ");
    scanf("%d", &b);
    res = a + b;
  } else {
    int status;
    waitpid(pid_from_fork, &status, 0);
    printf("status  %d\n", status);
    printf("Родительский процесс\n a = ");
    scanf("%d", &a);
    printf(" b = ");
    scanf("%d", &b);
    res = a * b;
  }
  pid = getpid();
  ppid = getppid();
  printf("My pid = %d, my ppid = %d, pid from fork = %d, result = %d\n",
         (int)pid, (int)ppid, pid_from_fork, res);
}