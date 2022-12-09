#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = getpid();
  pid_t ppid;
  for (int i = 0; i < 3; ++i) {
    int status;
    int pid_from_fork = fork();
    if (pid_from_fork == -1) {
      exit(127);
    } else if (pid_from_fork == 0) {
      waitpid(getppid(), &status, 0);
    } else {
      if (getpid() != pid) {
        waitpid(getppid(), &status, 0);
      }
    }

    pid = getpid();
    ppid = getppid();
    printf(
        "My pid = %d, my ppid = %d, pid from fork = %d\n",
        (int)pid, (int)ppid, pid_from_fork);
  }
}