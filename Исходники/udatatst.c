/* Test whether apps and ICU can each have their own root.res */
static void TestAppData()
{
  UResourceBundle *icu, *app;
  UResourceBundle *tmp = NULL;
  UResourceBundle *tmp2 = NULL;
  
  const UChar *appString;
  const UChar *icuString;

  int32_t len;

  UErrorCode status = U_ZERO_ERROR;
  char testMsgBuf[256];

  const char* testPath=loadTestData(&status);

  icu = ures_open(NULL, "root", &status);
  if(U_FAILURE(status))
  { 
     log_err("%s:%d: Couldn't open root ICU bundle- %s", __FILE__, __LINE__, u_errorName(status));
     return;
  }
  /*  log_info("Open icu root: %s size_%d\n", u_errorName(status), ures_getSize(icu)); */
  status = U_ZERO_ERROR;
  
  app = ures_open(testPath, "root", &status);
  if(U_FAILURE(status))
  { 
     log_err("%s:%d: Couldn't open app ICU bundle [%s]- %s", __FILE__, __LINE__, testPath, u_errorName(status));
     return;
  }
  /* log_info("Open  app: %s, size %d\n", u_errorName(status), ures_getSize(app)); */

  tmp = ures_getByKey(icu, "Version", tmp, &status);
  if(U_FAILURE(status))
  { 
     log_err("%s:%d: Couldn't get Version string from ICU root bundle- %s", __FILE__, __LINE__, u_errorName(status));
     return;
  }

  icuString =  ures_getString(tmp,  &len, &status);
  if(U_FAILURE(status))
  { 
     log_err("%s:%d: Couldn't get string from Version string from ICU root bundle- %s", __FILE__, __LINE__, u_errorName(status));
     return;
  }
  /* log_info("icuString=%p - %s\n", icuString, austrdup(icuString)); */


  tmp2 = ures_getByKey(app, "Version", tmp2, &status);
  if(U_FAILURE(status))
  { 
    log_err("%s:%d: Couldn't get Version string from App root bundle- %s", __FILE__, __LINE__, u_errorName(status));
     return;
  }

  appString =  ures_getString(tmp2,  &len, &status);
  if(U_FAILURE(status))
  { 
     log_err("%s:%d: Couldn't get string from Version string from App root bundle- %s", __FILE__, __LINE__, u_errorName(status));
     return;
  }

  /* log_info("appString=%p - %s\n", appString, austrdup(appString)); */


  if(!u_strcmp(icuString, appString))
  {
    log_err("%s:%d: Error! Expected ICU and App root version strings to be DIFFERENT but they are both %s and %s\n", __FILE__, __LINE__, austrdup(icuString),
    austrdup(appString));
  }
  else
  {
    log_verbose("%s:%d:  appstr=%s, icustr=%s\n", __FILE__,
      __LINE__, u_austrcpy(testMsgBuf, appString), u_austrcpy(testMsgBuf, icuString));
  }

  ures_close(tmp);
  ures_close(tmp2);
  ures_close(icu);
  ures_close(app);
}