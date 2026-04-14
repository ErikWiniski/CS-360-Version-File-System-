
#include "cControlSystemJurnalingSystem.h"
#include "cLockSystem.h"

void writeJournal(const char* file)
{
    //lock writing for this file so no other threads/terminals can write to it at the same time
    pthread_rwlock_wrlock(&global_rwlock);

    // construct journal file path
    struct stat st = {0};   

    if (stat(".vcs", &st) == -1)
    {
        printf("ERROR: .vcs directory not found. Run init first.\n");
        //unlock early
        pthread_rwlock_unlock(&global_rwlock);
        return;
    }
    // open journal file in write
    FILE* journalFile = fopen(".vcs/journal.log", "a");
    if (!journalFile)
    {
        perror("cannot open journal file");
        //unlock early
        pthread_rwlock_unlock(&global_rwlock);
        return;
    }

    // write some data to the journal file (for example, the filename)
    fprintf(journalFile, "Journal entry for file: %s\n", file);

    // close journal file
    fclose(journalFile);

    //unlock write functionality
    pthread_rwlock_unlock(&global_rwlock);
}


void recoverJournal()
{
    //lock for reading
    pthread_rwlock_rdlock(&global_rwlock);

    FILE* journal = fopen(".vcs/journal.log", "r");

    if(!journal)
    {
        //unlock early
        pthread_rwlock_unlock(&global_rwlock);
        return;
    }
    char line[256];
    int openCommits = 0;

    while(fgets(line, sizeof(line), journal))
    {
        if(strstr(line, "START_COMMIT"))
        {
            openCommits++;
        }
        else if(strstr(line, "END_COMMIT"))
        {
            openCommits--;
        }
    }

    fclose(journal);

    if(openCommits > 0)
    {
        printf("Recovery: unfinished commit detected.\n");
    }

    //unlock read lock
    pthread_rwlock_unlock(&global_rwlock);
}