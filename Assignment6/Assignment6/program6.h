/*
 * Filename:            program6.h
 * Date:                05/07/2021
 * Author:              Preston Glenn
 * Email:               Preston.Glenn@utdallas.edu
 * Version:             1.0
 * Copyright:           2021, All Rights Reserved
 *
 * Description:
 *   This is the header file for all the main non-class handler files.
 *
 */


#include <string>

using namespace std;
struct config_struct{
  string LogFile;
  bool Verbose;
  string Password;
  int NumVersions;
  string WatchDir;
};


config_struct parseConfig(const char * fileName);
config_struct parseConfigSignal(const char * fileName,config_struct prev);


enum tclapValues{DAEMON,CONFIG};

void signal_handler( int signalnum );

long createPID();

bool removePID();

bool checkPID();

string commandLine(string a);


string booleanToString(bool val);
bool stringToBoolean(string val);
