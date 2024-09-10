void log_record(

  int         eventtype,  /* I */
  int         objclass,   /* I */
  const char *objname,    /* I */
  const char *text)       /* I */

  {
  int tryagain = 2;
  time_t now;
  pid_t  thr_id = -1;

  struct tm *ptm;
  struct tm  tmpPtm;
  int    rc = 0;
  FILE  *savlog;
  char  *start = NULL, *end = NULL;
  size_t nchars;
  int eventclass = 0;
  char time_formatted_str[64];

  thr_id = syscall(SYS_gettid);
  pthread_mutex_lock(log_mutex);

  if (log_opened < 1)
    {
    pthread_mutex_unlock(log_mutex);
    return;
    }

  now = time((time_t *)0); /* get time for message */

  ptm = localtime_r(&now,&tmpPtm);

  /* Do we need to switch the log? */

  if (log_auto_switch && (ptm->tm_yday != log_open_day))
    {
    log_close(1);

    log_open(NULL, log_directory);

    if (log_opened < 1)
      {
      pthread_mutex_unlock(log_mutex);
      return;
      }
    }
  
  time_formatted_str[0] = 0;    
  log_get_set_eventclass(&eventclass, GETV);
  if (eventclass == PBS_EVENTCLASS_TRQAUTHD)
    {
    log_format_trq_timestamp(time_formatted_str, sizeof(time_formatted_str));
    }

  /*
   * Looking for the newline characters and splitting the output message
   * on them.  Sequence "\r\n" is mapped to the single newline.
   */
  start = (char *)text;

  while (1)
    {
    for (end = start; *end != '\n' && *end != '\r' && *end != '\0'; end++)
      ;

    nchars = end - start;

    if (*end == '\r' && *(end + 1) == '\n')
      end++;

    while (tryagain)
      {
      if (eventclass != PBS_EVENTCLASS_TRQAUTHD)
        {
        rc = fprintf(logfile,
              "%02d/%02d/%04d %02d:%02d:%02d;%04x;%10.10s.%d;%s;%s;%s%.*s\n",
              ptm->tm_mon + 1,
              ptm->tm_mday,
              ptm->tm_year + 1900,
              ptm->tm_hour,
              ptm->tm_min,
              ptm->tm_sec,
              (eventtype & ~PBSEVENT_FORCE),
              msg_daemonname,
              thr_id,
              class_names[objclass],
              objname,
              (text == start ? "" : "[continued]"),
              (int)nchars,
              start);
        }
      else
        {
        rc = fprintf(logfile,
              "%s %s%.*s\n",
              time_formatted_str,
              (text == start ? "" : "[continued]"),
              (int)nchars,
              start);
        }
      if ((rc < 0) &&
          (errno == EPIPE) &&
          (tryagain == 2))
        {
        /* the log file descriptor has been changed--it now points to a socket!
         * reopen log and leave the previous file descriptor alone--do not close it */

        log_opened = 0;
        log_open(NULL, log_directory);
        tryagain--;
        }
      else
        {
        tryagain = 0;
        }
      }

    if (rc < 0)
      break;

    if (*end == '\0')
      break;

    start = end + 1;
    }  /* END while (1) */

  fflush(logfile);

  if (rc < 0)
    {
    rc = errno;
    clearerr(logfile);
    savlog = logfile;
    logfile = fopen("/dev/console", "w");
    /* we need to add this check to make sure the disk isn't full so we don't segfault 
     * if we can't open this then we're going to have a nice surprise failure */
    if (logfile != NULL)
      {
      pthread_mutex_unlock(log_mutex);
      log_err(rc, __func__, "PBS cannot write to its log");
      fclose(logfile);
      pthread_mutex_lock(log_mutex);
      }

    logfile = savlog;
    }
  
  pthread_mutex_unlock(log_mutex);

  return;
  }  /* END log_record() */