int spcmd_splitadd(void *source, int cargc, char **cargv) {
  nick *np = (nick*)source;
  unsigned long long num;
  char *end;
  flag_t servertype = 0;
  char *servername;
  size_t servernamelen;
  time_t splittime;
  server fake;

  if (cargc < 1) {
      controlreply(np, "Usage: splitadd <servername> [+flags] [split time as unix timestamp]");
      return CMD_ERROR;
  }

  servername = cargv[0];
  servernamelen = strlen(servername);

  if (findserver(servername) != -1) {
    controlreply(np, "Server %s is linked right now, refusing to add split.",
        servername);
    return CMD_ERROR;
  }

  if (doessplitalreadyexist(servername)) {
    controlreply(np, "There is a split for %s already.", servername);
    return CMD_ERROR;
  }

  if (servernamelen > SERVERLEN) {
    controlreply(np, "Server name %s is too long (max: %d characters)",
        servername, SERVERLEN);
    return CMD_ERROR;
  }

  /* Handle flags */
  if (cargc > 1) {
    if (setflags(&servertype, (flag_t)-1, cargv[1], servertypeflags,
          REJECT_UNKNOWN) != REJECT_NONE) {
      controlreply(np, "Flag string %s contained invalid flags.", cargv[1]);
      return CMD_ERROR;
    }
  } else {
    /* Set up a fake server for getservertype. */
    memset(&fake, 0, sizeof(fake));

    fake.name = getsstring(servername, servernamelen);
    servertype = getservertype(&fake);
    freesstring(fake.name);
  }

  /* Handle timestamp */
  if (cargc < 3) {
    splittime = getnettime();
  } else {
    errno = 0;
    num = strtoull(cargv[2], &end, 10);
    if (errno == ERANGE) {
      controlreply(np, "%s is out of range for a timestamp.", cargv[2]);
      return CMD_ERROR;
    }

    /* Truncation may happen here. 
     * However, there's no way to get the max time_t value, so we'll just try to
     * find out after the fact.
     */
    splittime = (time_t)num;

    if ((unsigned long long)splittime < num) {
      controlreply(np, "Tried to use %llu as split time value, but it's too "
          "large for the system to handle", num);
      return CMD_ERROR;
    }
  }

  sp_addsplit(servername, splittime, servertype);
  controlreply(np, "Added split for %s (%s ago) with flags %s.",
      servername, longtoduration(getnettime() - splittime, 1),
      printflags(servertype, servertypeflags));

  return CMD_OK;
}