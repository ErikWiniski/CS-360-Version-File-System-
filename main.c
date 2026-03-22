
#include "cVersionControlSystem.h"

// Main
int main(int argc, char* argv[]) {

    // use switch statement?

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

    // check to see if command called is checkout
    else if (strcmp(argv[1], "checkout") == 0)
    {
       if (argc < 4) // need 4 arguments
       {
            printf("ERROR: not enough arguments");
            return 1;
       }

       // call checkout with the filename and version
       checkout(argv[2], atoi(argv[3]));
    }

    return 0;
}