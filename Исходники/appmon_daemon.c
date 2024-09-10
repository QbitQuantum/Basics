int main(int argc, char** argv)
{
  char *buffer = NULL;
  int portno = 0, stop, optval;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
  struct sigaction action_CHLD;
  struct sigaction action_ALRM;

  /* Preliminary signal configuration:
   * SIGCHLD and SIGALRM are used with different handler
   * configure each handler to mask the other signal during it's process
   * Note: within a handler called upon a signal SIGX, the SIGX signal is
   * automatically de-activated.
   */

  sigemptyset(&block_sigs);
  sigaddset(&block_sigs, SIGCHLD);
  sigaddset(&block_sigs, SIGALRM);

  action_CHLD.sa_flags = SA_RESTART;
  action_CHLD.sa_handler = SIGCHLD_handler;
  sigemptyset(&(action_CHLD.sa_mask));
  sigaddset(&(action_CHLD.sa_mask), SIGALRM);

  action_ALRM.sa_flags = SA_RESTART;
  action_ALRM.sa_handler = SIGALRM_handler;
  sigemptyset(&(action_ALRM.sa_mask));
  sigaddset(&(action_ALRM.sa_mask), SIGCHLD);

  PointerList_Create(&apps, 0);
  if (NULL == apps)
    err_exit("PointerList_Create");

  /* Command line arguments Parsing
   * Options
   * a : privileged app path
   * w : privileged app working directory
   * v : user id to use to start privileged app
   * h : group id to use to start privileged app
   * p : TCP port to receive commands
   * u : user id to use to start regular apps
   * g : group id to use to start regular apps
   * n : nice value (process priority) for regular apps
   */
  char* init_app = NULL;
  char* init_app_wd = NULL;
  app_t* privileged_app = NULL;
  int opt;
  char useropt_given = 0;
  char grpopt_given = 0;
  //optarg is set by getopt
  while ((opt = getopt(argc, argv, "a:w:v:h:p:u:g:n:")) != -1)
  {
    switch (opt)
    {
      case 'a':
        init_app = optarg;
        SWI_LOG("APPMON", DEBUG, "Command line arguments parsing: init_app %s\n", init_app);
        break;
      case 'w':
        init_app_wd = optarg;
        SWI_LOG("APPMON", DEBUG, "Command line arguments parsing: init_app_wd %s\n", init_app_wd);
        break;
      case 'p':
        parse_arg_integer(optarg, &portno, "Command line arguments parsing: bad format for port argument");
        SWI_LOG("APPMON", DEBUG, "Command line arguments parsing: port =%d\n", portno);
        if (portno > UINT16_MAX)
        {
          err_exit("Command line arguments parsing: bad value for port, range=[0, 65535]");
        }
        break;
      case 'u':
        useropt_given = 1; //used to set default value after cmd line option parsing
        get_uid_option(&uid);
        break;
      case 'v':
        get_uid_option(&puid);
        break;
      case 'g':
        grpopt_given = 1; //used to set default value after cmd line option parsing
        get_gid_option(&gid);
        break;
      case 'h':
        get_gid_option(&pgid);
        break;
      case 'n':
        parse_arg_integer(optarg, &app_priority,
            "Command line arguments parsing: app process priority must be an integer");
        if (19 < app_priority || -20 > app_priority)
        {
          err_exit("Command line arguments parsing: app process priority must be between -20 and 19");
        }
        SWI_LOG("APPMON", DEBUG, "Command line arguments parsing: nice increment =%d\n", app_priority);
        break;
      default: /* '?' */
        SWI_LOG("APPMON", ERROR, "Command line arguments parsing: unknown argument\n");
        break;
    }

  }
  if (NULL != init_app)
  {

    if (NULL == init_app_wd)
    { //using current working directory as privileged app wd.
      cwd = malloc(PATH_MAX);
      if (NULL == cwd)
      {
        err_exit("Cannot malloc init_app_wd");
      }
      cwd = getcwd(cwd, PATH_MAX);
      if (NULL == cwd)
      {
        err_exit("getcwd failed to guess privileged app default wd");
      }
      init_app_wd = cwd;
    }
    char * res = check_params(init_app_wd, init_app);
    if (NULL != res)
    {
      SWI_LOG("APPMON", ERROR, "check_params on privileged app failed: %s\n", res);
      err_exit("check_params on privileged app failed");
    }
    privileged_app = add_app(init_app_wd, init_app, 1);
    if (NULL == privileged_app)
    {
      err_exit("add_app on privileged app failed");
    }
  }

  if (!uid && !useropt_given)
  { //get default "nobody" user.
    uid = 65534;
  }

  if (!gid && !grpopt_given)
  { //get default "nogroup" group.
    gid = 65534;
  }

  SWI_LOG("APPMON", DEBUG, "Command line arguments parsing: will use uid=%d and gid=%d to run unprivileged apps\n",
      uid, gid);

  /* configuring signals handling */
  if (sigaction(SIGCHLD, &action_CHLD, NULL))
    err_exit("configuring signals handling: sigaction SIGCHLD call error");

  if (sigaction(SIGALRM, &action_ALRM, NULL))
    err_exit("configuring signals handling: sigaction SIGCHLD call error");

  srv_skt = socket(AF_INET, SOCK_STREAM, 0);
  if (srv_skt < 0)
    err_exit("socket configuration: opening socket error");

  // set SO_REUSEADDR on socket:
  optval = 1;
  if (setsockopt(srv_skt, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval))
    err_exit("socket configuration: setting SO_REUSEADDR on socket failed");

  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = portno ? portno : DEFAULT_LISTENING_PORT;

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if (bind(srv_skt, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    err_exit("socket configuration: error on binding");

  if (listen(srv_skt, 5))
    err_exit("socket configuration: error on listen");

  clilen = sizeof(cli_addr);
  stop = 0;

  SWI_LOG("APPMON", DEBUG, "Init successful, now running as daemon.\n");
  /* daemonize the later possible to enhance sync error reporting*/
  daemonize();
  /* Now we are a simple daemon */
  SWI_LOG("APPMON", DEBUG, "Daemon pid=%d, Listening port = %d\n", getpid(), portno);

  if (privileged_app)
  {
    SWI_LOG("APPMON", DEBUG, "Autostarting privileged app\n");
    start_app(privileged_app);
  }

  while (!stop)
  {
    fflush(stdout);
    client_skt = accept(srv_skt, (struct sockaddr *) &cli_addr, &clilen);
    if (client_skt < 0)
    {
      SWI_LOG("APPMON", ERROR, "socket configuration: error on accept: %s\n", strerror(errno));
      SWI_LOG("APPMON", ERROR, "Now going to crippled mode: cannot use socket API anymore!\n");
      if (client_skt)
        close(client_skt);
      if (srv_skt)
        close(srv_skt);
      // Sleep for 1.5 sec
      // sleep() function not used here, as it may disrupt the use of SIGALRM made in this program.
      struct timeval tv;
      while (1)
      {
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        int res = select(0, NULL, NULL, NULL, &tv);
        SWI_LOG("APPMON", DEBUG, "crippled mode: select, res = %d\n", res);
      }
      //never returning from here, need to kill the daemon
      // but apps should still be managed.
    }

    SWI_LOG("APPMON", DEBUG, "new client ...\n");
    buffer = readline(client_skt);

    //deal with all the requests coming from the new client
    while (NULL != buffer && !stop)
    {
      SWI_LOG("APPMON", DEBUG, "NEW cmd=[%s]\n", buffer);
      do
      {
        if (!strncmp(buffer, STOP_DAEMON, strlen(STOP_DAEMON)))
        {
          stop = 1;
          send_result("ok, destroy is in progress, stopping aps, closing sockets.");
          break;
        }
        if (!strncmp(buffer, PCONFIG, strlen(PCONFIG)))
        {
          send_result(
              fill_output_buf(
                  "appmon_daemon: version[%s], uid=[%d], gid=[%d], puid=[%d], pgid=[%d], app_priority=[%d]",
                  GIT_REV, uid, gid, puid, pgid, app_priority));
          break;
        }
        if (!strncmp(buffer, SETUP_APP, strlen(SETUP_APP)))
        {
          char* buf = buffer;
          strsep(&buf, " ");
          char* wd = strsep(&buf, " ");
          char* prog = strsep(&buf, " ");

          SWI_LOG("APPMON", DEBUG, "SETUP wd =%s, prog = %s\n", wd, prog);
          if (NULL == wd || NULL == prog)
          {
            send_result("Bad command format, must have wd and prog params");
            break;
          }
          char *res = check_params(wd, prog);
          if (res)
          {
            send_result(res);
            break;
          }
          sigprocmask(SIG_BLOCK, &block_sigs, NULL);
          app_t* app = add_app(wd, prog, 0);
          if (NULL == app)
            send_result("Cannot add app");
          else
            send_result(fill_output_buf("%d", app->id));

          sigprocmask(SIG_UNBLOCK, &block_sigs, NULL);

          break;
        }
        if (!strncmp(buffer, START_APP, strlen(START_APP)))
        {
          char* str_id = buffer + strlen(START_APP);
          int id = atoi(str_id);
          SWI_LOG("APPMON", DEBUG, "START_APP, id =%d\n", id);
          if (id == 0)
          {
            send_result("Bad command format, start called with invalid app id");
            break;
          }
          sigprocmask(SIG_BLOCK, &block_sigs, NULL);
          app_t* app = find_by_id(id);
          if (app == NULL)
          {
            send_result("Unknown app");
            sigprocmask(SIG_UNBLOCK, &block_sigs, NULL);
            break;
          }
          if (app->privileged)
          {
            send_result("Privileged App, cannot act on it through socket.");
            sigprocmask(SIG_UNBLOCK, &block_sigs, NULL);
            break;
          }
          if (app->status != KILLED)
          {
            send_result("App already running (or set to be restarted), start command discarded");
            sigprocmask(SIG_UNBLOCK, &block_sigs, NULL);
            break;
          }
          send_result(start_app(app));
          sigprocmask(SIG_UNBLOCK, &block_sigs, NULL);
          break;
        }

        if (!strncmp(buffer, STOP_APP, strlen(STOP_APP)))
        {
          char* str_id = buffer + strlen(STOP_APP);
          int id = atoi(str_id);
          if (id == 0)
          {
            send_result("Bad command format, stop called with invalid app id");
            break;
          }
          sigprocmask(SIG_BLOCK, &block_sigs, NULL);
          app_t* app = find_by_id(id);
          if (NULL == app)
            send_result("Unknown app");
          else
          {
            if (app->privileged)
            {
              send_result("Privileged App, cannot act on it through socket.");
              sigprocmask(SIG_UNBLOCK, &block_sigs, NULL);
              break;
            }

            //stop command has effect only if application is running.
            if (app->status == STARTED || app->status == TO_BE_KILLED)
            {
              send_result(stop_app(app));
            }
            else
            { //application is already stopped (app->status could be KILLED or TO_BE_RESTARTED)
              app->status = KILLED; //force app->status =  KILLED, prevent app to be restarted if restart was scheduled. (see SIG ALRM handler)
              send_result("ok, already stopped, won't be automatically restarted anymore");
            }

          }
          sigprocmask(SIG_UNBLOCK, &block_sigs, NULL);
          break;
        }

        if (!strncmp(buffer, REMOVE_APP, strlen(REMOVE_APP)))
        {
          char* str_id = buffer + strlen(REMOVE_APP);
          int id = atoi(str_id);
          if (id == 0)
          {
            send_result("Bad command format, remove called with invalid app id");
            break;
          }
          sigprocmask(SIG_BLOCK, &block_sigs, NULL);
          app_t* app = find_by_id(id);
          if (NULL == app)
            send_result("Unknown app");
          else
          {
            if (app->privileged)
            {
              send_result("Privileged App, cannot act on it through socket.");
              sigprocmask(SIG_UNBLOCK, &block_sigs, NULL);
              break;
            }
            //stop command has effect only if application is running.
            if (app->status == STARTED || app->status == TO_BE_KILLED)
            {
              stop_app(app); //trying to stop, no big deal with it fails
            }

            app_t* app = NULL;
            unsigned int size, i = 0;
            PointerList_GetSize(apps, &size, NULL);
            for (i = 0; i < size; i++)
            {
              PointerList_Peek(apps, i, (void**) &app);
              if (app->id == id)
              {
                swi_status_t res = 0;
                if (SWI_STATUS_OK != (res = PointerList_Remove(apps, i, (void**) &app)))
                {
                  send_result(fill_output_buf("Remove: PointerList_Remove failed, AwtStatus =%d", res));
                }
                else
                {
                  free(app);
                  send_result("ok");
                }
                break;
              }
            }
          }
          sigprocmask(SIG_UNBLOCK, &block_sigs, NULL);
          break;
        }

        if (!strncmp(buffer, STATUS_APP, strlen(STATUS_APP)))
        {
          char* str_id = buffer + strlen(STATUS_APP);
          int id = atoi(str_id);
          if (id == 0)
          {
            send_result("Bad command format, status called with invalid app id");
            break;
          }

          sigprocmask(SIG_BLOCK, &block_sigs, NULL);
          app_t* app = find_by_id(id);
          if (NULL == app)
            send_result("Unknown app");
          else
          {
            SWI_LOG("APPMON", DEBUG, "sending app status...\n");
            send_result(create_app_status(app));
          }
          sigprocmask(SIG_UNBLOCK, &block_sigs, NULL);
          break;
        }
        if (!strncmp(buffer, LIST_APPS, strlen(LIST_APPS)))
        {
          SWI_LOG("APPMON", DEBUG, "sending app list ...\n");
          sigprocmask(SIG_BLOCK, &block_sigs, NULL);
          app_t* app = NULL;
          unsigned int size, i = 0;
          PointerList_GetSize(apps, &size, NULL);
          for (i = 0; i < size; i++)
          {
            PointerList_Peek(apps, i, (void**) &app);
            char* app_status_tmp = create_app_status(app);
            if (strlen(app_status_tmp) != write(client_skt, app_status_tmp, strlen(app_status_tmp)))
            {
              SWI_LOG("APPMON", ERROR, "list: cannot write res to socket\n");
            }
            SWI_LOG("APPMON", DEBUG, "list: send status, app_status_tmp=%s\n", app_status_tmp);
            char* statussep = "\t";
            if (strlen(statussep) != write(client_skt, statussep, strlen(statussep)))
            {
              SWI_LOG("APPMON", ERROR, "list: cannot write statussep: %s\n", statussep);
            }
          }
          send_result("");
          sigprocmask(SIG_UNBLOCK, &block_sigs, NULL);
          break;
        }
        if (!strncmp(buffer, SETENV, strlen(SETENV)))
        {
          char *arg, *varname, *tmp;

          arg = buffer + strlen(SETENV);
          varname = arg;
          tmp = strchr(arg, '=');
          *tmp++ = '\0';

          SWI_LOG("APPMON", DEBUG, "Setting Application framework environment variable %s = %s...\n", varname, tmp);
          setenv(varname, tmp, 1);

          send_result("");
          break;
        }

        //command not found
        send_result("command not found");
        SWI_LOG("APPMON", DEBUG, "Command not found\n");
      } while (0);

      if (stop)
        break;

      //read some data again to allow to send several commands with the same socket
      buffer = readline(client_skt);

    } //end while buffer not NULL: current client has no more data to send

    //current client exited, let's close client skt, wait for another connexion
    close(client_skt);
  }

  sigprocmask(SIG_BLOCK, &block_sigs, NULL);
  int exit_status_daemon = clean_all();
  SWI_LOG("APPMON", DEBUG, "appmon daemon end, exit_status_daemon: %d\n", exit_status_daemon);
  return exit_status_daemon;
}