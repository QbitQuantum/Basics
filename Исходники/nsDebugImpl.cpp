NS_IMETHODIMP 
nsDebugImpl::Abort(const char *aFile, PRInt32 aLine)
{
  InitLog();

   PR_LOG(gDebugLog, PR_LOG_ERROR, 
         ("###!!! Abort: at file %s, line %d", aFile, aLine));
   PR_LogFlush();
   fprintf(stderr, "\07 Abort\n");  fflush(stderr);
   fflush(stderr);

#if defined(_WIN32)
#ifdef _M_IX86
  long* __p = (long*) 0x7;
  *__p = 0x7;
#else /* _M_ALPHA */
  PR_Abort();
#endif
#elif defined(XP_MAC)
  ExitToShell();
#elif defined(XP_UNIX)
  PR_Abort();
#elif defined(XP_OS2)
  DebugBreak();
  return NS_OK;
#elif defined(XP_BEOS)
  {
#ifndef DEBUG_cls
	char buf[2000];
	sprintf(buf, "Abort: at file %s, line %d", aFile, aLine);
	DEBUGGER(buf);
#endif
  } 
#endif
  return NS_OK;
}