/**
 * Handles exceptions (useful for debugging).
 * Issues a DebugBreak() call if the process is being debugged (not really
 * useful - if the process is being debugged, this handler won't be invoked
 * anyway). If it is not, runs a debugger from GNUNET_DEBUGGER env var,
 * substituting first %u in it for PID, and the second one for the event,
 * that should be set once the debugger attaches itself (otherwise the
 * only way out of WaitForSingleObject() is to time out after 1 minute).
 */
LONG __stdcall
GNWinVEH (PEXCEPTION_POINTERS ExceptionInfo)
{
  char debugger[MAX_PATH + 1];
  char *debugger_env = NULL;
  if (IsDebuggerPresent ())
  {
    DebugBreak ();
    return EXCEPTION_CONTINUE_EXECUTION;
  }
  debugger_env = getenv ("GNUNET_DEBUGGER");
  if (debugger_env != NULL)
  {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    HANDLE event;
    SECURITY_ATTRIBUTES sa;
    memset (&si, 0, sizeof (si));
    si.cb = sizeof (si);
    memset (&pi, 0, sizeof (pi));
    memset (&sa, 0, sizeof (sa));
    sa.nLength = sizeof (sa);
    sa.bInheritHandle = TRUE;
    event = CreateEvent (&sa, FALSE, FALSE, NULL);
    snprintf (debugger, MAX_PATH + 1, debugger_env, GetCurrentProcessId (), (uintptr_t) event);
    debugger[MAX_PATH] = '\0';
    if (0 != CreateProcessA (NULL, debugger, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
      CloseHandle (pi.hProcess);
      CloseHandle (pi.hThread);
      WaitForSingleObject (event, 60000);
      CloseHandle (event);
      if (IsDebuggerPresent ())
      {
        return EXCEPTION_CONTINUE_EXECUTION;
      }
    }
    else
      CloseHandle (event);
  }
  return EXCEPTION_CONTINUE_SEARCH;
}