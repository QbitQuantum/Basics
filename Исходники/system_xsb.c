/* spawn a subprocess PROGNAME and pass it the arguments ARGV[]
   ARGV must be a NULL-terminated array of strings.
   Also pass it two arrays of strings: PIPE_TO_PROC[2] and PIPE_FROM_PROC[2].
   These are going to be the arrays of fds for the communication pipes 

   This function is protected from being called by more than one
   thread at a time by a mutex: the context is passed in for error handling.
*/
static int xsb_spawn (CTXTdeclc char *progname, char *argv[], int callno,
		      int pipe_to_proc[],
		      int pipe_from_proc[],int pipe_from_stderr[],
		      FILE *toprocess_fptr, FILE *fromprocess_fptr,
		      FILE *fromproc_stderr_fptr)
{
  int pid;
  int stdin_saved, stdout_saved, stderr_saved;
  static char shell_command[MAX_CMD_LEN];

  if ( (pipe_to_proc != NULL) && PIPE(pipe_to_proc) < 0 ) {
    /* can't open pipe to process */
    xsb_warn("[SPAWN_PROCESS] Can't open pipe for subprocess input");
    return PIPE_TO_PROC_FAILED;
  }
  if ( (pipe_from_proc != NULL) && PIPE(pipe_from_proc) < 0 ) {
    /* can't open pipe from process */
    xsb_warn("[SPAWN_PROCESS] Can't open pipe for subprocess output");
    return PIPE_FROM_PROC_FAILED;
  }
  if ( (pipe_from_stderr != NULL) && PIPE(pipe_from_stderr) < 0 ) {
    /* can't open stderr pipe from process */
    xsb_warn("[SPAWN_PROCESS] Can't open pipe for subprocess errors");
    return PIPE_FROM_PROC_FAILED;
  }

  /* The following is due to the awkwardness of windoze process creation.
     We commit this atrocity in order to be portable between Unix and Windows.
     1. Save stdio of the parent process.
     2. Redirect main process stdio to the pipes.
     3. Spawn subprocess. The subprocess inherits the redirected I/O
     4. Restore the original stdio for the parent process.

     On the bright side, this trick allowed us to cpature the I/O streams of
     the shell commands invoked by system()
  */

  /* save I/O */
  stdin_saved  = dup(fileno(stdin));
  stdout_saved = dup(fileno(stdout));
  stderr_saved = dup(fileno(stderr));
  if ((fileno(stdin) < 0) || (stdin_saved < 0))
    xsb_warn("[SPAWN_PROCESS] Bad stdin=%d; stdin closed by mistake?",
	     fileno(stdin));
  if ((fileno(stdout) < 0) || (stdout_saved < 0))
    xsb_warn("[SPAWN_PROCESS] Bad stdout=%d; stdout closed by mistake?",
	     fileno(stdout));
  if ((fileno(stderr) < 0) || (stderr_saved < 0))
    xsb_warn("[SPAWN_PROCESS] Bad stderr=%d; stderr closed by mistake?",
	     fileno(stderr));

  if (pipe_to_proc != NULL) {
    /* close child stdin, bind it to the reading part of pipe_to_proc */
    if (dup2(pipe_to_proc[0], fileno(stdin)) < 0) {
      xsb_warn("[SPAWN_PROCESS] Can't connect pipe %d to subprocess stdin",
	       pipe_to_proc[0]);
      return PIPE_TO_PROC_FAILED;
    }
    close(pipe_to_proc[0]); /* close the parent read end of pipe */
  }
  /* if stdin must be captured in an existing I/O port -- do it */
  if (toprocess_fptr != NULL)
    if (dup2(fileno(toprocess_fptr), fileno(stdin)) < 0) {
      xsb_warn("[SPAWN_PROCESS] Can't connect stream %d to subprocess stdin",
	       fileno(toprocess_fptr));
      return PIPE_TO_PROC_FAILED;
    }
  
  if (pipe_from_proc != NULL) {
    /* close child stdout, bind it to the write part of pipe_from_proc */
    if (dup2(pipe_from_proc[1], fileno(stdout)) < 0) {
      xsb_warn("[SPAWN_PROCESS] Can't connect subprocess stdout to pipe %d",
	       pipe_from_proc[1]);
      return PIPE_TO_PROC_FAILED;
    }
    close(pipe_from_proc[1]); /* close the parent write end of pipe */
  }
  /* if stdout must be captured in an existing I/O port -- do it */
  if (fromprocess_fptr != NULL)
    if (dup2(fileno(fromprocess_fptr), fileno(stdout)) < 0) {
      xsb_warn("[SPAWN_PROCESS] Can't connect subprocess stdout to stream %d",
	       fileno(fromprocess_fptr));
      return PIPE_TO_PROC_FAILED;
    }

  if (pipe_from_stderr != NULL) {
    /* close child stderr, bind it to the write part of pipe_from_proc */
    if (dup2(pipe_from_stderr[1], fileno(stderr)) < 0) {
      xsb_warn("[SPAWN_PROCESS] Can't connect subprocess stderr to pipe %d",
	       pipe_from_stderr[1]);
      return PIPE_TO_PROC_FAILED;
    }
    close(pipe_from_stderr[1]); /* close the parent write end of pipe */
  }
  /* if stderr must be captured in an existing I/O port -- do it */
  if (fromproc_stderr_fptr != NULL)
    if (dup2(fileno(fromproc_stderr_fptr), fileno(stderr)) < 0) {
      xsb_warn("[SPAWN_PROCESS] Can't connect subprocess stderr to stream %d",
	       fileno(fromproc_stderr_fptr));
      return PIPE_TO_PROC_FAILED;
    }

  if (callno == SPAWN_PROCESS) {
#ifdef WIN_NT

    static char bufQuoted[MAX_CMD_LEN + 2*(MAX_SUBPROC_PARAMS + 2)];
    const char * argvQuoted[MAX_SUBPROC_PARAMS + 2];
    char *  argq = bufQuoted;
    char *  arge = bufQuoted + sizeof(bufQuoted);
    char ** argp = argv;
    size_t  len  = 0; 
    int     i;

    for (i = 0; i < MAX_SUBPROC_PARAMS + 2; ++i) {
      if (*argp && (argq + (len = strlen(*argp)) + 4 < arge)) {
         argvQuoted[i] = argq;
         *argq++ = '"';
         strncpy(argq, *argp, len);
         argq += len;
         *argq++ = '"';
         *argq++ = '\0';
         ++argp;
      } else {
         *argq = '\0';
         argvQuoted[i] = 0;
         break;
      }
    }
    pid = (int)_spawnvp(P_NOWAIT, progname, argvQuoted); // should pid be Integer?
#else
    pid = fork();
#endif

    if (pid < 0) {
      /* failed */
      xsb_warn("[SPAWN_PROCESS] Can't fork off subprocess");
      return pid;
    } else if (pid == 0) {
      /* child process */

      /* Close the writing side of child's in-pipe. Must do this or else the
	 child won't see EOF when parent closes its end of this pipe. */
      if (pipe_to_proc != NULL) close(pipe_to_proc[1]);
      /* Close the reading part of child's out-pipe and stderr-pipe */
      if (pipe_from_proc != NULL) close(pipe_from_proc[0]);
      if (pipe_from_stderr != NULL) close(pipe_from_stderr[0]);
      
#ifndef WIN_NT  /* Unix: must exec */
      execvp(progname, argv);
      /* if we ever get here, this means that invocation of the process has
	 failed */
      exit(SUB_PROC_FAILED);
#endif
    }
  } else { /* SHELL command */
    /* no separator */
    concat_array(CTXTc argv, "", shell_command, MAX_CMD_LEN);
    pid = system(shell_command);
  }

  /* main process continues */

  /* duplicate saved copies of stdio fds back into main process stdio */
  if (dup2(stdin_saved, fileno(stdin)) < 0) {
    perror("SPAWN_PROCESS");
    close(stdin_saved); close(stdout_saved); close(stderr_saved);
    return PIPE_TO_PROC_FAILED;
  }
  if (dup2(stdout_saved, fileno(stdout)) < 0) {
    perror("SPAWN_PROCESS");
    close(stdin_saved); close(stdout_saved); close(stderr_saved);
    return PIPE_TO_PROC_FAILED;
  }
  if (dup2(stderr_saved, fileno(stderr)) < 0) {
    perror("SPAWN_PROCESS");
    close(stdin_saved); close(stdout_saved); close(stderr_saved);
    return PIPE_TO_PROC_FAILED;
  }

  close(stdin_saved); close(stdout_saved); close(stderr_saved);
  return pid;
}