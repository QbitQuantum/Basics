/* This function does file handle black magic.  Here, we create pipes,
   duplicate the ones we're going to pass on to the child process, and
   set the current process's stdin and stdout to be those pipes.  (###
   I'm not sure duplicating them is necessary, but it doesn't hurt...)

   inpipes, outpipes, and old_handles are 2 element arrays.  */
static void pipe_setup (STARTUPINFO *siStartInfo, int inpipes[], 
			int outpipes[], HANDLE old_handles[])
{
  const int pipe_size = 2000;
  HANDLE new_stdin, new_stdout;
  HANDLE parent = GetCurrentProcess();

  /* Create new file handles--in binary mode.
     _pipe sticks the read then the write handle in {in,out}pipes, and
     returns 0 on success and -1 on failure */
  if (_pipe(inpipes, pipe_size, O_BINARY) != 0
      || _pipe(outpipes, pipe_size, O_BINARY) != 0

      /* Duplicate the stdin and stdout handles.  False on failure. */
      || !DuplicateHandle(parent, /* source process */
			  /* next, handle to dup */
			  (HANDLE) _get_osfhandle(inpipes[0]),
			  parent,  /* Proc to give new handles to */
			  &new_stdin, /* Where new handle is stored */
			  0,  /* Parameter ignored */
			  TRUE, /* Make new handle inheritable */
			  DUPLICATE_SAME_ACCESS)
      || !DuplicateHandle(parent,  /* source process */
			  /* next, handle to dup */
			  (HANDLE)_get_osfhandle(outpipes[1]),
			  parent,   /* Proc to give new handles to */
			  &new_stdout,  /* Where new handle is stored */
			  0,  /* Parameter ignored */
			  TRUE, /* Make new handle inheritable */
			  DUPLICATE_SAME_ACCESS)) {
    fprintf(stderr, "Failed while doing pipe stuff for fd_exec");
    exit(1);
  }

  /* Save the old stdin and stdout handles to some place we can remember */
  old_handles[0] = GetStdHandle(STD_INPUT_HANDLE);
  old_handles[1] = GetStdHandle(STD_OUTPUT_HANDLE);

  /* Set stdin and stdout to the new handles */
  if (!SetStdHandle(STD_INPUT_HANDLE, new_stdin)
      || !SetStdHandle(STD_OUTPUT_HANDLE, new_stdout)) {
    fprintf(stderr, "Failed while doing pipe stuff for fd_exec");
    exit(1);
  }

  /* Now tell the StartInfo to use the handles we just created.  By
     default, child processes don't inherit the stdin and stdout of
     their parents. */
  siStartInfo->dwFlags = STARTF_USESTDHANDLES;
  siStartInfo->hStdInput = new_stdin;
  siStartInfo->hStdOutput = new_stdout;

  /* nothing funny with stderr, but we still have to initialize 
     the field anyway */
  siStartInfo->hStdError = GetStdHandle(STD_ERROR_HANDLE);
}