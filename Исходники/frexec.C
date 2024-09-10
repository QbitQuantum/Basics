static bool fork_program(char **arglist, int &pipe_in, int &pipe_out)
{
#if defined(MSDOS) || defined(__MSDOS__) || defined(__WINDOWS__) || defined(__NT__)
  FrWarning("Sorry, fork() is not available under MS-DOS or Windoze.\n"
	    "Change the program's configuration to indicate a socket number\n"
	    "other than -1 to permit the use of "
#ifdef FrUSING_POPEN
	    "popen"
#else
	    "spawn"
#endif /* FrUSING_POPEN */
	    "(), which IS supported.") ;
  (void)arglist ; (void)pipe_in ; (void)pipe_out ;
  return false ;
#else
  int pipe_desc[2] ;
  pipe_desc[0] = EOF ;
  pipe_desc[1] = EOF ;
  errno = 0 ;
  int pipe_stat = pipe( pipe_desc ) ;
  if (pipe_stat)
     {
     if (pipe_desc[0] != EOF) close(pipe_desc[0]) ;
     if (pipe_desc[1] != EOF) close(pipe_desc[1]) ;
     FrErrorVA("bad write pipe (errno=%d: %s)",errno,strerror(errno)) ;
     return false ;
     }
  int pipe_in_child = pipe_desc[0] ;
  int pipe_out_parent = pipe_desc[1] ;
  errno = 0 ;
  pipe_stat = pipe( pipe_desc ) ;
  if (pipe_stat)
     {
     close(pipe_in_child) ;
     close(pipe_out_parent) ;
     if (pipe_desc[0] != EOF && pipe_desc[0] != pipe_in_child)
	(void)close(pipe_desc[0]) ;
     if (pipe_desc[1] != EOF && pipe_desc[1] != pipe_out_parent)
	(void)close(pipe_desc[1]) ;
     FrErrorVA("bad read pipe (errno=%d: %s)",errno,strerror(errno)) ;
     return false ;
     }
  int pipe_in_parent = pipe_desc[0] ;
  int pipe_out_child = pipe_desc[1] ;

  errno = 0 ;
  int pid = fork() ;
  if (pid == -1)
     {
     close(pipe_in_parent) ;
     close(pipe_in_child) ;
     close(pipe_out_parent) ;
     close(pipe_out_child) ;
     FrErrorVA("unable to fork %s (errno=%d)",arglist[0],errno) ;
     return false ;
     }
  else if (pid == 0)
     {
     dup2( pipe_in_child, 0 ) ;	  // put the read end of the pipe on stdin
     dup2( pipe_out_child, 1 ) ;  // put the write end of the pipe on stdout
//   dup2( 1, 2 ) ;		  // also put stderr thru the pipe
     if (!FramepaC_verbose)
	{
	close(2) ;
	open(FrNULL_DEVICE,O_WRONLY) ;
	}
     close(pipe_in_child) ;
     close(pipe_out_child) ;
     close( pipe_in_parent ) ;	 // close the unused ends of the pipes
     close( pipe_out_parent ) ;
     errno = 0 ;
     execvp( arglist[0], arglist) ;
     // not reached except when error
     FrErrorVA("couldn't exec program %s (errno=%d) -- check configuration file",
	       arglist[0],errno) ;
     return false ;
     }
  else
     {
     close(pipe_in_child) ;	// close the unused ends of the pipes
     close(pipe_out_child) ;
     pipe_in = pipe_in_parent ;
     pipe_out = pipe_out_parent ;
     set_child_pid(pid) ;
     }
  return true ;
#endif /* __WINDOWS__ || __NT__ */
}