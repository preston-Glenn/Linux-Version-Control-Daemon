# Linux File System Daemon

## Objective
The goal of this program is to create a UNIX style daemon process that will watch a folder and 
respond to specific file operations that occur in that folder. The daemon process will read its 
configuration parameters from a CONFIG file and then operate according to that configuration. The 
daemon process will also respond to several UNIX signals that will help control its operation. 

Once operational, the daemon will act on any files written to the folder that it is observing. When it 
detects a write, the daemon will immediately create a copy of the just written file and store that copy 
in a .versions subfolder. Each copy stored in the .versions subfolder will have a date stamp 
appended to the filename.

## Build Executable
In order to create the executable simply untar the tar file, and run the "make" command. The executable is cs3377dirmond.

For help run ./cs3377dirmond -h

In order to run this program you will need the TCLAP header files as well as the rude library. In addition you will need to change the Makefile
preprocessor and compiler flags to point to the correct include and lib directories.

## Additional Functionality
This program can be run as a daemon by adding the '-d' flag otherwise it runs as a foreground process.

When running the executable use the -v flag to indicaate verbose. The main purpose of verbose is that it causes the program to log additional info. The main addition is that, when enabled the logger will indicate what file was changed, while when not enabled it will only indicate that a file was change.

In order to terminate the prgoram run "ps" to obtain the process id. Then run "kill -s SIGINT 'pid' "

The user can also use the command "kill -s SIGINT 'pid' " in order to tell the program to updated its setting from the conf. file.
The program will only update the NumVersions, Verbose, and the LogFile. It will not update the Paswword or watchDir.



