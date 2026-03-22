
#include "cVersionControlSystem.h"

// creates the .vcs and versions folders to contain the versions of
// files for the system, use 0700 permisions so only user can access 
void init()
{
    // permissions set to 0700, so only user can access
    mkdir(".vcs", 0700);  // create vcs folder
    mkdir(".vcs/versions", 0700);  // create versions sub folder
}

// saves the file as a version in the versions folder
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

// replaces the current file with a selected version of the file
void checkout(const char* file, int ver)
{
    char verFilepath[300];    // stores the file path of the version

    // check if we can find file / it doesnt exist
    snprintf(verFilepath, sizeof(verFilepath), ".vcs/versions/%s_v%d", file, ver);

    if (access(verFilepath, F_OK) == -1)
    {
        printf("Cannot find file or it doesnt exist.\n");
        return;
    }

    // file in read
    FILE* newVerFile = fopen(verFilepath, "rb");
    if (!newVerFile)
    {
        // if cant find ver file
        printf("cannot open version file");
        return;
    }

    // open original file in write
    FILE* original = fopen(file, "wb");
    if (!original)
    {
        // if cant open
        printf("cannot open original file");
        fclose(newVerFile);
        return;
    }

    // buffer holds file data
    char byteBuffer[64000];
    size_t bytes; // how many bytes read

    // read from file, stops when bytes no longer being read (bytes = 0)
    while ((bytes = fread(byteBuffer, 1, sizeof(byteBuffer), newVerFile)) > 0)
    {
        // write to the file
        fwrite(byteBuffer, 1, bytes, original);
    }

    // close files
    fclose(newVerFile);
    fclose(original);
    
    printf("Replaced %s with version %d.\n", file, ver); // show that file is replaced with ver
}