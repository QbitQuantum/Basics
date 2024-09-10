MARPAWRAPPER_EXPORT void _genericLogger_defaultCallback(const void *userDatavp, const genericLoggerLevel_t leveli, const char *msgs) {
  /* We are NOT going to do a general log4c mechanism (this can come later) */
  /* I.e. we are fixing the default output to be: DD/MM/YYYY hh::mm::ss PREFIX MESSAGE */
  const char *prefixs =
    (leveli == GENERICLOGGER_LOGLEVEL_TRACE    ) ? "TRACE"     :
    (leveli == GENERICLOGGER_LOGLEVEL_DEBUG    ) ? "DEBUG"     :
    (leveli == GENERICLOGGER_LOGLEVEL_INFO     ) ? "INFO"      :
    (leveli == GENERICLOGGER_LOGLEVEL_NOTICE   ) ? "NOTICE"    :
    (leveli == GENERICLOGGER_LOGLEVEL_WARNING  ) ? "WARNING"   :
    (leveli == GENERICLOGGER_LOGLEVEL_ERROR    ) ? "ERROR"     :
    (leveli == GENERICLOGGER_LOGLEVEL_CRITICAL ) ? "CRITICAL"  :
    (leveli == GENERICLOGGER_LOGLEVEL_ALERT    ) ? "ALERT"     :
    (leveli == GENERICLOGGER_LOGLEVEL_EMERGENCY) ? "EMERGENCY" :
    "UNKOWN";
  char *dates = dateBuilder("%d/%m/%Y %H:%M:%S");
  char *localMsgs = messageBuilder("%s %9s %s\n", dates, prefixs, (msgs != NULL) ? (char *) msgs : (char *) GENERICLOGGER_LOG_NO_MESSAGE);
  char *p = localMsgs;
#ifdef FILENO
  int filenoStderr = FILENO(stderr);
#ifdef SYS_FILENO_IS_FILENO
  ssize_t bytesWriten = 0;
#else
  size_t bytesWriten = 0;
#endif
  size_t  count;
#endif

#ifdef FILENO
  count = strlen(p);
  while (bytesWriten < count) {
    bytesWriten += SYS_WRITE(filenoStderr, p+bytesWriten, count-bytesWriten);
  }
#else
  /* Note: this is not asynchroneous safe */
  fprintf(stderr, "%s", p);
#endif

  if (dates != dateBuilder_internalErrors()) {
    free(dates);
  }
  if (localMsgs != messageBuilder_internalErrors()) {
    free(localMsgs);
  }
}