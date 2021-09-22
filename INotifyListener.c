/*
 * Filename:            INotifyListener.c
 * Date:                05/07/2021
 * Author:              Preston Glenn
 * Email:               Preston.Glenn@utdallas.edu
 * Version:             1.0
 * Copyright:           2021, All Rights Reserved
 *
 * Description:
 *    This is the inotifyhandler class file. It initializes in the constructor and then calls an infinite loop in the function Initialize, where it  
 * waits for a notification from inotify.
 */


#include "LoggingHandler.h"
#include "INotifyListener.h"
#include "program6.h"
#include <string>
#include <map>



using namespace std;


extern map<int,string> valueMap;
extern Logger logger;

INotifyListener::INotifyListener(){

  bufsize = sizeof(struct inotify_event)+NAME_MAX + 1;
  struct inotify_event *event = (struct inotify_event *) malloc(bufsize);   
}

INotifyListener::~INotifyListener(){
  inotify_rm_watch(fd,wd);
}


void INotifyListener::Initialize(string newDir){
  watchDir = newDir;

  fd = inotify_init();
  wd = inotify_add_watch(fd,newDir.c_str(),IN_CLOSE_WRITE|IN_CREATE|IN_MODIFY); 


  while(1){

    int count = 0;
    char buffer[bufsize*3];
    int bytes_read = 0;


    int temp_size = bufsize;
    char * temp_buffer = buffer;
   
    do{
      bytes_read = read(fd,temp_buffer,temp_size);
      
      if(bytes_read  < 0 && errno != EINTR){
        logger.log("I_NOTIFY_LISTENER STATUS: ERROR IN READ\n");
        break;
	//ERROR
      }

      if(errno == EINTR) // If signal flag, then we redo the read otherwise if read bytes is less than min size we redo
	continue;
      temp_size -= bytes_read;
      temp_buffer += bytes_read;

    }while((errno == EINTR)|| bytes_read < (sizeof(struct inotify_event)+2)); // while the number of bytes read is less than the minimum number of bytes
    // per event read more from the buffer


    // We need this loop in case more than one event were written to the buffer. The number of bytes read to the buffer is returned in bytes and the size each event is the len of the event->name plus the size of the constant size of the struct.
    while(count < bytes_read){
     
      event = (struct inotify_event*) &buffer[count];
      count += sizeof(struct inotify_event) + event->len;
      
      string event_name = event->name;

      string first_chars = event_name.substr(0,2);
      if( first_chars == ".#")
	continue;


      string date_instr = "date +.%Y.%m.%d-%H:%M:%S";

      //gets current date and time
      string date = commandLine(date_instr);
      date = event->name+date;


      string instr = "cp " + watchDir + "/" + event->name + " " + watchDir + "/.versions/" + date;
      string res =  commandLine(instr);
      

      if(logger.getVerbose())
	{
	  string str = "I_NOTIFY_LISTENER STATUS: "+ watchDir + "/" + event->name + " was copied to " + watchDir + "/.versions/" + date; 
	  logger.log(str);
	} else {
	  logger.log("I_NOTIFY_LISTENER STATUS: A file has been changed. Saving it to .versions\n");
      }
    }
  }
}
// closes the current watch directories
void INotifyListener::close(){
  inotify_rm_watch(fd,wd);
}


// changes watch directory:: not used in current code.
bool INotifyListener::changeDir(string newDir){
  watchDir = newDir;
  inotify_rm_watch(fd,wd);
  wd = inotify_add_watch(fd,newDir.c_str(),IN_CLOSE_WRITE|IN_CREATE|IN_MODIFY|IN_DELETE);
  return wd != -1;
}

