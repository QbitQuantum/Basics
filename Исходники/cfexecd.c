void StartServer(int argc,char **argv)

{ int pid,time_to_run = false;
  time_t now = time(NULL); 
#ifdef HAVE_PTHREAD_H
  pthread_t tid = 1;
#else
  int tid = -1
#endif

Banner("Starting server");
  
if ((!NO_FORK) && (fork() != 0))
   {
   snprintf(OUTPUT,CF_BUFSIZE*2,"cfexecd starting %.24s\n",ctime(&now));
   CfLog(cfinform,OUTPUT,"");
   exit(0);
   }

if (!ONCE)
   {
   if (!GetLock("cfexecd","execd",0,0,VUQNAME,now))
      {
      snprintf(OUTPUT,CF_BUFSIZE*2,"cfexecd: Couldn't get a lock -- exists or too soon: IfElapsed %d, ExpireAfter %d\n",0,0);
      CfLog(cfverbose,OUTPUT,"");
      return;
      }

   SaveExecLock(); 
   }
 
if (!NO_FORK)
  {
  ActAsDaemon(0);
  }

WritePID("cfexecd.pid");
signal(SIGINT,(void *)ExitCleanly);
signal(SIGTERM,(void *)ExitCleanly);
signal(SIGHUP,SIG_IGN);
signal(SIGPIPE,SIG_IGN);
signal(SIGUSR1,HandleSignal);
signal(SIGUSR2,HandleSignal);
 
umask(077);

if (ONCE)
   {
   GetCfStuff();
   LocalExec((void *)0);
   }
else
   { char **nargv;
     int i;

   /*
    * Append --once option to our arguments for spawned monitor process.
    */
     nargv = malloc(sizeof(char *) * (argc+2));
   
   for (i = 0; i < argc; i++)
      {
      nargv[i] = argv[i];
      }
   
   nargv[i++] = strdup("--once");
   nargv[i++] = NULL;
   
   GetCfStuff();
   
   while (true)
      {
      time_to_run = ScheduleRun();
      
      if (time_to_run)
         {
         if (!GetLock("cfd","exec",CF_EXEC_IFELAPSED,CF_EXEC_EXPIREAFTER,VUQNAME,time(NULL)))
            {
            snprintf(OUTPUT,CF_BUFSIZE*2,"cfexecd: Couldn't get exec lock -- exists or too soon: IfElapsed %d, ExpireAfter %d\n",CF_EXEC_IFELAPSED,CF_EXEC_EXPIREAFTER);
            CfLog(cfverbose,OUTPUT,"");
            continue;
            }
         
         GetCfStuff();
         
#ifdef NT 
         /*
          * Spawn a separate process - spawn will work if the cfexecd binary
          * has changed (where cygwin's fork() would fail).
          */
         
         Debug("Spawning %s\n", nargv[0]);

         pid = _spawnvp((int)_P_NOWAIT,nargv[0],nargv);

         if (pid < 1)
            {
            CfLog(cfinform,"Can't spawn run","spawnvp");
            }
#endif
#ifndef NT
#if (defined HAVE_LIBPTHREAD || defined BUILDTIN_GCC_THREAD)
         
         pthread_attr_init(&PTHREADDEFAULTS);
         pthread_attr_setdetachstate(&PTHREADDEFAULTS,PTHREAD_CREATE_DETACHED);
         
#ifdef HAVE_PTHREAD_ATTR_SETSTACKSIZE
         pthread_attr_setstacksize(&PTHREADDEFAULTS,(size_t)2048*1024);
#endif
         
         if (pthread_create(&tid,&PTHREADDEFAULTS,LocalExec,(void *)1) != 0)
            {
            CfLog(cfinform,"Can't create thread!","pthread_create");
            LocalExec((void *)1);
            }
         
         pthread_attr_destroy(&PTHREADDEFAULTS);
#else
         LocalExec((void *)1);  
#endif
#endif
         
         ReleaseCurrentLock();
         }
      }
   }
}