int GWEN_Gui_CProgress_Advance(GWEN_GUI_CPROGRESS *cp, uint64_t progress) {
#ifndef OS_WIN32
  int fl;
#endif

  assert(cp);
  if (!cp->shown) {
    time_t t1;

    t1=time(0);
    if (difftime(t1, cp->startTime)>GWEN_GUI_DELAY_SECS) {
      if (!(GWEN_Gui_GetFlags(cp->gui) & GWEN_GUI_FLAGS_NONINTERACTIVE))
        GWEN_Gui_StdPrintf(cp->gui, stderr, "%s: Started.\n", cp->title);
      cp->shown=1;
    }
  }

  if (progress==GWEN_GUI_PROGRESS_ONE)
    progress=cp->current+1;
  if (progress!=GWEN_GUI_PROGRESS_NONE) {
    if (progress!=cp->current) {
      if (cp->shown) {
        if (!(GWEN_Gui_GetFlags(cp->gui) & GWEN_GUI_FLAGS_NONINTERACTIVE)) {
          if (cp->total==GWEN_GUI_PROGRESS_NONE)
            GWEN_Gui_StdPrintf(cp->gui, stderr, "%s: %llu\n", cp->title,
                               (long long unsigned)progress);
          else
            GWEN_Gui_StdPrintf(cp->gui, stderr, "%s: %llu of %llu\n",
                               cp->title,
                               (long long unsigned)progress,
                               (long long unsigned)cp->total);
        }
      }
      cp->current=progress;
    }
  }
  if (cp->aborted)
    return GWEN_ERROR_USER_ABORTED;

#ifndef OS_WIN32
  if (!(GWEN_Gui_GetFlags(cp->gui) & GWEN_GUI_FLAGS_NONINTERACTIVE)) {
    /* check for abort */
    fl=fcntl(fileno(stdin), F_GETFL);
    if (fl!=-1) {
      int chr;

      /* set stdin to nonblocking */
      if (fcntl(fileno(stdin), F_SETFL, fl | O_NONBLOCK)) {
        DBG_INFO(GWEN_LOGDOMAIN, "fcntl(stdin): %s", strerror(errno));
        return 0;
      }
      /* check whether there is a character */
      chr=getchar();
      /* set blocking mode to what we found before modification */
      fcntl(fileno(stdin), F_SETFL, fl);
      if (chr==GWEN_GUI_CPROGRESS_CHAR_ABORT) {
        GWEN_Gui_StdPrintf(cp->gui, stderr, "------> ABORTED BY USER\n");
        cp->aborted=1;
        return GWEN_ERROR_USER_ABORTED;
      }
    }
  }
#endif

  return 0;
}