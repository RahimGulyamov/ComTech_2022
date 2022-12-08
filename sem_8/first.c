#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "struct.h"

int main() {
    Node* storage;
    int shmid;
    bool cond;
    char pathname[] = "first.c";
    key_t key;  // key_t == int
    
    key = ftok(pathname, 0);
    
    if (key == -1) {
        printf ("Can\'t generate key \n");
        exit(-1);
    }
    
    shmid = shmget(key, 10 * sizeof(Node), 0666|IPC_CREAT|IPC_EXCL);
    
    if (shmid == -1) {
        if (errno != EEXIST) {
            printf ("Can\'t crearte sharaed memory \n");
            exit(-1);
        } else {
            shmid = shmget(key, 10 * sizeof(Node), 0);
            if (shmid == -1) {
                printf ("Can\'t find shared memory\n");
                exit(-1);
            }
        }
    }
    storage = (Node*)shmat(shmid, NULL, 0);
    if (storage == (Node*)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    for (int i = 0; i < 10; ++i) {
        cond = (rand() % 2);
        if (cond) {
            
        }
    }
    

    return 0;
}