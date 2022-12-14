#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>

int main() {
  int *res;
  int shmid;
  int is_new = 1;
  int semid;
  char pathname[] = "first";
  key_t key;
  struct sembuf buf_first;
  struct sembuf buf_second;
  if ((key = ftok(pathname, 0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }
  if ((semid = semget(key, 2, 0666 | IPC_CREAT)) == -1) {
    printf("Can\'t get semid\n");
    exit(-1);
  }
  if ((shmid = shmget(key, 2 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
    if (errno != EEXIST) {
      printf("Can\'t create shared memory\n");
      exit(-1);
    } else {
      if ((shmid = shmget(key, 2 * sizeof(int), 0)) < 0) {
        printf("Can\'t find shared memory\n");
        exit(-1);
      }
      is_new = 0;
    }
  }
  if ((res = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }

  buf_first.sem_op = -1;
  buf_first.sem_flg = 0;
  buf_first.sem_num = 0;

  buf_second.sem_op = 1;
  buf_second.sem_flg = 0;
  buf_second.sem_num = 1;

  if (semop(semid, &buf_second, 1) < 0) {
    printf("Can\'t wait for condition\n");
    exit(-1);
  }

  if (semop(semid, &buf_first, 1) < 0) {
    printf("Can\'t wait for condition\n");
    exit(-1);
  }

  if (is_new == 1) {
    res[0] = 1;
    res[1] = 0;
  } else {
    ++res[0];
  }
  printf("first\t res[0] = %d\t res[1] = %d\n", res[0], res[1]);

  for (int i = 0; i < 100; ++i) {
    if (semop(semid, &buf_second, 1) < 0) {
      printf("Can\'t wait for condition\n");
      exit(-1);
    }
    if (semop(semid, &buf_first, 1) < 0) {
      printf("Can\'t wait for condition\n");
      exit(-1);
    }
    ++res[0];
    printf("first\t res[0] = %d\t res[1] = %d\n", res[0], res[1]);
  }
  if (shmdt(res) < 0) {
    printf("Can't detach shared memory\n");
    exit(-1);
  }
  if (semctl(semid, 0, IPC_RMID, 0) < 0) {
    printf("Can't delete semafor\n It was deleted by second\n");
    exit(-1);
  }
  printf("first\t finish\n");
  
  return 0;
}