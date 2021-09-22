/*
 * Filename:            pidHandler.c
 * Date:                05/04/2021
 * Author:              Preston Glenn
 * Email:               Preston.Glenn@utdallas.edu
 * Version:             1.0
 * Copyright:           2021, All Rights Reserved
 *
 * Description:
 *      This file provides the functions in order to handle the pid file.
 *
 */


#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


// Returns true if file pid file exits
bool checkPID(){

  ifstream file("cs3377dirmond.pid");
  
  if(file.is_open()){
    //log file exists
    file.close();
    return true;
  }
  return false;

}

// Returns true if file is removed successfully
bool removePID(){

  int status = remove("cs3377dirmond.pid");
  // log file removed correctly or not
  return status;

}


// Function to return pid and create file to store it in.
long createPID(){
  long pid = (long)getpid();

  ofstream file("cs3377dirmond.pid");
  if(file.is_open()){ // file opened correctly
    file << pid <<endl;
    file.close();
    return pid;
  }

  cerr << "Unable to open PID file\n";
  cerr << "Terminating Program." << endl;
  exit(1);
  return 0;
}
