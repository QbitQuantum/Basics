static int
setup_child(pid_t *pid, const char *term, const char *attr, char *const *argv)
{
  int master;
  char ttyname[20];

  DBUG_ENTER("setup_child");
  switch ((*pid = pty_fork(&master, ttyname, 0, 0))) {
  case -1:
    DBUG_PRINT("startup", ("forkpty: failed"));
    DBUG_RETURN(-errno);
    /*NOTREACHED*/
  case 0: {
    const char *shell;
    DBUG_PROCESS("child");

    DBUG_PRINT("info", ("TERM=%s", term));
    if (term) setenv("TERM", term, 1);

    DBUG_PRINT("info", ("attributes=%s", attr));
    if (attr) init_pty(0, attr);

    if (!(shell = argv[0])) {
      char *s0;
      uid_t uid;
      struct passwd *pw;
      shell = "/bin/bash";
      s0 = "-bash";
      /* get user's login shell */
      if (!(pw = getpwuid(uid = getuid()))) {
        DBUG_PRINT("error", ("getpwuid(%ld) failed: %s",
          uid, strerror(errno)));
      }
      else if (!(shell = pw->pw_shell) || *shell != '/') {
        DBUG_PRINT("error", ("bad shell for user id %ld", uid));
      }
      else {
        DBUG_PRINT("info", ("got shell %s", shell));
        s0 = strrchr(shell, '/');
        s0 = str_dup(s0);
        assert(s0 != 0);
        s0[0] = '-';
      }
      DBUG_PRINT("info", ("startup %s (%s)", shell, s0));
      execl(shell, s0, (char *)0);
    }
    else {
      DBUG_PRINT("info", ("startup %s", *argv));
      execvp(*argv, argv);
    }

    DBUG_PRINT("error", ("exec* failed: %s", strerror(errno)));
    perror(shell);
    exit(111);
    /*NOTREACHED*/ }
  default: { // Parent process.
      fcntl(master, F_SETFL, O_NONBLOCK);
      char *dev = ptsname(master);
      if (dev) {
        struct utmp ut;
        memset(&ut, 0, sizeof ut);
        if (!strncmp(dev, "/dev/", 5))
          dev += 5;
        strlcpy(ut.ut_line, dev, sizeof ut.ut_line);
        if (dev[1] == 't' && dev[2] == 'y')
          dev += 3;
        if (!strncmp(dev, "pts/", 4))
          dev += 4;
        strncpy(ut.ut_id, dev, sizeof ut.ut_id);
        ut.ut_type = USER_PROCESS;
        ut.ut_pid = (long int)*pid;
        ut.ut_time = time(0);
        strlcpy(ut.ut_user, getlogin() ?: "?", sizeof ut.ut_user);
        gethostname(ut.ut_host, sizeof ut.ut_host);
        login(&ut);
      }
    }
  }
  DBUG_PRINT("startup", ("forkpty:pid=%ld:master=%d:ttyname=%s",
    (long int)*pid, master, ttyname));
  DBUG_RETURN(master);
}