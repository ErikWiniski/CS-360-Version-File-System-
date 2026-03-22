
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

    // check to see if command called is commit
    else if (strcmp(argv[1], "commit") == 0)
    {
       if (argc < 3) // need 3 arguments
       {
            printf("ERROR: not enough arguments");
            return 1;
       }

       // call commit with the filename
       commit(argv[2]);
    }

    // check to see if command called is log
    else if (strcmp(argv[1], "log") == 0)
    {
        if (argc < 3) // need 3 arguments
        {
            printf("ERROR: not enough arguments\n");
            return 1;
        }

        // get versions of a given file using its name and show them
        fileLogs(argv[2]);
    }

    return 0;
}