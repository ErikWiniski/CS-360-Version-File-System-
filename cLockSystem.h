#ifndef CTHREADSYSTEM_H
#define CTHREADSYSTEM_H

#include <pthread.h>

//global lock for all operations
extern pthread_rwlock_t global_rwlock;

void InitilizeLock();
void DestroyLock();

#endif