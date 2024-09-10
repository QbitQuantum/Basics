void toolong(

  int sig)

  {
  char *id = "toolong";

  struct stat sb;
  pid_t cpid;

  log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, id,
             "scheduling iteration took too long");
  DBPRT(("scheduling iteration too long\n"))

  if (connector >= 0 && server_disconnect(connector))
    log_err(errno, id, "server_disconnect");

  if (close(server_sock))
    log_err(errno, id, "close");

  if ((cpid = fork()) > 0)   /* parent re-execs itself */
    {
    rpp_terminate();
#ifndef linux
    sleep(5);
#endif

    /* hopefully, that gave the child enough */
    /*   time to do its business. anyhow:    */
    (void)waitpid(cpid, NULL, 0);

    if (chdir(oldpath) == -1)
      {
      sprintf(log_buffer, "chdir to %s", oldpath);
      log_err(errno, id, log_buffer);
      }

    sprintf(log_buffer, "restart dir %s object %s",

            oldpath, glob_argv[0]);
    log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER,
               id, log_buffer);

    execvp(glob_argv[0], glob_argv);
    log_err(errno, id, "execv");
    exit(3);
    }

  /*
  ** Child (or error on fork) gets here and tried
  ** to dump core.
  */
  if (stat("core", &sb) == -1)
    {
    if (errno == ENOENT)
      {
      log_close(1);
      abort();
      rpp_terminate();
      exit(2); /* not reached (hopefully) */
      }

    log_err(errno, id, "stat");
    }

  log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER,

             id, "exiting without core dump");
  log_close(1);
  rpp_terminate();
  exit(0);
  }