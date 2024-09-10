int main(int argc, char *argv[])
{
 if(!init_cfg())
 {
  fprintf(stderr, "Unable to open config file or invalid content in config file.\n");
  exit(1);
 }
 
 parseopts(argc, argv, conf);

 if(conf->msg)
 {
  if(!open_producer())
  {
   printf("Unable to contact Bluemote server!\n");
   exit(1);
  }
  if(ipc_write(conf->device, strlen(conf->device))<=0)
  {
   printf("Unable to send message to Bluemote server!\n");
   close_producer();
   exit(1);
  }
  close_producer();
  exit(0);
 }
 else
 {
  if(!get_lock())
  {
   printf("Another instance of Bluemote already running!\n");
   exit(1);
  }

  if(!open_consumer())
  {
   printf("Unable to listen for messages!\n");
   exit(1);
  }
 }

 strcpy(logfile, getenv("HOME"));
 strcat(logfile, BLUEMOTEDIR);
 strcat(logfile, LOGFILE);

 printf("Setting up signal handlers.\n");
 logger("INIT", "Setting up signal handlers");
 if(!init_signals())
 {
  perror("init_signals()");
  exit(1);
 }

 if(conf->daemon)
 {
  printf("Entering daemon mode.\n");
  logger("INIT", "Entering daemon mode.\n");
  if(daemon(TRUE, FALSE)==-1)
  {
   printf("Unable to enter daemon mode. Exiting.\n");
   logger("ERROR", "Unable to enter daemon mode. Exiting.\n");
   exit(1);
  }
 }

 while(TRUE)
 {
  closeport();

  printf("Connecting to phone...\n");
  logger("INIT", "Connecting to phone...");
  while(openport(conf->device) == -1)
  {
   sprintf(buf,"Unable to connect to phone. Will retry after %d secs.",conf->retrysecs);
   logger("INIT", buf);
   sleep(conf->retrysecs);
   logger("INIT", "Retrying...");
  }
  printf("Connected to phone.\n");
  logger("INIT", "Connected to phone.");
  
  printf("Initialising the connection.\n");
  logger("INIT", "Initialising the connection.\n");
  if(!initport()) exit(1);

  printf("Waiting for commands from phone\n");
  logger("INIT", "Waiting for commands from phone\n");

  /* Not looping to take care of timeout because timeout is very unlikely and
   * this function is called again inside remote(). In the worst case, the I/O
   * commands for Connect event won't have any effect. */
  if(init_mainmenu()==-1) continue;

  exec_event("Connect");
  if(!manual)
  {
   exec_event("MoveIn");
  }
  manual = FALSE;
  remote();
  if(!manual)
  {
   exec_event("MoveOut");
  }
  exec_event("Disconnect");
 }
 return(0);
}