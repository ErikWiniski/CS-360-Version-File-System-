
#include "cVersionControlSystem.h"
#include "cControlSystemJurnalingSystem.h"
#include "cLockSystem.h"

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
//<<<<<<< HEAD
    // permissions set to 0700, so only user can access
    MKDIR(".vcs");  // create vcs folder
    MKDIR(".vcs/versions");  // create versions sub folder

    // create metadata file if it doesnt exist
    FILE* metaFile = fopen(".vcs/metadata.txt", "a");
    if (metaFile) // if file opened close it
    {
        fclose(metaFile);
    }
//=======
    if (MKDIR(".vcs") == -1)
    {
        printf("Warning: .vcs may already exist\n");
    }

    if (MKDIR(".vcs/versions") == -1)
    {
        printf("Warning: versions folder may already exist\n");
    }

    FILE* journal = fopen(".vcs/journal.log", "w");

    if(!journal)
    {
        printf("Failed to create journal file.\n");
        return;
    }

    fclose(journal);

    printf("Repository initialized.\n");
//>>>>>>> 1a4ee87 (4/10/26)
}

//this function is needed so that commit does not double lock when writeJournal() from the other file is called
static void internalWriteJournal(const char* file)
{
    // construct journal file path
    struct stat st = {0};   

    if (stat(".vcs", &st) == -1)
    {
        printf("ERROR: .vcs directory not found. Run init first.\n");
        return;
    }
    // open journal file in write
    FILE* journalFile = fopen(".vcs/journal.log", "a");
    if (!journalFile)
    {
        perror("cannot open journal file");
        return;
    }

    // write some data to the journal file (for example, the filename)
    fprintf(journalFile, "Journal entry for file: %s\n", file);

    // close journal file
    fclose(journalFile);
}

// saves the file as a version in the versions folder
void commit(const char* file)
{
    //lock writing for this file so no other threads/terminals can write to it at the same time
    pthread_rwlock_wrlock(&global_rwlock);

    // check if we can find file / it doesnt exist
    if (access(file, F_OK) == -1)
    {
        printf("Cannot find file or it doesnt exist.\n");
        //unlock early
        pthread_rwlock_unlock(&global_rwlock);
        return;
    }

    char journalFilepath[200];
    snprintf(journalFilepath, sizeof(journalFilepath), "START_COMMIT: %s", file);
    internalWriteJournal(journalFilepath); // write to journal before commiting


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
        //unlock early
        pthread_rwlock_unlock(&global_rwlock);
        return;
    }

    // create new file in write
    FILE* newVerFile = fopen(verFilepath, "wb");
    if (!newVerFile)
    {
        // if cant make new file
        printf("cannot create new version file");
        fclose(original);
        //unlock early
        pthread_rwlock_unlock(&global_rwlock);
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

//<<<<<<< HEAD
    // add to metadata
    FILE* metaFile = fopen(".vcs/metadata.txt", "a");
    if (metaFile) // check if open
    {
        // get current time
        time_t ct = time(NULL);
        char* currentTime = ctime(&ct);

        // print metadata into file
        fprintf(metaFile, "%s v%d %s", file, ver, currentTime);
        fclose(metaFile); // close file
    }

    printf("Committed.\n"); // show that file is commited
//=======
    snprintf(journalFilepath, sizeof(journalFilepath), "END_COMMIT: %s", file);
    internalWriteJournal(journalFilepath); // write to journal after commiting

    printf("Committed version %d of %s.\n", ver, file); // show that file is commited
//>>>>>>> 1a4ee87 (4/10/26)

    //unlock write functionality
    pthread_rwlock_unlock(&global_rwlock);
}

// replaces the current file with a selected version of the file
void checkout(const char* file, int ver)
{
    //lock writing for this file so no other threads/terminals can write to it at the same time
    pthread_rwlock_wrlock(&global_rwlock);

    char verFilepath[300];    // stores the file path of the version

    // check if we can find file / it doesnt exist
    snprintf(verFilepath, sizeof(verFilepath), ".vcs/versions/%s_v%d", file, ver);

    if (access(verFilepath, F_OK) == -1)
    {
        printf("Cannot find file or it doesnt exist.\n");
        //unlock early
        pthread_rwlock_unlock(&global_rwlock);
        return;
    }

    // file in read
    FILE* newVerFile = fopen(verFilepath, "rb");
    if (!newVerFile)
    {
        // if cant find ver file
        printf("cannot open version file");
        //unlock early
        pthread_rwlock_unlock(&global_rwlock);
        return;
    }

    // open original file in write
    FILE* original = fopen(file, "wb");
    if (!original)
    {
        // if cant open
        printf("cannot open original file");
        fclose(newVerFile);
        //unlock early
        pthread_rwlock_unlock(&global_rwlock);
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

    //unlock write functionality
    pthread_rwlock_unlock(&global_rwlock);
}

void fileLogs(const char* file)
{
    //lock for reading
    pthread_rwlock_rdlock(&global_rwlock);

    // check if we can find file / it doesnt exist
    char firstVer[300];
    snprintf(firstVer, sizeof(firstVer), ".vcs/versions/%s_v1", file);

    if (access(firstVer, F_OK) == -1)
    {
        printf("No versions found for the file: %s\n", file);
        //unlock early
        pthread_rwlock_unlock(&global_rwlock);
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
    //unlock read lock
    pthread_rwlock_unlock(&global_rwlock);
}