/* Send an interrupt request to the inferior process. */
static void
win32_request_interrupt (void)
{
  winapi_DebugBreakProcess DebugBreakProcess;
  winapi_GenerateConsoleCtrlEvent GenerateConsoleCtrlEvent;

#ifdef _WIN32_WCE
  HMODULE dll = GetModuleHandle (_T("COREDLL.DLL"));
#else
  HMODULE dll = GetModuleHandle (_T("KERNEL32.DLL"));
#endif

  GenerateConsoleCtrlEvent = GETPROCADDRESS (dll, GenerateConsoleCtrlEvent);

  if (GenerateConsoleCtrlEvent != NULL
      && GenerateConsoleCtrlEvent (CTRL_BREAK_EVENT, current_process_id))
    return;

  /* GenerateConsoleCtrlEvent can fail if process id being debugged is
     not a process group id.
     Fallback to XP/Vista 'DebugBreakProcess', which generates a
     breakpoint exception in the interior process.  */

  DebugBreakProcess = GETPROCADDRESS (dll, DebugBreakProcess);

  if (DebugBreakProcess != NULL
      && DebugBreakProcess (current_process_handle))
    return;

  /* Last resort, suspend all threads manually.  */
  soft_interrupt_requested = 1;
}