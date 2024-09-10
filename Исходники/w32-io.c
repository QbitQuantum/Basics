int
_gpgme_io_spawn (const char *path, char *const argv[], unsigned int flags,
		 struct spawn_fd_item_s *fd_list,
		 void (*atfork) (void *opaque, int reserved),
		 void *atforkvalue, pid_t *r_pid)
{
  SECURITY_ATTRIBUTES sec_attr;
  PROCESS_INFORMATION pi =
    {
      NULL,      /* returns process handle */
      0,         /* returns primary thread handle */
      0,         /* returns pid */
      0          /* returns tid */
    };
  STARTUPINFO si;
  int cr_flags = (CREATE_DEFAULT_ERROR_MODE
                  | GetPriorityClass (GetCurrentProcess ()));
  int i;
  char **args;
  char *arg_string;
  /* FIXME.  */
  int debug_me = 0;
  int tmp_fd;
  char *tmp_name;

  TRACE_BEG1 (DEBUG_SYSIO, "_gpgme_io_spawn", path,
	      "path=%s", path);
  i = 0;
  while (argv[i])
    {
      TRACE_LOG2 ("argv[%2i] = %s", i, argv[i]);
      i++;
    }

  /* We do not inherit any handles by default, and just insert those
     handles we want the child to have afterwards.  But some handle
     values occur on the command line, and we need to move
     stdin/out/err to the right location.  So we use a wrapper program
     which gets the information from a temporary file.  */
  if (_gpgme_mkstemp (&tmp_fd, &tmp_name) < 0)
    {
      TRACE_LOG1 ("_gpgme_mkstemp failed: %s", strerror (errno));
      return TRACE_SYSRES (-1);
    }
  TRACE_LOG1 ("tmp_name = %s", tmp_name);

  args = calloc (2 + i + 1, sizeof (*args));
  args[0] = (char *) _gpgme_get_w32spawn_path ();
  args[1] = tmp_name;
  args[2] = path;
  memcpy (&args[3], &argv[1], i * sizeof (*args));

  memset (&sec_attr, 0, sizeof sec_attr);
  sec_attr.nLength = sizeof sec_attr;
  sec_attr.bInheritHandle = FALSE;
 
  arg_string = build_commandline (args);
  free (args);
  if (!arg_string)
    {
      close (tmp_fd);
      DeleteFile (tmp_name);
      return TRACE_SYSRES (-1);
    }

  memset (&si, 0, sizeof si);
  si.cb = sizeof (si);
  si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
  si.wShowWindow = debug_me ? SW_SHOW : SW_HIDE;
  si.hStdInput = INVALID_HANDLE_VALUE;
  si.hStdOutput = INVALID_HANDLE_VALUE;
  si.hStdError = INVALID_HANDLE_VALUE;

  cr_flags |= CREATE_SUSPENDED; 
  cr_flags |= DETACHED_PROCESS;
  if (!CreateProcessA (_gpgme_get_w32spawn_path (),
		       arg_string,
		       &sec_attr,     /* process security attributes */
		       &sec_attr,     /* thread security attributes */
		       FALSE,         /* inherit handles */
		       cr_flags,      /* creation flags */
		       NULL,          /* environment */
		       NULL,          /* use current drive/directory */
		       &si,           /* startup information */
		       &pi))          /* returns process information */
    {
      TRACE_LOG1 ("CreateProcess failed: ec=%d", (int) GetLastError ());
      free (arg_string);
      close (tmp_fd);
      DeleteFile (tmp_name);

      /* FIXME: Should translate the error code.  */
      errno = EIO;
      return TRACE_SYSRES (-1);
    }

  free (arg_string);

  if (flags & IOSPAWN_FLAG_ALLOW_SET_FG)
    _gpgme_allow_set_foreground_window ((pid_t)pi.dwProcessId);

  /* Insert the inherited handles.  */
  for (i = 0; fd_list[i].fd != -1; i++)
    {
      HANDLE hd;

      /* Make it inheritable for the wrapper process.  */
      if (!DuplicateHandle (GetCurrentProcess(), fd_to_handle (fd_list[i].fd),
			    pi.hProcess, &hd, 0, TRUE, DUPLICATE_SAME_ACCESS))
	{
	  TRACE_LOG1 ("DuplicateHandle failed: ec=%d", (int) GetLastError ());
	  TerminateProcess (pi.hProcess, 0);
	  /* Just in case TerminateProcess didn't work, let the
	     process fail on its own.  */
	  ResumeThread (pi.hThread);
	  CloseHandle (pi.hThread);
	  CloseHandle (pi.hProcess);

	  close (tmp_fd);
	  DeleteFile (tmp_name);

	  /* FIXME: Should translate the error code.  */
	  errno = EIO;
	  return TRACE_SYSRES (-1);
        }
      /* Return the child name of this handle.  */
      fd_list[i].peer_name = handle_to_fd (hd);
    }
  
  /* Write the handle translation information to the temporary
     file.  */
  {
    /* Hold roughly MAX_TRANS quadruplets of 64 bit numbers in hex
       notation: "0xFEDCBA9876543210" with an extra white space after
       every quadruplet.  10*(19*4 + 1) - 1 = 769.  This plans ahead
       for a time when a HANDLE is 64 bit.  */
#define BUFFER_MAX 810
    char line[BUFFER_MAX + 1];
    int res;
    int written;
    size_t len;

    if ((flags & IOSPAWN_FLAG_ALLOW_SET_FG))
      strcpy (line, "~1 \n");
    else
      strcpy (line, "\n");
    for (i = 0; fd_list[i].fd != -1; i++)
      {
	/* Strip the newline.  */
	len = strlen (line) - 1;
	
	/* Format is: Local name, stdin/stdout/stderr, peer name, argv idx.  */
	snprintf (&line[len], BUFFER_MAX - len, "0x%x %d 0x%x %d  \n",
		  fd_list[i].fd, fd_list[i].dup_to,
		  fd_list[i].peer_name, fd_list[i].arg_loc);
	/* Rather safe than sorry.  */
	line[BUFFER_MAX - 1] = '\n';
	line[BUFFER_MAX] = '\0';
      }
    len = strlen (line);
    written = 0;
    do
      {
	res = write (tmp_fd, &line[written], len - written);
	if (res > 0)
	  written += res;
      }
    while (res > 0 || (res < 0 && errno == EAGAIN));
  }
  close (tmp_fd);
  /* The temporary file is deleted by the gpgme-w32spawn process
     (hopefully).  */

  TRACE_LOG4 ("CreateProcess ready: hProcess=%p, hThread=%p, "
	      "dwProcessID=%d, dwThreadId=%d",
	      pi.hProcess, pi.hThread, 
	      (int) pi.dwProcessId, (int) pi.dwThreadId);
  
  if (r_pid)
    *r_pid = (pid_t)pi.dwProcessId;

  
  if (ResumeThread (pi.hThread) < 0)
    TRACE_LOG1 ("ResumeThread failed: ec=%d", (int) GetLastError ());
  
  if (!CloseHandle (pi.hThread))
    TRACE_LOG1 ("CloseHandle of thread failed: ec=%d",
		(int) GetLastError ());

  TRACE_LOG1 ("process=%p", pi.hProcess);

  /* We don't need to wait for the process.  */
  if (!CloseHandle (pi.hProcess))
    TRACE_LOG1 ("CloseHandle of process failed: ec=%d",
		(int) GetLastError ());

  if (! (flags & IOSPAWN_FLAG_NOCLOSE))
    {
      for (i = 0; fd_list[i].fd != -1; i++)
	_gpgme_io_close (fd_list[i].fd);
    }

  for (i = 0; fd_list[i].fd != -1; i++)
    if (fd_list[i].dup_to == -1)
      TRACE_LOG3 ("fd[%i] = 0x%x -> 0x%x", i, fd_list[i].fd,
		  fd_list[i].peer_name);
    else
      TRACE_LOG4 ("fd[%i] = 0x%x -> 0x%x (std%s)", i, fd_list[i].fd,
		  fd_list[i].peer_name, (fd_list[i].dup_to == 0) ? "in" :
		  ((fd_list[i].dup_to == 1) ? "out" : "err"));

  return TRACE_SYSRES (0);
}