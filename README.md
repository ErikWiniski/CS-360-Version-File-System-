# CS-360-Version-File-System-
This system lets the user store multiple file versions as well as recover and revert changes beetween multiple versions. It features logs, journaling, metadata, read/write locks, and a vcs file structure to store the file versions.

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
