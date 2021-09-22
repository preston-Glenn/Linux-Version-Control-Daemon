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


## Usage

```

./dirmond [-d] [--] [--version] [-h] <config filename>

Where:
-d, --daemon
	Run in daemon mode (forks to run as a daemon).

--, --ignore_rest
	Ignores the rest of the labeled arguments following this flag.

--version
	Displays version information and exits.

-h, --help
	Displays usage information and exits.

<config filename>
	The name of the configuration file. Defaults to cs3377dirmond.conf
 
 dirmond Directory Monitor Daemon
 ```
## Dependencies
You'll need to edit the makefile to refelct where you installed these dependencies.
- rudeconfig 
- tclap 

## Additional Functionality
This program can be run as a daemon by adding the '-d' flag otherwise it runs as a foreground process.

When running the executable use the -v flag to indicaate verbose. The main purpose of verbose is that it causes the program to log additional info. The main addition is that, when enabled the logger will indicate what file was changed, while when not enabled it will only indicate that a file was change.

In order to terminate the prgoram run "ps" to obtain the process id. Then run "kill -s SIGINT 'pid' "

The user can also use the command "kill -s SIGINT 'pid' " in order to tell the program to updated its setting from the conf. file.
The program will only update the NumVersions, Verbose, and the LogFile. It will not update the Paswword or watchDir.



