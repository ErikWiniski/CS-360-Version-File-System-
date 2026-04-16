# CS-360-Version-File-System-
run:
gcc main.c cVersionControlSystem.c cControlSystemJurnalingSystem.c cLockSystem.c -o vcs

commands:
./vcs init
./vcs commit (FILENAME)
./vcs checkout (FILENAME) (version number)
./vcs log (FILENAME)

./vcs init should create a .vcs file and inside should create two file holder
    -Verisons: holds the different versions of the same file when a new version
    -journal.log: hold the start and end of commit when is complete storing the file verisons
