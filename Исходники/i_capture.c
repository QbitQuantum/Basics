// extra pointer is used to hold process id to wait on to close
// NB: stdin is opened as "wb", stdout, stderr as "r"
int my_popen3 (pipeinfo_t *p)
{
  FILE *fin = NULL;
  FILE *fout = NULL;
  FILE *ferr = NULL;
  HANDLE child_hin = INVALID_HANDLE_VALUE;
  HANDLE child_hout = INVALID_HANDLE_VALUE;
  HANDLE child_herr = INVALID_HANDLE_VALUE;
  HANDLE parent_hin = INVALID_HANDLE_VALUE;
  HANDLE parent_hout = INVALID_HANDLE_VALUE;
  HANDLE parent_herr = INVALID_HANDLE_VALUE;


  puser_t *puser = NULL;


  PROCESS_INFORMATION piProcInfo;
  STARTUPINFO siStartInfo;
  SECURITY_ATTRIBUTES sa;

  puser = malloc (sizeof (puser_t));
  if (!puser)
    return 0;

  puser->proc = INVALID_HANDLE_VALUE;
  puser->thread = INVALID_HANDLE_VALUE;


  // make the pipes

  sa.nLength = sizeof (sa);
  sa.bInheritHandle = 1;
  sa.lpSecurityDescriptor = NULL;
  if (!CreatePipe (&child_hin, &parent_hin, &sa, 0))
    goto fail;
  if (!CreatePipe (&parent_hout, &child_hout, &sa, 0))
    goto fail;
  if (!CreatePipe (&parent_herr, &child_herr, &sa, 0))
    goto fail;


  // very important
  if (!SetHandleInformation (parent_hin, HANDLE_FLAG_INHERIT, 0))
    goto fail;
  if (!SetHandleInformation (parent_hout, HANDLE_FLAG_INHERIT, 0))
    goto fail;
  if (!SetHandleInformation (parent_herr, HANDLE_FLAG_INHERIT, 0))
    goto fail;




  // start the child process

  ZeroMemory (&siStartInfo, sizeof (STARTUPINFO));
  siStartInfo.cb         = sizeof (STARTUPINFO);
  siStartInfo.hStdInput  = child_hin;
  siStartInfo.hStdOutput = child_hout;
  siStartInfo.hStdError  = child_herr;
  siStartInfo.dwFlags    = STARTF_USESTDHANDLES;

  if (!CreateProcess(NULL,// application name
       (LPTSTR)p->command,// command line
       NULL,              // process security attributes
       NULL,              // primary thread security attributes
       TRUE,              // handles are inherited
       DETACHED_PROCESS,  // creation flags
       NULL,              // use parent's environment
       NULL,              // use parent's current directory
       &siStartInfo,      // STARTUPINFO pointer
       &piProcInfo))      // receives PROCESS_INFORMATION
  {
    goto fail;
  }



  puser->proc = piProcInfo.hProcess;
  puser->thread = piProcInfo.hThread;


                                // what the hell is this cast for
  if (NULL == (fin = _fdopen (_open_osfhandle ((int) parent_hin, 0), "wb")))
    goto fail;
  if (NULL == (fout = _fdopen (_open_osfhandle ((int) parent_hout, 0), "r")))
    goto fail;
  if (NULL == (ferr = _fdopen (_open_osfhandle ((int) parent_herr, 0), "r")))
    goto fail;
  // after fdopen(osf()), we don't need to keep track of parent handles anymore
  // fclose on the FILE struct will automatically free them


  p->user = puser;
  p->f_stdin = fin;
  p->f_stdout = fout;
  p->f_stderr = ferr;

  CloseHandle (child_hin);
  CloseHandle (child_hout);
  CloseHandle (child_herr);

  return 1;

  fail:
  if (fin)
    fclose (fin);
  if (fout)
    fclose (fout);
  if (ferr)
    fclose (ferr);

  if (puser->proc)
    CloseHandle (puser->proc);
  if (puser->thread)
    CloseHandle (puser->thread);

  if (child_hin != INVALID_HANDLE_VALUE)
    CloseHandle (child_hin);
  if (child_hout != INVALID_HANDLE_VALUE)
    CloseHandle (child_hout);
  if (child_herr != INVALID_HANDLE_VALUE)
    CloseHandle (child_herr);
  if (parent_hin != INVALID_HANDLE_VALUE)
    CloseHandle (parent_hin);
  if (parent_hout != INVALID_HANDLE_VALUE)
    CloseHandle (parent_hout);
  if (parent_herr != INVALID_HANDLE_VALUE)
    CloseHandle (parent_herr);

  free (puser);

  return 0;


}