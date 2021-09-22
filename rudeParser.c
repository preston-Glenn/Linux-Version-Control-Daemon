/*
 * Filename:            rudeParser.c
 * Date:                05/04/2021
 * Author:              Preston Glenn
 * Email:               Preston.Glenn@utdallas.edu
 * Version:             1.0
 * Copyright:           2021, All Rights Reserved
 *
 * Description:
 *    This file provides the main rudeConfig parsing functions in order to parse the conf file.
 *
 */


#include <sys/stat.h>
#include "LoggingHandler.h"
#include "program6.h"
#include <rude/config.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace rude;
using namespace std;

#include <iostream>

extern Logger logger;

config_struct parseConfig(const char * fileName){ // TODO Check if Parameter is missing
  Config config;
  config_struct obj;

  if(config.load(fileName)){
    



    config.setSection("Parameters",true);


    if(strcmp(config.getSectionNameAt(1),"Parameters")|| !config.exists("Verbose") || !config.exists("LogFile") || !config.exists("Password") || !config\
       .exists("NumVersions") || !config.exists("WatchDir"))
      {
	cerr << "CONFIG_HANDLER: Missing config property in config file.\n";
	cerr << "TERMINATING PROGRAM" << endl;
	removePID();
	exit(1);
      }


    obj.Verbose = config.getBoolValue("Verbose");
    obj.LogFile = config.getStringValue("LogFile");
    obj.Password= config.getStringValue("Password");
    obj.NumVersions=config.getIntValue("NumVersions");
    obj.WatchDir = config.getStringValue("WatchDir");
    
    struct stat buffer;
    struct stat buffer2;

    string versions = obj.WatchDir + "/.versions";

    if(stat (obj.WatchDir.c_str(), &buffer) != 0)
      {
	cerr <<  "Watch Directory does not exist. Terminating program.\n";
	cerr << "TERMINATING PROGRAM" << endl;

	removePID();
	exit(1);

      }


    if((stat (obj.WatchDir.c_str(), &buffer) == 0)&&(stat (versions.c_str(), &buffer2) != 0)){
      string st = commandLine("mkdir "+obj.WatchDir+"/.versions");


    }
    return obj;

  } else {


    cerr << "CONFIG_HANDLER ERROR: Unable to open file.\n";
    cerr << "TERMINATING PROGRAM" << endl;

    removePID();
    exit(1);
  }


}


config_struct parseConfigSignal(const char * fileName,config_struct prev){
  Config config;
  config_struct obj;

  if(config.load(fileName)){
    
    if(strcmp(config.getSectionNameAt(1),"Parameters")==0){
      config.setSection("Parameters",true);
    }

    if(strcmp(config.getSectionNameAt(1),"Parameters")|| !config.exists("Verbose") || !config.exists("LogFile") || !config.exists("Password") || !config.exists("NumVersions") || !config.exists("WatchDir"))
      {
        logger.log("CONFIG_HANDLER: Missing config property in config file.\n");
	cerr << "CONFIG_HANDLER: Missing config property in config file." << endl;
	removePID();
        
	cerr << "TERMINATING PROGRAM" << endl;
	exit(1);
      }


    obj.Verbose = config.getBoolValue("Verbose");
    obj.LogFile = config.getStringValue("LogFile");
    obj.Password = prev.Password;
    obj.NumVersions = config.getIntValue("NumVersions");
    obj.WatchDir = prev.WatchDir;

    struct stat buffer;


    // Not needed since WatchDir wont change.
    //if(stat (obj.WatchDir.c_str(), &buffer) != 0){
      //commandLine("mkdir "+obj.WatchDir+"/.versions");
      // if(logger.getVerbose())
	//	logger.log("RUDE_PARSER_HANDLER STATUS: Created new directory at "+ obj.WatchDir+"/.versions\n");

    //    }
    logger.setVerbose(obj.Verbose);
    return obj;

  } else {
    logger.log("CONFIG_HANDLER ERROR: Unable to open file.\n");
    cerr << "CONFIG_HANDLER ERROR: Unable to open file." << endl;
    cerr << "TERMINATING PROGRAM" << endl;
    removePID();
    exit(1);
  }


}
