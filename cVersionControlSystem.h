#ifndef CVERSIONCONTROLSYSTEM_H
#define CVERSIONCONTROLSYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h> // for mkdir
#include <unistd.h> // for access

// function prototypes
void init();
void commit(const char* file);
void checkout(const char* file, int ver);


#endif