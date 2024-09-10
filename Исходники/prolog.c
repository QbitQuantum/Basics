int run_pelog(

  int   which,      /* I (one of PE_*) */
  char *specpelog,  /* I - script path */
  job  *pjob,       /* I - associated job */
  int   pe_io_type) /* I */

  {
  char *id = "run_pelog";

  struct sigaction act;
  struct sigaction oldact;
  char *arg[12];
  int   fds1 = 0;
  int   fds2 = 0;
  int   fd_input;
  char  resc_list[2048];
  char  resc_used[2048];

  struct stat sbuf;
  char   sid[20];
  char   exit_stat[11];
  int    waitst;
  int    isjoined;  /* boolean */
  char   buf[MAXPATHLEN + 1024];
  char   pelog[MAXPATHLEN + 1024];

  uid_t  real_uid = 0;
  gid_t *real_gids = NULL;
  gid_t  real_gid = 0;
  int    num_gids = 0;

  int    jobtypespecified = 0;

  resource      *r;

  char          *EmptyString = "";

  int            LastArg;
  int            aindex;

  int            rc;

  char          *ptr;

  if ((pjob == NULL) || (specpelog == NULL) || (specpelog[0] == '\0'))
    {
    return(0);
    }

  ptr = pjob->ji_wattr[(int)JOB_ATR_jobtype].at_val.at_str;

  if (ptr != NULL)
    {
    jobtypespecified = 1;

    snprintf(pelog,sizeof(pelog),"%s.%s",
      specpelog,
      ptr);
    }
  else
    {
    strncpy(pelog,specpelog,sizeof(pelog));
    }

  /* to support root squashing, become the user before performing file checks */
  if ((which == PE_PROLOGUSER) || 
      (which == PE_EPILOGUSER) || 
      (which == PE_PROLOGUSERJOB) || 
      (which == PE_EPILOGUSERJOB))
    {
    real_uid = getuid();
    real_gid = getgid();

    if ((num_gids = getgroups(0,real_gids)) < 0)
      {
      log_err(errno,id,"getgroups failed\n");

      return(-1);
      }
    else
      {
      real_gids = malloc(sizeof(gid_t) * num_gids);
      
      if (real_gids == NULL)
        {
        log_err(ENOMEM,id,"Cannot allocate memory! FAILURE\n");

        return(-1);
        }

      if (getgroups(num_gids,real_gids) < 0)
        {
        log_err(errno,id,"getgroups failed\n");
        
        return(-1);
        }
      }

    /* pjob->ji_grpcache will not be set if using LDAP and LDAP not set */
    /* It is possible that ji_grpcache failed to allocate as well. 
       Make sure ji_grpcache is not NULL */
    if (pjob->ji_grpcache != NULL)
      {
      if (setgroups(
            pjob->ji_grpcache->gc_ngroup,
            (gid_t *)pjob->ji_grpcache->gc_groups) != 0)
        {
        snprintf(log_buffer,sizeof(log_buffer),
          "setgroups() for UID = %lu failed: %s\n",
          (unsigned long)pjob->ji_qs.ji_un.ji_momt.ji_exuid,
          strerror(errno));
      
        log_err(errno, id, log_buffer);
      
        undo_set_euid_egid(which,real_uid,real_gid,num_gids,real_gids,id);
      
        return(-1);
        }
      }
    else
      {
      sprintf(log_buffer, "pjob->ji_grpcache is null. check_pwd likely failed.");
      log_err(-1, id, log_buffer);
      undo_set_euid_egid(which,real_uid,real_gid,num_gids,real_gids,id);
      return(-1);
      }
    
    if (setegid(pjob->ji_qs.ji_un.ji_momt.ji_exgid) != 0)
      {
      snprintf(log_buffer,sizeof(log_buffer),
        "setegid(%lu) for UID = %lu failed: %s\n",
        (unsigned long)pjob->ji_qs.ji_un.ji_momt.ji_exgid,
        (unsigned long)pjob->ji_qs.ji_un.ji_momt.ji_exuid,
        strerror(errno));
      
      log_err(errno, id, log_buffer);
      
      undo_set_euid_egid(which,real_uid,real_gid,num_gids,real_gids,id);
      
      return(-1);
      }
    
    if (seteuid(pjob->ji_qs.ji_un.ji_momt.ji_exuid) != 0)
      {
      snprintf(log_buffer,sizeof(log_buffer),
        "seteuid(%lu) failed: %s\n",
        (unsigned long)pjob->ji_qs.ji_un.ji_momt.ji_exuid,
        strerror(errno));
      
      log_err(errno, id, log_buffer);
      
      undo_set_euid_egid(which,real_uid,real_gid,num_gids,real_gids,id);

      return(-1);
      }
    }

  rc = stat(pelog,&sbuf);

  if ((rc == -1) && (jobtypespecified == 1))
    {
    strncpy(pelog,specpelog,sizeof(pelog));

    rc = stat(pelog,&sbuf);
    }

  if (rc == -1)
    {
    if (errno == ENOENT || errno == EBADF)
      {
      /* epilog/prolog script does not exist */

      if (LOGLEVEL >= 5)
        {
        static char tmpBuf[1024];

        sprintf(log_buffer, "%s script '%s' for job %s does not exist (cwd: %s,pid: %d)",
          PPEType[which],
          (pelog != NULL) ? pelog : "NULL",
          (pjob != NULL) ? pjob->ji_qs.ji_jobid : "NULL",
          getcwd(tmpBuf, sizeof(tmpBuf)),
          getpid());

        log_record(PBSEVENT_SYSTEM, 0, id, log_buffer);
        }

#ifdef ENABLE_CSA
      if ((which == PE_EPILOGUSER) && (!strcmp(pelog, path_epiloguser)))
        {
        /*
          * Add a workload management end record
        */
        if (LOGLEVEL >= 8)
          {
          sprintf(log_buffer, "%s calling add_wkm_end from run_pelog() - no user epilog",
            pjob->ji_qs.ji_jobid);

          log_err(-1, id, log_buffer);
          }

        add_wkm_end(pjob->ji_wattr[(int)JOB_ATR_pagg_id].at_val.at_ll,

                    pjob->ji_qs.ji_un.ji_momt.ji_exitstat, pjob->ji_qs.ji_jobid);
        }

#endif /* ENABLE_CSA */

      undo_set_euid_egid(which,real_uid,real_gid,num_gids,real_gids,id);

      return(0);
      }
      
    undo_set_euid_egid(which,real_uid,real_gid,num_gids,real_gids,id);

    return(pelog_err(pjob,pelog,errno,"cannot stat"));
    }

  if (LOGLEVEL >= 5)
    {
    sprintf(log_buffer,"running %s script '%s' for job %s",
      PPEType[which],
      (pelog != NULL) ? pelog : "NULL",
      pjob->ji_qs.ji_jobid);

    log_ext(-1,id,log_buffer,LOG_DEBUG);  /* not actually an error--but informational */
    }

  /* script must be owned by root, be regular file, read and execute by user *
   * and not writeable by group or other */

  if (reduceprologchecks == TRUE)
    {
    if ((!S_ISREG(sbuf.st_mode)) ||
        (!(sbuf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))))
      {
      undo_set_euid_egid(which,real_uid,real_gid,num_gids,real_gids,id);
      return(pelog_err(pjob,pelog,-1,"permission Error"));
      }
    }
  else
    {
    if (which == PE_PROLOGUSERJOB || which == PE_EPILOGUSERJOB)
      {
      if ((sbuf.st_uid != pjob->ji_qs.ji_un.ji_momt.ji_exuid) || 
          (!S_ISREG(sbuf.st_mode)) ||
          ((sbuf.st_mode & (S_IRUSR | S_IXUSR)) != (S_IRUSR | S_IXUSR)) ||
          (sbuf.st_mode & (S_IWGRP | S_IWOTH)))
        {
        undo_set_euid_egid(which,real_uid,real_gid,num_gids,real_gids,id);
        return(pelog_err(pjob,pelog,-1,"permission Error"));
        }
      }
    else if ((sbuf.st_uid != 0) ||
        (!S_ISREG(sbuf.st_mode)) ||
        ((sbuf.st_mode & (S_IRUSR | S_IXUSR)) != (S_IRUSR | S_IXUSR)) ||\
        (sbuf.st_mode & (S_IWGRP | S_IWOTH)))
      {
      undo_set_euid_egid(which,real_uid,real_gid,num_gids,real_gids,id);
      return(pelog_err(pjob,pelog,-1,"permission Error"));
      }
    
    if ((which == PE_PROLOGUSER) || (which == PE_EPILOGUSER))
      {
      /* script must also be read and execute by other */
      
      if ((sbuf.st_mode & (S_IROTH | S_IXOTH)) != (S_IROTH | S_IXOTH))
        {
        undo_set_euid_egid(which,real_uid,real_gid,num_gids,real_gids,id);
        return(pelog_err(pjob, pelog, -1, "permission Error"));
        }
      }
    } /* END !reduceprologchecks */

  fd_input = pe_input(pjob->ji_qs.ji_jobid);

  if (fd_input < 0)
    {
    undo_set_euid_egid(which,real_uid,real_gid,num_gids,real_gids,id);
    return(pelog_err(pjob, pelog, -2, "no pro/epilogue input file"));
    }

  run_exit = 0;

  child = fork();

  if (child > 0)
    {
    int KillSent = FALSE;

    /* parent - watch for prolog/epilog to complete */

    close(fd_input);

    /* switch back to root if necessary */
    undo_set_euid_egid(which,real_uid,real_gid,num_gids,real_gids,id);

    act.sa_handler = pelogalm;

    sigemptyset(&act.sa_mask);

    act.sa_flags = 0;

    sigaction(SIGALRM, &act, &oldact);

    /* it would be nice if the harvest routine could block for 5 seconds,
       and if the prolog is not complete in that time, mark job as prolog
       pending, append prolog child, and continue */

    /* main loop should attempt to harvest prolog in non-blocking mode.
       If unsuccessful after timeout, job should be terminated, and failure
       reported.  If successful, mom should unset prolog pending, and
       continue with job start sequence.  Mom should report job as running
       while prologpending flag is set.  (NOTE:  must track per job prolog
       start time)
    */

    alarm(pe_alarm_time);

    while (waitpid(child, &waitst, 0) < 0)
      {
      if (errno != EINTR)
        {
        /* exit loop. non-alarm based failure occurred */

        run_exit = -3;

        MOMPrologFailureCount++;

        break;
        }

      if (run_exit == -4)
        {
        if (KillSent == FALSE)
          {
          MOMPrologTimeoutCount++;

          /* timeout occurred */

          KillSent = TRUE;

          /* NOTE:  prolog/epilog may be locked in KERNEL space and unkillable */

          alarm(5);
          }
        else
          {
          /* cannot kill prolog/epilog, give up */

          run_exit = -5;

          break;
          }
        }
      }    /* END while (wait(&waitst) < 0) */

    /* epilog/prolog child completed */
#ifdef ENABLE_CSA
    if ((which == PE_EPILOGUSER) && (!strcmp(pelog, path_epiloguser)))
      {
      /*
       * Add a workload management end record
      */
      if (LOGLEVEL >= 8)
        {
        sprintf(log_buffer, "%s calling add_wkm_end from run_pelog() - after user epilog",
                pjob->ji_qs.ji_jobid);

        log_err(-1, id, log_buffer);
        }

      add_wkm_end(pjob->ji_wattr[(int)JOB_ATR_pagg_id].at_val.at_ll,

                  pjob->ji_qs.ji_un.ji_momt.ji_exitstat, pjob->ji_qs.ji_jobid);
      }

#endif /* ENABLE_CSA */

    alarm(0);

    /* restore the previous handler */

    sigaction(SIGALRM, &oldact, 0);

    if (run_exit == 0)
      {
      if (WIFEXITED(waitst))
        {
        run_exit = WEXITSTATUS(waitst);
        }
      }
    }
  else
    {
    /* child - run script */

    log_close(0);

    if (lockfds >= 0)
      {
      close(lockfds);

      lockfds = -1;
      }

    net_close(-1);

    if (fd_input != 0)
      {
      close(0);

      if (dup(fd_input) == -1) {}

      close(fd_input);
      }

    if (pe_io_type == PE_IO_TYPE_NULL)
      {
      /* no output, force to /dev/null */

      fds1 = open("/dev/null", O_WRONLY, 0600);
      fds2 = open("/dev/null", O_WRONLY, 0600);
      }
    else if (pe_io_type == PE_IO_TYPE_STD)
      {
      /* open job standard out/error */

      /*
       * We need to know if files are joined or not.
       * If they are then open the correct file and duplicate it to the other
      */

      isjoined = is_joined(pjob);

      switch (isjoined)
        {
        case -1:

          fds2 = open_std_file(pjob, StdErr, O_WRONLY | O_APPEND,
                               pjob->ji_qs.ji_un.ji_momt.ji_exgid);

          fds1 = dup(fds2);

          break;

        case 1:

          fds1 = open_std_file(pjob, StdOut, O_WRONLY | O_APPEND,
                               pjob->ji_qs.ji_un.ji_momt.ji_exgid);

          fds2 = dup(fds1);

          break;

        default:

          fds1 = open_std_file(pjob, StdOut, O_WRONLY | O_APPEND,
                               pjob->ji_qs.ji_un.ji_momt.ji_exgid);

          fds2 = open_std_file(pjob, StdErr, O_WRONLY | O_APPEND,
                               pjob->ji_qs.ji_un.ji_momt.ji_exgid);
          break;
        }
      }

    if (pe_io_type != PE_IO_TYPE_ASIS)
      {
      /* If PE_IO_TYPE_ASIS, leave as is, already open to job */

      if (fds1 != 1)
        {
        close(1);

        if (dup(fds1) == -1) {}

        close(fds1);
        }

      if (fds2 != 2)
        {
        close(2);

        if (dup(fds2) == -1) {}

        close(fds2);
        }
      }

    if ((which == PE_PROLOGUSER) || (which == PE_EPILOGUSER) || (which == PE_PROLOGUSERJOB) || (which == PE_EPILOGUSERJOB))
      {
      if (chdir(pjob->ji_grpcache->gc_homedir) != 0)
        {
        /* warn only, no failure */

        sprintf(log_buffer,
          "PBS: chdir to %s failed: %s (running user %s in current directory)",
          pjob->ji_grpcache->gc_homedir,
          strerror(errno),
          which == PE_PROLOGUSER ? "prologue" : "epilogue");

        if (write(2, log_buffer, strlen(log_buffer)) == -1) {}

        fsync(2);
        }
      }

    /* for both prolog and epilog */

    if (DEBUGMODE == 1)
      {
      fprintf(stderr, "PELOGINFO:  script:'%s'  jobid:'%s'  euser:'******'  egroup:'%s'  jobname:'%s' SSID:'%ld'  RESC:'%s'\n",
              pelog,
              pjob->ji_qs.ji_jobid,
              pjob->ji_wattr[(int)JOB_ATR_euser].at_val.at_str,
              pjob->ji_wattr[(int)JOB_ATR_egroup].at_val.at_str,
              pjob->ji_wattr[(int)JOB_ATR_jobname].at_val.at_str,
              pjob->ji_wattr[(int)JOB_ATR_session_id].at_val.at_long,
              resc_to_string(pjob, (int)JOB_ATR_resource, resc_list, sizeof(resc_list)));
      }

    arg[0] = pelog;

    arg[1] = pjob->ji_qs.ji_jobid;
    arg[2] = pjob->ji_wattr[(int)JOB_ATR_euser].at_val.at_str;
    arg[3] = pjob->ji_wattr[(int)JOB_ATR_egroup].at_val.at_str;
    arg[4] = pjob->ji_wattr[(int)JOB_ATR_jobname].at_val.at_str;

    /* NOTE:  inside child */

    if ( which == PE_EPILOG || which == PE_EPILOGUSER || which == PE_EPILOGUSERJOB )
      {
      /* for epilog only */

      sprintf(sid, "%ld",
              pjob->ji_wattr[(int)JOB_ATR_session_id].at_val.at_long);
      sprintf(exit_stat,"%d",
              pjob->ji_qs.ji_un.ji_exect.ji_exitstat);

      arg[5] = sid;
      arg[6] = resc_to_string(pjob, (int)JOB_ATR_resource, resc_list, sizeof(resc_list));
      arg[7] = resc_to_string(pjob, (int)JOB_ATR_resc_used, resc_used, sizeof(resc_used));
      arg[8] = pjob->ji_wattr[(int)JOB_ATR_in_queue].at_val.at_str;
      arg[9] = pjob->ji_wattr[(int)JOB_ATR_account].at_val.at_str;
      arg[10] = exit_stat;
      arg[11] = NULL;

      LastArg = 11;
      }
    else
      {
      /* prolog */

      arg[5] = resc_to_string(pjob, (int)JOB_ATR_resource, resc_list, sizeof(resc_list));
      arg[6] = pjob->ji_wattr[(int)JOB_ATR_in_queue].at_val.at_str;
      arg[7] = pjob->ji_wattr[(int)JOB_ATR_account].at_val.at_str;
      arg[8] = NULL;

      LastArg = 8;
      }

    for (aindex = 0;aindex < LastArg;aindex++)
      {
      if (arg[aindex] == NULL)
        arg[aindex] = EmptyString;
      }  /* END for (aindex) */

    /*
     * Pass Resource_List.nodes request in environment
     * to allow pro/epi-logue setup/teardown of system
     * settings.  --pw, 2 Jan 02
     * Fixed to use putenv for sysV compatibility.
     *  --troy, 11 jun 03
     *
     */

    r = find_resc_entry(
          &pjob->ji_wattr[(int)JOB_ATR_resource],
          find_resc_def(svr_resc_def, "nodes", svr_resc_size));

    if (r != NULL)
      {
      /* setenv("PBS_RESOURCE_NODES",r->rs_value.at_val.at_str,1); */

      const char *envname = "PBS_RESOURCE_NODES=";
      char *envstr;

      envstr = malloc(
                 (strlen(envname) + strlen(r->rs_value.at_val.at_str) + 1) * sizeof(char));

      if (envstr != NULL)
        {
        strcpy(envstr,envname);

        strcat(envstr,r->rs_value.at_val.at_str);

        /* do _not_ free the string when using putenv */

        putenv(envstr);
        }
      }  /* END if (r != NULL) */

    r = find_resc_entry(
          &pjob->ji_wattr[(int)JOB_ATR_resource],
          find_resc_def(svr_resc_def, "gres", svr_resc_size));

    if (r != NULL)
      {
      /* setenv("PBS_RESOURCE_NODES",r->rs_value.at_val.at_str,1); */

      const char *envname = "PBS_RESOURCE_GRES=";
      char *envstr;

      envstr = malloc(
                 (strlen(envname) + strlen(r->rs_value.at_val.at_str) + 1) * sizeof(char));

      if (envstr != NULL)
        {
        strcpy(envstr,envname);

        strcat(envstr,r->rs_value.at_val.at_str);

        /* do _not_ free the string when using putenv */

        putenv(envstr);
        }
      }  /* END if (r != NULL) */

    if (TTmpDirName(pjob, buf))
      {
      const char *envname = "TMPDIR=";
      char *envstr;

      envstr = malloc(
                 (strlen(envname) + strlen(buf) + 1) * sizeof(char));

      if (envstr != NULL)
        {
        strcpy(envstr,envname);

        strcat(envstr,buf);

        /* do _not_ free the string when using putenv */

        putenv(envstr);
        }
      }  /* END if (TTmpDirName(pjob,&buf)) */

    /* Set PBS_SCHED_HINT */

      {
      char *envname = "PBS_SCHED_HINT";
      char *envval;
      char *envstr;

      if ((envval = get_job_envvar(pjob, envname)) != NULL)
        {
        envstr = malloc((strlen(envname) + strlen(envval) + 2) * sizeof(char));

        if (envstr != NULL)
          {
          sprintf(envstr,"%s=%s",
            envname,
            envval);

          putenv(envstr);
          }
        }
      }

    /* Set PBS_NODENUM */
      {
      char *envname = "PBS_NODENUM";
      char *envstr;

      sprintf(buf, "%d",
        pjob->ji_nodeid);

      envstr = malloc((strlen(envname) + strlen(buf) + 2) * sizeof(char));

      if (envstr != NULL)
        {
        sprintf(envstr,"%s=%d",
          envname,
          pjob->ji_nodeid);

        putenv(envstr);
        }
      }

    /* Set PBS_MSHOST */
      {
      char *envname = "PBS_MSHOST";
      char *envstr;

      if ((pjob->ji_vnods[0].vn_host != NULL) && (pjob->ji_vnods[0].vn_host->hn_host != NULL))
        {
        envstr = malloc((strlen(envname) + strlen(pjob->ji_vnods[0].vn_host->hn_host) + 2) * sizeof(char));

        if (envstr != NULL)
          {
          sprintf(envstr,"%s=%s",
            envname,
            pjob->ji_vnods[0].vn_host->hn_host);

          putenv(envstr);
          }
        }
      }

    /* Set PBS_NODEFILE */
      {
      char *envname = "PBS_NODEFILE";
      char *envstr;

      if (pjob->ji_flags & MOM_HAS_NODEFILE)
        {
        sprintf(buf, "%s/%s",
          path_aux,
          pjob->ji_qs.ji_jobid);

        envstr = malloc((strlen(envname) + strlen(buf) + 2) * sizeof(char));

        if (envstr != NULL)
          {
          sprintf(envstr,"%s=%s",
            envname,
            buf);

          putenv(envstr);
          }
        }
      }

    /* Set PBS_O_Workdir */
      {
      char *envname = "PBS_O_WORKDIR";
      char *workdir_val;
      char *envstr;

      workdir_val = get_job_envvar(pjob,envname);
      if (workdir_val != NULL)
        {
        envstr = malloc((strlen(workdir_val) + strlen(envname) + 2) * sizeof(char));

        if (envstr != NULL)
          {
          sprintf(envstr,"%s=%s",
            envname,
            workdir_val);

          putenv(envstr);
          }
        }
      }

    /* SET BEOWULF_JOB_MAP */

      {

      struct array_strings *vstrs;

      int VarIsSet = 0;
      int j;

      vstrs = pjob->ji_wattr[(int)JOB_ATR_variables].at_val.at_arst;

      for (j = 0;j < vstrs->as_usedptr;++j)
        {
        if (!strncmp(
              vstrs->as_string[j],
              "BEOWULF_JOB_MAP=",
              strlen("BEOWULF_JOB_MAP=")))
          {
          VarIsSet = 1;

          break;
          }
        }

      if (VarIsSet == 1)
        {
        char *envstr;

        envstr = malloc((strlen(vstrs->as_string[j])) * sizeof(char));

        if (envstr != NULL)
          {
          strcpy(envstr,vstrs->as_string[j]);

          putenv(envstr);
          }
        }
      }

  /*
   * if we want to run as user then we need to reset real user permissions
   * since it seems that some OSs use real not effective user id when execv'ing
   */

  if ((which == PE_PROLOGUSER) || 
      (which == PE_EPILOGUSER) || 
      (which == PE_PROLOGUSERJOB) || 
      (which == PE_EPILOGUSERJOB))
    {
      seteuid(pbsuser);
      setegid(pbsgroup);

    if (setgid(pjob->ji_qs.ji_un.ji_momt.ji_exgid) != 0)
      {
      snprintf(log_buffer,sizeof(log_buffer),
        "setgid(%lu) for UID = %lu failed: %s\n",
        (unsigned long)pjob->ji_qs.ji_un.ji_momt.ji_exgid,
        (unsigned long)pjob->ji_qs.ji_un.ji_momt.ji_exuid,
        strerror(errno));
      
      log_err(errno, id, log_buffer);
      
      return(-1);
      }
    
    if (setuid(pjob->ji_qs.ji_un.ji_momt.ji_exuid) != 0)
      {
      snprintf(log_buffer,sizeof(log_buffer),
        "setuid(%lu) failed: %s\n",
        (unsigned long)pjob->ji_qs.ji_un.ji_momt.ji_exuid,
        strerror(errno));
      
      log_err(errno, id, log_buffer);
      
      return(-1);
      }
    }

    execv(pelog,arg);

    sprintf(log_buffer,"execv of %s failed: %s\n",
      pelog,
      strerror(errno));

    if (write(2, log_buffer, strlen(log_buffer)) == -1) 
      {
      /* cannot write message to stderr */

      /* NO-OP */
      }

    fsync(2);

    exit(255);
    }  /* END else () */

  switch (run_exit)
    {
    case 0:

      /* SUCCESS */

      /* NO-OP */

      break;

    case - 3:

      pelog_err(pjob, pelog, run_exit, "child wait interrupted");

      break;

    case - 4:

      pelog_err(pjob, pelog, run_exit, "prolog/epilog timeout occurred, child cleaned up");

      break;

    case - 5:

      pelog_err(pjob, pelog, run_exit, "prolog/epilog timeout occurred, cannot kill child");

      break;

    default:

      pelog_err(pjob, pelog, run_exit, "nonzero p/e exit status");

      break;
    }  /* END switch (run_exit) */

  return(run_exit);
  }  /* END run_pelog() */