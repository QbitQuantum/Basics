void
__gnat_kill (int pid, int sig, int close)
{
  HANDLE h = OpenProcess (PROCESS_ALL_ACCESS, FALSE, pid);
  if (h == NULL)
    return;
  if (sig == 9)
    {
      TerminateProcess (h, 0);
      __gnat_win32_remove_handle (NULL, pid);
    }
  else if (sig == SIGINT)
    GenerateConsoleCtrlEvent (CTRL_C_EVENT, pid);
  else if (sig == SIGBREAK)
    GenerateConsoleCtrlEvent (CTRL_BREAK_EVENT, pid);
  /* ??? The last two alternatives don't really work. SIGBREAK requires setting
     up process groups at start time which we don't do; treating SIGINT is just
     not possible apparently. So we really only support signal 9. Fortunately
     that's all we use in GNAT.Expect */

  CloseHandle (h);
}