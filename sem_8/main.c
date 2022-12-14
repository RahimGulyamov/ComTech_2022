#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int *array;
  int shmid;
  int new = 1;
  char pathname[] = "main.c";
  key_t key;

  if ((key = ftok(pathname, 0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  int pid_from_fork = fork();

  if (pid_from_fork == -1) {
    exit(127);
  }

  if ((shmid = shmget(key, 3 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
    if (errno != EEXIST) {
      printf("Can\'t create shared memory\n");
      exit(-1);
    } else {
      if ((shmid = shmget(key, 3 * sizeof(int), 0)) < 0) {
        printf("Can\'t find shared memory\n");
        exit(-1);
      }
      new = 0;
    }
  }

  if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }

  if (pid_from_fork == 0) {
    printf("Дочерний процесс\n");
    if (new) {
      array[0] = 0;
      array[1] = 1;
      array[2] = 1;
    } else {
      array[1] += 1;
      array[2] += 1;
    }

    printf(
        "Parent program was spawn %d times, Child program - %d times, total - "
        "%d "
        "times\n",
        array[0], array[1], array[2]);
  } else {
    printf("Родительский процесс\n");
    if (new) {
      array[0] = 1;
      array[1] = 0;
      array[2] = 1;
    } else {
      array[0] += 1;
      array[2] += 1;
    }

    printf(
        "Parent program was spawn %d times, Child program - %d times, total - "
        "%d "
        "times\n",
        array[0], array[1], array[2]);
  }

  if (shmdt(array) < 0) {
    printf("Can't detach shared memory\n");
    exit(-1);
  }

  return 0;
}