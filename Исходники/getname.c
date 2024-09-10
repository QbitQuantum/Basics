getname(char *defname, char *defpasswd)

/* Let person identify themselves from w */
{
  register char ch;
  int     secondsLeft = 199, laststate;
  char    tempstr[40];
  LONG    lasttime;
  char   *namptr, *passptr;
  register int j;
  struct timeval timeout;
  fd_set  readfds;

  autolog = (*defpasswd && *defname) ? 1 : 0;

  MZERO(mystats, sizeof(struct stats));

  mystats->st_tticks = 1;
  for (j = 0; j < 95; j++)
    {
      mystats->st_keymap[j] = j + 32;
      mystats->st_keymap[j + 96] = j + 32 + 96;

#ifdef MOUSE_AS_SHIFT
      mystats->st_keymap[j + 192] = j + 32;
      mystats->st_keymap[j + 288] = j + 32;
      mystats->st_keymap[j + 384] = j + 32;
#endif
    }
  mystats->st_keymap[95] = 0;
  mystats->st_flags = ST_MAPMODE + ST_NAMEMODE + ST_SHOWSHIELDS +
      ST_KEEPPEACE + ST_SHOWLOCAL * 2 + ST_SHOWGLOBAL * 2;

  lasttime = time(NULL);

  if (ghoststart)
    return;

  tempname[0] = '\0';
  password1[0] = '\0';
  password2[0] = '\0';

  laststate = state = ST_GETNAME;
  displayStartup(defname);
  while (1)
    {
      handleWEvents(defname);

      if (!autolog)
  {

#ifndef HAVE_WIN32
    W_FullScreen(baseWin);
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
#else
    /* Since we don't have a socket to check on Win32 for windowing *
     * system events, we set the timeout to zero and effectively poll.
     * * Yes, I could do the correct thing and call *
     * WaitForMultipleObjects() etc. but I don't feel like it */
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000;
#endif

    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);
    if (udpSock >= 0)
      FD_SET(udpSock, &readfds);

#ifndef HAVE_WIN32
    FD_SET(W_Socket(), &readfds);
#endif

    if (SELECT(32, &readfds, 0, 0, &timeout) < 0)
      {
        perror("select");
        continue;
      }

    if (FD_ISSET(sock, &readfds)
        || (udpSock >= 0 && FD_ISSET(udpSock, &readfds)))
      readFromServer(&readfds);

#ifndef HAVE_WIN32
    if (FD_ISSET(W_Socket(), &readfds))
#else
    if (W_EventsPending())
#endif

      handleWEvents(defname);
  }
      else
  {
    readFromServer(&readfds);
  }

      if (isServerDead())
  {
    printf("Shit, we were ghostbusted\n");

#ifdef HAVE_XPM
    W_GalacticBgd(GHOST_PIX);
#endif

#ifdef AUTOKEY
    if (autoKey)
      W_AutoRepeatOn();
#endif

    terminate(0);
  }

      if (time(0) != lasttime)
  {
    lasttime++;
    secondsLeft--;
    showreadme();
    if (!autolog)
      {
        sprintf(tempstr, "Seconds to go: %d ", secondsLeft);
        W_WriteText(w, 100, 400, textColor, tempstr, strlen(tempstr),
        W_RegularFont);
      }
    if (secondsLeft == 0)
      {
        me->p_status = PFREE;
        printf("Timed Out.\n");

#ifdef AUTOKEY
        if (autoKey)
    W_AutoRepeatOn();
#endif

        terminate(0);
      }
  }
      if (state == ST_DONE)
  {
    W_ClearWindow(w);
    W_ClearWindow(mapw);
    return;
  }
      if (autolog)
  {
    switch (state)
      {
      case ST_GETNAME:
        tempname[0] = '\0';
        ch = 13;
        j = 0;
        break;

      case ST_GETPASS:
      case ST_MAKEPASS1:
      case ST_MAKEPASS2:
        ch = defpasswd[j++];
        if (ch == '\0')
    {
      j = 0;
      ch = 13;
    }
        break;

      default:
        break;
      }

    loginproced(ch, defname);

  }

      laststate = state;
    }
}