static BOOL
resume_process (DWORD dwOwnerPID)
{
  HANDLE        hThreadSnap = NULL;
  BOOL          bRet        = FALSE;
  THREADENTRY32 te32        = { 0 };

  hThreadSnap = CreateToolhelp32Snapshot (TH32CS_SNAPTHREAD, 0);
  if (hThreadSnap == INVALID_HANDLE_VALUE)
    return FALSE;

  te32.dwSize = sizeof (THREADENTRY32);

  if (Thread32First (hThreadSnap, &te32))
    {
      do
        {
          if (te32.th32OwnerProcessID == dwOwnerPID)
            {
              HANDLE hThread = OpenThread (THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
              printf ("Resuming Thread: %u\n",te32.th32ThreadID);
              ResumeThread (hThread);
              CloseHandle (hThread);
            }
        }
      while (Thread32Next (hThreadSnap, &te32));
      bRet = TRUE;
    }
  else
    bRet = FALSE;

  CloseHandle (hThreadSnap);

  return bRet;
}