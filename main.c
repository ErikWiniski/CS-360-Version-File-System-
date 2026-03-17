
#include "cVersionControlSystem.h"

// Main
int main(int argc, char* argv[]) {

    // check if arguments is less than 2, we need at least two
    if(argc < 2)
    {
        printf("ERROR: not enough arguments");
        return 1; // terminate program
    }


    // check to see if command called is init
    if (strcmp(argv[1], "init") == 0)
    {
        init(); // call init to create vcs and versions folders
    }


    return 0;
}