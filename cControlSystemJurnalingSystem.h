#ifndef CCONTROLSYSTEMJURNALINGSYSTEM_H
#define CCONTROLSYSTEMJURNALINGSYSTEM_H

#include <sys/stat.h> // for mkdir
#include <sys/types.h>
#include <unistd.h> // for access
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <dirent.h>

// journaling system functions
void writeJournal(const char* file);
void recoverJournal();

#endif
