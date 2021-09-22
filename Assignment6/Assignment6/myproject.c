/*
 * Filename:		myproject.c
 * Date:		05/07/2021
 * Author:		Preston Glenn
 * Email:		Preston.Glenn@utdallas.edu
 * Version:		1.0
 * Copyright:		2021, All Rights Reserved
 *
 * Description:
 *    This file serves as the main function to the project. It calls all the various handlers in order to run the program correctly
 *
 */


// This code was originally in the bison-parse example program and modified to fit my needs.
#include <iostream>
#include <map>
#include <fstream>
#include <tclap/CmdLine.h>
#include <cctype>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <csignal>
#include <iostream>

#include "program6.h"
#include "LoggingHandler.h"
#include "INotifyListener.h"

using namespace std;
using namespace TCLAP;

// Global Variables to be used in signal handler
config_struct configFileObj;
map<int,string> valueMap;
Logger logger;
INotifyListener listener;

int main(int argc, char *argv[]){

  // initialize variables
  signal(SIGTERM, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGHUP, signal_handler);
  stringstream int_stream;
  string str;


  // create cmdLine
  CmdLine cmd("cs3377dirmond Directory Monitor Daemon",' ',"1.0");


  // TCLAP WORK-----------------------------------------------------------------------------------------------------
  // create SwitchArgs
  SwitchArg daemon("d","daemon","Run program as daemon",cmd,false);

  // Create unlabeledValueArg
  UnlabeledValueArg<string> configArg("Config-File-Name","The config file name", false,"cs3377dirmond.conf","config file name", false);

  //Add ValueArgs and UnlabeledValueArgs
  cmd.add(configArg);

  cmd.parse(argc,argv);

  valueMap[DAEMON] = booleanToString(daemon.getValue());
  valueMap[CONFIG] = configArg.getValue();

  if(configFileObj.Verbose)
    cout << "MAIN_HANDLER STATUS: Command Line parsed"<<endl;
  // END OF TCLAP WORK---------------------------------------------------------------------------------------------


  // RUDE CONFIG SETUP--------------------------------------------------------------------------------------------

  configFileObj = parseConfig(valueMap[CONFIG].c_str());
  // END OF RUDE CONFIG SETUP---------------------------------------------------------------------------------------------




  // LOGGER SETUP ---------------------------------------------------------------------------------------------

  logger.setFileName(configFileObj.LogFile);
  logger.log("MAIN_HANDLER STATUS: Logfile started.\n");
  logger.setVerbose(configFileObj.Verbose);
  logger.log("\n\n\n");
  if(configFileObj.Verbose){
    int_stream << configFileObj.LogFile;
    logger.log("MAIN_HANDLER STATUS: Logfile created at: " + int_stream.str()+"\n");
  }
  // END OF LOGGER SETUP---------------------------------------------------------------------------------------------





  // PID and DAEMON SETUP---------------------------------------------------------------------------------------------


  // Check if a different DAEMON is currently running

  if(checkPID()){
    // Log process is already runnin
    cerr << "MAIN _HANDLER ERROR: PROCESS is already open, shutting down newest process.\n";
    return 0;
  }


  // CHECK IF DAEMON Flag is set 
  /* If so then we want to fork and then kill original process
  */

  if(stringToBoolean(valueMap[DAEMON])){
    long temp_pid = getpid();
    int status = fork();
    
    if(status == -1) { // Error
      //log error
      cerr << "MAIN_HANDLER ERROR: Fork did not fork correctly."<<endl;
      logger.log("MAIN_HANDLER ERROR: Fork did not fork correctly.\n");
      cerr << "TERMINATING PROGRAM" << endl;

      return 1;

    } else if ( status == 0) {//child
      logger.log("MAIN_HANDLER STATUS: Program called as Daemon\n");

    } else{ //parent
      int_stream.str("");
      int_stream << status;
      string str = int_stream.str();
      
      if(configFileObj.Verbose) logger.log("MAIN_HANDLER DATA: Child's PID code: "+str+"\n");
      int_stream.str("");
      //log on verbose pid and closing parent
      return 0;
    }
  }
  long pid = createPID();
  int_stream.str("");
  int_stream << pid;
  str = int_stream.str();
  // END OF DAEMON AND PID SETUP---------------------------------------------------------------------------------------------


  // LOGGING CONFIGURATION PROPERTIES----------------------------------------------------------------------------------------

  if(configFileObj.Verbose){
    logger.log("MAIN_HANDLER STATUS: PID File Created: "+str+"\n");
  }
  
  logger.log("MAIN_HANDLER STATUS: Config files added.\n");

  if(configFileObj.Verbose){
    int_stream.str("");    
    int_stream << configFileObj.NumVersions;
    str = int_stream.str();

    logger.log("MAIN_HANDLER: Config File Properties------\n");
    logger.log("\tVerbose: ");
    logger.log(booleanToString(configFileObj.Verbose));
    logger.log("\n\tLogfile: ");
    logger.log(configFileObj.LogFile);
    logger.log("\n\tPassword: ");
    logger.log(configFileObj.Password);
    logger.log("\n\tNumVersions: ");
    logger.log(str);
    logger.log("\n\tWatchDir: ");
    logger.log(configFileObj.WatchDir);
    logger.log("\n");
  }


  // START I NOTIFY LISTENER

  // This is the main function of the program. 
  // This function calls while(1) so it loops forever, unless it calls break();
  listener.Initialize(configFileObj.WatchDir);
  

 
  removePID();
  return 0;
}
