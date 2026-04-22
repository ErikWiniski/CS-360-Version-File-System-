# CS-360-Version-File-System-
This system lets the user store multiple file versions as well as recover and revert changes beetween multiple versions. It features logs, journaling, metadata, read/write locks, and a vcs file structure to store the file versions.

Main goal: Create a working file version control system that can track, manage, and recover changes to file.

Sub goals:
* Design a structure data management system to organize and access file versions efficiently 
* Add control flow mechanism to manage file versions, making sure files are handled correctly 
* Add a journaling system
* Implement thread safety including read/write locks 
* Store file versions effectively

Themes: 
* file systems 		- creates vcs file system for a file structure.
* system level I/O		- reads and writes file data with low level operations.
* memory systems		- use short term memory systems to store data for transfering.
* control flow 		- manage user commands, go through file versions, and handle recovery.

Design
* User space control version control system in C
* Uses system-level I/O
* Metadata used for tracking file versions
* Journaling for crash recovery, going back to an old version, and editing.
* Thread safety using read/write locks to prevent concurrent writing while allowing the file to be read.

Trade Offs:
* Journaling - leads to more writes but ensure crashes are safe.
* Simple architecture - reliable functionality and easier debugging but may not have as many features like merging.
* FUSE interface - We had to focus on the core system and due to time constraints we decided not to focus on implementing it

Challenges Encountered:
* File path errors and incorrect file locations
* Debugging system calls like fopen, mkdir, stat
* Handling invalid user inputs, and crashes
* Redesign our part of the code and journaling system to properly compile and operate correctly

Lessons Learned:
* Gain greater understanding on version control system 
- Creating directories using mkdir
- Checking for file existence with stat and access
- Organizing file into structured folder, and also tracking and restoring changes
* Learning systems maintain data integrity
- How system detect incomplete operations
- How crashes can corrupt data
- How journaling prevents inconsistency
- Logged operations like START_COMMIT, END_COMMIT are example of it


run:
gcc main.c cVersionControlSystem.c cControlSystemJurnalingSystem.c cLockSystem.c -o vcs

commands:
* ./vcs init
* ./vcs commit (FILENAME)
* ./vcs checkout (FILENAME) (version number)
* ./vcs log (FILENAME)

* ./vcs init should create a .vcs file and inside should create two file holder
    - Verisons: holds the different versions of the same file when a new version
    - journal.log: hold the start and end of commit when is complete storing the file verisons
