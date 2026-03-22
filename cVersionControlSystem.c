
#include "cVersionControlSystem.h"

// makes it so the mkdir works on both windows and mac/linux systems
#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
#else
    #include <sys/stat.h>
    #include <sys/types.h>
    #define MKDIR(path) mkdir(path, 0700)
#endif

// creates the .vcs and versions folders to contain the versions of
// files for the system, use 0700 permisions so only user can access 
void init()
{
    // permissions set to 0700, so only user can access
    mkdir(".vcs");  // create vcs folder
    mkdir(".vcs/versions");  // create versions sub folder
}

void commit(const char* file)
{
    // check if we can find file / it doesnt exist
    if (access(file, F_OK) == -1)
    {
        printf("Cannot find file or it doesnt exist.\n");
        return;
    }

    // need to go check versions
    int ver = 1;    // version checking starts at 1
    char verFilepath[300];    // stores the file path of the version

    while(1)
    {
        // create filepath for each version to check
        snprintf(verFilepath, sizeof(verFilepath), ".vcs/versions/%s_v%d", file, ver);

        // check if next file ver exists
        if(access(verFilepath, F_OK) == -1)
        {
            break; // found next ver
        }

        ver++; // increment file
    }

    // open original file in read
    FILE* original = fopen(file, "rb");
    if (!original)
    {
        // if cant open
        printf("cannot open original file");
        return;
    }

    // create new file in write
    FILE* newVerFile = fopen(verFilepath, "wb");
    if (!newVerFile)
    {
        // if cant make new file
        printf("cannot create new version file");
        fclose(original);
        return;
    }

    // buffer holds file data
    char byteBuffer[64000];
    size_t bytes; // how many bytes read

    // read from file, stops when bytes no longer being read (bytes = 0)
    while ((bytes = fread(byteBuffer, 1, sizeof(byteBuffer), original)) > 0)
    {
        // write to the new ver file
        fwrite(byteBuffer, 1, bytes, newVerFile);
    }

    // close files
    fclose(original);
    fclose(newVerFile);

    printf("Committed.\n"); // show that file is commited
}

void fileLogs(const char* file)
{
    // check if we can find file / it doesnt exist
    char firstVer[300];
    snprintf(firstVer, sizeof(firstVer), ".vcs/versions/%s_v1", file);

    if (access(firstVer, F_OK) == -1)
    {
        printf("No versions found for the file: %s\n", file);
        return;
    }

    // need to go check versions
    int ver = 1;    // version checking starts at 1
    char verFilepath[300];    // stores the file path of the version

    // intro text before versions start getting printed
    printf("Version(s) for the file: %s\n\n", file);

    // loop that prints each version
    while(1)
    {
        snprintf(verFilepath, sizeof(verFilepath), ".vcs/versions/%s_v%d", file, ver);

        if (access(verFilepath, F_OK) == -1)
        {
            break;
        }
        printf("Version #%d\n", ver);
        ver++;
    }
}