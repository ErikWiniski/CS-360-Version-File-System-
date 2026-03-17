
#include "cVersionControlSystem.h"

// creates the .vcs and versions folders to contain the versions of
// files for the system, use 0700 permisions so only user can access 
void init()
{
    // permissions set to 0700, so only user can access
    mkdir(".vcs", 0700);  // create vcs folder
    mkdir(".vcs/versions", 0700);  // create versions sub folder
}