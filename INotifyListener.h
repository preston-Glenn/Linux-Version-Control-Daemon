/*
 * Filename:            INotifyListener.h
 * Date:                05/07/2021
 * Author:              Preston Glenn
 * Email:               Preston.Glenn@utdallas.edu
 * Version:             1.0
 * Copyright:           2021, All Rights Reserved
 *
 * Description:
 *   Header file for INotifyListener class.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <iostream>
#include <limits.h>
#include <fstream>
#include <string>

using namespace std;


class INotifyListener{
 public:
  INotifyListener();
  ~INotifyListener();
  void Initialize(string w);
  bool changeDir(string watchDir);
  void close();


 private:
  int bufsize;
  struct inotify_event * event;
  int total_bytes_read;
  string watchDir;
  int fd;
  int wd;

};
