#ifndef CVERSIONCONTROLSYSTEM_H
#define CVERSIONCONTROLSYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h> // for mkdir
#include <unistd.h> // for access
#include <time.h> // for metadata

// function prototypes
void init();
static void internalwriteJournal(const char* file);
void commit(const char* file);
void checkout(const char* file, int ver);

// version logging
void fileLogs(const char* file);

#endif