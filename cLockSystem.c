#include "cLockSystem.h"
#include <stdio.h>

pthread_rwlock_t global_rwlock = PTHREAD_RWLOCK_INITIALIZER;

void InitilizeLock() {
    if (pthread_rwlock_init(&global_rwlock, NULL) != 0) {
        printf("ERROR: failed to initilize lock\n");
    }
}

void DestroyLock() {
    pthread_rwlock_destroy(&global_rwlock);
}