# Linux File System Daemon

## Objective

## Build Executable
In order to create the executable simply untar the tar file, and run the "make" command. The executable is cs3377dirmond.
In order to terminate the prgoram run "ps" to obtain the process id. Then run "kill -s SIGINT 'pid' "
The user can also use the command "kill -s SIGINT 'pid' " in order to tell the program to updated its setting from the conf. file.

The program will only update the NumVersions, Verbose, and the LogFile. It will not update the Paswword or watchDir.

## Functionality


This program can be run as a daemon by adding the '-d' flag otherwise it runs as a foreground process.


The main purpose of verbose is that it causes the program to log additional info. The main addition is that, when enabled the logger will indicate what file was changed, while when not enabled it will only indicate that a file was change.




In order to run this program you will need the TCLAP header files as well as the rude library. In addition you will need to change the Makefile
preprocessor and compiler flags to point to the correct include and lib directories.