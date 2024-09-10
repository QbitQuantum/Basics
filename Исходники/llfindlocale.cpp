FL_Success
FL_FindLocale(FL_Locale **locale, FL_Domain domain) {
  FL_Success success = FL_FAILED;
  FL_Locale *rtn = (FL_Locale*)malloc(sizeof(FL_Locale));
  rtn->lang = NULL;
  rtn->country = NULL;
  rtn->variant = NULL;

#ifdef WIN32
  /* win32 >= mswindows95 */
  {
    LCID lcid = GetThreadLocale();
    if (lcid_to_fl(lcid, rtn)) {
      success = FL_CONFIDENT;
    }
    if (success == FL_FAILED) {
      /* assume US English on mswindows systems unless we know otherwise */
      if (accumulate_locstring("en_US.ISO_8859-1", rtn)) {
        success = FL_DEFAULT_GUESS;
      }
    }
  }
#else
  /* assume unixoid */
  {
    /* examples: */
    /* sv_SE.ISO_8859-1 */
    /* fr_FR.ISO8859-1 */
    /* no_NO_NB */
    /* no_NO_NY */
    /* no_NO */
    /* de_DE */
    /* try the various vars in decreasing order of authority */
    if (accumulate_env("LC_ALL", rtn) ||
        accumulate_env("LC_MESSAGES", rtn) ||
        accumulate_env("LANG", rtn) ||
        accumulate_env("LANGUAGE", rtn)) {
      success = FL_CONFIDENT;
    }
    if (success == FL_FAILED) {
      /* assume US English on unixoid systems unless we know otherwise */
      if (accumulate_locstring("en_US.ISO_8859-1", rtn)) {
        success = FL_DEFAULT_GUESS;
      }
    }
  }
#endif

  if (success != FL_FAILED) {
    canonise_fl(rtn);
  }

  *locale = rtn;
  return success;
}