#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LAST_MESSAGE 255

int main() {
  int msqid;
  int semid;
  char pathname[] = "main.c";
  key_t key;
  int i, len;

  struct sembuf sembuf;

  struct mymsgbuf {
    long mtype;
    char mtext[81];
  } mybuf;

  if ((key = ftok(pathname, 0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  int pid_from_fork = fork();

  if (pid_from_fork == -1) {
    exit(127);
  }

  else if (pid_from_fork == 0) {
    int maxlen;

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
      printf("Child:\tCan\'t get msqid\n");
      exit(-1);
    }

    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
      printf("Child:\tCan\'t get semid\n");
      exit(-1);
    }

    sembuf.sem_op = 1;
    sembuf.sem_flg = 0;
    sembuf.sem_num = 0;

    while (1) {
      maxlen = 81;
      if (len = msgrcv(msqid, (struct msgbuf *)&mybuf, maxlen, 0, 0) < 0) {
        printf("Child:\tCan\'t receive message from queue\n");
        exit(-1);
      }
      if (mybuf.mtype == LAST_MESSAGE) {
        msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
        exit(0);
      }
      printf("message type = %ld, info = %s\n", mybuf.mtype, mybuf.mtext);
      if (semop(semid, &sembuf, 1) < 0) {
        printf("Child:\tCan\'t wait for condition\n");
        exit(-1);
      }
      // printf("Condition is set\n");
    }
    if (semctl(semid, 0, IPC_RMID, 0) == -1) {
      printf("Child:\tCan\'t delete sem\n");
      exit(5);
    } else {
      printf("Child:\tSem has been deleted\n");
    }
  }

  else {
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
      printf("Parent:\tCan\'t get msqid\n");
      exit(-1);
    }

    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
      printf("Parent:\tCan\'t get semid\n");
      exit(-1);
    }

    sembuf.sem_op = -1;
    sembuf.sem_flg = 0;
    sembuf.sem_num = 0;

    for (i = 1; i <= 5; i++) {
      mybuf.mtype = 1;
      if (i > 1) {
        if (semop(semid, &sembuf, 1) < 0) {
          printf("Parent:\tCan\'t wait for condition\n");
          exit(-1);
        }
      }
      printf("Input message:\t");
      fgets(mybuf.mtext, 81, stdin);
      len = strlen(mybuf.mtext) + 1;
      if (msgsnd(msqid, (struct msbuf *)&mybuf, len, 0) < 0) {
        printf("Parent:\tCan\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
        exit(-1);
      } else {
        printf("Parent:\tThe message has been sent\n");
      }
    }

    mybuf.mtype = LAST_MESSAGE;
    len = 0;
    if (semop(semid, &sembuf, 1) < 0) {
      printf("Parent:\tCan\'t wait for condition\n");
      exit(-1);
    }
    if (msgsnd(msqid, (struct msgbuf *)&mybuf, len, 0) < 0) {
      printf("Parent:\tCan\'t send message to queue\n");
      msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
      exit(-1);
    }

    if (semctl(semid, 0, IPC_RMID, 0) == -1) {
      printf("Parent:\tCan\'t delete sem\n");
      exit(5);
    } else {
      printf("Parent:\tSem has been deleted\n");
    }
  }
  return 0;
}