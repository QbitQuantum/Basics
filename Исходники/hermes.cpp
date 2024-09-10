int
#ifdef WIN32_SERVICE
hermes_main
#else
main
#endif //WIN32_SERVICE
(int argc,char *argv[])
{
  /* TODO:think of this again
  if(argc>2)
  {
    for(unsigned i=1;i<argc;i++)
    {
      argv++
  }
  */

  #ifdef HAVE_SSL
    CRYPTO_set_locking_callback(ssl_locking_function);
    #ifndef WIN32 //getpid() returns different values for threads on windows, therefor this is not needed
    CRYPTO_set_id_callback(pthread_self);
    #endif //WIN32
  #endif //HAVE_SSL
  try
  {
    if(2==argc)
    {
      if(!Utils::file_exists(argv[1]))
        throw Exception(string(_("Config file "))+argv[1]+_(" doesn't exist or is not readable."),__FILE__,__LINE__);
      cfg.parse(argv[1]);
    }
    else
      throw Exception(_("Config file not specified"), __FILE__, __LINE__);
    cfg.validateConfig();
  }
  catch(Exception &e)
  {
    LERR(e);
    return -1;
  }

  unsigned long nconns=0;

  signal(SIGTERM,exit_requested);
  signal(SIGINT,exit_requested);
  #ifndef WIN32
  signal(SIGCHLD,SIG_IGN);
  signal(SIGPIPE,SIG_IGN);
  #endif //WIN32

  //we have to create the server socket BEFORE chrooting, because if we don't,
  //SSL cannot initialize because it's missing libz
  ServerSocket server;
  pthread_t cleaner_thread;
  string peer_address;

  #ifndef WIN32
    if(cfg.getBackground())
    {
      int retval;

      retval=fork();
      if(retval>0)
        exit(0); //succesful fork

      if(retval<0)
      {
        LERR(_("Error forking into the background") + Utils::errnotostrerror(errno));
        return -1;
      }
    }
    
    if(cfg.getPidFile()!="")
    {
      try
      {
        Utils::write_pid(cfg.getPidFile(),getpid());
      }
      catch(Exception &e)
      {
        LERR(e);
      }
    }

    if(cfg.getChroot()!="")
    {
      //this is needed to get hermes to load the dns resolver BEFORE chrooting
      (void)gethostbyname("hermes-project.com");
      if(-1 == chdir(cfg.getChroot().c_str()))
      {
        LERR(_("Couldn't chdir into ") + cfg.getChroot() + " " + Utils::errnotostrerror(errno) );
        return -1;
      }
      if(-1==chroot(cfg.getChroot().c_str()))
      {
        LERR(_("Couldn't chroot ") + Utils::errnotostrerror(errno));
        return -1;
      }
      if(-1 == chdir("/"))
      {
        LERR(_("Couldn't chdir into /, this shouldn't happen: " + Utils::errnotostrerror(errno)) );
        return -1;
      }
    }
  #endif //WIN32

  LINF("Starting hermes with pid "+Utils::inttostr(getpid()));
  try
  {
    server.init();
    server.setPort(cfg.getListeningPort());
    server.listen(cfg.getListeningPort(),cfg.getBindTo());
  }
  catch(Exception &e)
  {
    LERR(e);
    return -1; //couldn't bind, exit
  }

  #ifndef WIN32
  if(cfg.getDropPrivileges())
  {
    //drop privileges once we have opened the listening port
    if(-1 == setgroups(0,NULL))
    {
      LERR(_("Error dropping priviledges " + Utils::errnotostrerror(errno)) );
      return -1;
    }
    if(-1 == setgid(cfg.getGid()))
    {
      LERR(_("Error setting gid " + Utils::inttostr(cfg.getGid()) + " " + Utils::errnotostrerror(errno)) );
      return -1;
    }
    if(-1 == setuid(cfg.getUid()))
    {
      LERR(_("Error setting uid " + Utils::inttostr(cfg.getUid()) + " " + Utils::errnotostrerror(errno)) );
      return -1;
    }
    if(-1 == setuid(cfg.getUid()))
    {
      LERR(_("Error setting uid " + Utils::inttostr(cfg.getUid()) + " " + Utils::errnotostrerror(errno)) );
      return -1;
    }
  }
  #endif //WIN32

  /* start our cleaner thread */
  if(cfg.getCleanDb())
    pthread_create(&cleaner_thread,NULL,cleaner_thread_run,NULL);

  new_conn_info info;
  stack<new_conn_info> info_stack;
  while(!quit)
  {
    if(server.canRead(1)) //wait one second for incoming connections, if none then loop again(allows us to check for SIGTERM and SIGINT)
    {
      pthread_t thread;
      pthread_attr_t thread_attr;
      pthread_attr_init(&thread_attr);
      pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

      int retval;
      int fd=server.accept(&peer_address);
      info.new_fd=fd;
      info.peer_address=peer_address;
      info.connection_id=++nconns;
      pthread_mutex_lock(&info_stack_mutex);
      info_stack.push(info);
      pthread_mutex_unlock(&info_stack_mutex);
      retval=pthread_create(&thread,&thread_attr,thread_main,(void *)&info_stack);
      if(retval)
      {
        LERR(_("Error creating thread: ") + Utils::errnotostrerror(retval) + _(". Sleeping 5 seconds before continuing..."));
        sleep(5);
      }
      else
      {
        #ifdef WIN32
        LDEB("New thread created [" + Utils::ulongtostr(nconns) + "] thread_id: " + Utils::ulongtostr((unsigned long)thread.p) + ":" + Utils::ulongtostr(thread.x));
        #else
        LDEB("New thread created [" + Utils::ulongtostr(nconns) + "] thread_id: " + Utils::ulongtostr(thread));
        #endif //WIN32
        pthread_mutex_lock(&childrenlist_mutex);
        children.push_back(nconns);
        pthread_mutex_unlock(&childrenlist_mutex);
      }
    }
  }

  //close connection so that the port is no longer usable
  server.close();

  // wait for all threads to finish
  LINF("Waiting for threads to finish");
  #ifndef WIN32
  while(children.size())
  {
    if(false==cfg.getBackground())
    {
      cout << "Threads active:" << children.size() << (char)13;
      fflush(stdout);
    }
    sleep(1);
  }
  #endif //WIN32
  if(cfg.getCleanDb())
    pthread_join(cleaner_thread,NULL);

  #ifndef WIN32
  if(false==cfg.getBackground())
    cout << endl;
  #endif //WIN32

  #ifdef HAVE_SPF
  Spf::deinitialize();
  #endif //HAVE_SPF
  return 0;
}