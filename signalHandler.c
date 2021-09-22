/*
 * Filename:            signalHandler.c
 * Date:                05/04/2021
 * Author:              Preston Glenn
 * Email:               Preston.Glenn@utdallas.edu
 * Version:             1.0
 * Copyright:           2021, All Rights Reserved
 *
 * Description:
 *    This is the signal_handler function that is registered with the signals that the program is waiting for.
 *
 */



#include <sstream>
#include <map>
#include <stdlib.h>
#include <csignal>
#include <iostream>
#include "program6.h"
#include "LoggingHandler.h"
#include "INotifyListener.h"



using namespace std;

extern  config_struct configFileObj;
extern map<int,string> valueMap;
extern Logger logger;
extern INotifyListener listener;

void signal_handler( int signalnum ) {
  
  stringstream stream;
  stream << signalnum;
  string str = stream.str();


  if(signalnum == SIGINT || signalnum == SIGTERM)
    { // log removing PID and closing program log which sig was sent   

      logger.log("SIGNAL_HANDLER STATUS: SIGINT signal received. Terminating Program.\n");
      removePID();
      exit(signalnum);

    } else if( signalnum == SIGHUP){ // log sighup received updating files
    string prev_log = configFileObj.LogFile;
    logger.log("SIGNAL_HANDLER STATUS: SIGHUP signal received. Reevaluating CONF file.\n");
    configFileObj = parseConfigSignal(valueMap[CONFIG].c_str(),configFileObj);
    
    cout << configFileObj.LogFile << endl;
    if(prev_log != configFileObj.LogFile){
      logger.log("SIGNAL_HANDLER STATUS: Received new log location for logs. Closing current log file.\n");
      logger.log("SIGNAL_HANDLER STATUS: New file is: "+configFileObj.LogFile+"\n");
      logger.setFileName(configFileObj.LogFile);
      logger.log("\n\nSIGNAL_HANDLER STATUS: Beggining of new Log file\n");

    }

  }




 
}
