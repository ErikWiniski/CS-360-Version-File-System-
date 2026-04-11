
#include "cControlSystemJurnalingSystem.h"

void writeJournal(const char* file)
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


void recoverJournal()
{
    FILE* journal = fopen(".vcs/journal.log", "r");

    if(!journal)
    {
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
}