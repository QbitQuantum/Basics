/* Start an Erlang node. return value 0 indicates that node was
 * started successfully, negative values indicate error. 
 * 
 * node -  the name of the remote node to start (alivename@hostname).
 * flags - turn on or off certain options. See erl_start.h for a list.
 * erl -  is the name of the erl script to call. If NULL, the default
 * name "erl" will be used.
 * args - a NULL-terminated list of strings containing
 * additional arguments to be sent to the remote Erlang node. These
 * strings are simply appended to the end of the command line, so any
 * quoting of special characters, etc must be done by the caller.
 * There may be some conflicts between some of these arguments and the
 * default arguments hard-coded into this function, so be careful. 
 */
int erl_start_sys(ei_cnode *ec, char *alive, Erl_IpAddr adr, int flags,
		  char *erl, char *args[])
{
  struct timeval timeout;
  struct sockaddr_in addr;
  SocklenType namelen;
  int port;
  int sockd = 0;
  int one = 1;
#if defined(VXWORKS) || defined(__WIN32__)
  unsigned long pid = 0;
#else
  int pid = 0;
#endif
  int r = 0;

  if (((sockd = socket(AF_INET, SOCK_STREAM, 0)) < 0) ||
      (setsockopt(sockd, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(one)) < 0)) {
    r = ERL_SYS_ERROR;
    goto done;
  }

  memset(&addr,0,sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = 0;

  if (bind(sockd,(struct sockaddr *)&addr,sizeof(addr))<0) {
      return ERL_SYS_ERROR;
  }
  namelen = sizeof(addr);
  if (getsockname(sockd,(struct sockaddr *)&addr,&namelen)<0) {
      return ERL_SYS_ERROR;
  }
  port = ntohs(addr.sin_port);

  listen(sockd,5);

#if defined(VXWORKS) || defined(__WIN32__)
  if((pid = spawn_erlang_epmd(ec,alive,adr,flags,erl,args,port,1))
      == 0)
     return ERL_SYS_ERROR;
  timeout.tv_usec = 0;
  timeout.tv_sec = 10; /* ignoring ERL_START_TIME */
  if((r = wait_for_erlang(sockd,unique_id(),&timeout))
     == ERL_TIMEOUT) {
#if defined(VXWORKS)
      taskDelete((int) pid);
      if(taskIdVerify((int) pid) != ERROR)
	  taskDeleteForce((int) pid);
#else /* Windows */
      /* Well, this is not a nice way to do it, and it does not 
	 always kill the emulator, but the alternatives are few.*/
      TerminateProcess((HANDLE) pid,1);
#endif /* defined(VXWORKS) */
  }
#else /* Unix */
  switch ((pid = fork())) {
  case -1:
    r = ERL_SYS_ERROR;
    break;

  case 0:
    /* child - start the erlang node */
    exec_erlang(ec, alive, adr, flags, erl, args, port);

    /* error if reached - parent reports back to caller after timeout
       so we just exit here */
    exit(1);
    break;

  default:

    /* parent - waits for response from Erlang node */
    /* child pid used here as magic number */
    timeout.tv_usec = 0;
    timeout.tv_sec = 10; /* ignoring ERL_START_TIME */
    if ((r = wait_for_erlang(sockd,pid,&timeout)) == ERL_TIMEOUT) {
      /* kill child if no response */
      kill(pid,SIGINT);
      sleep(1);
      if (waitpid(pid,NULL,WNOHANG) != pid) {
	/* no luck - try harder */
	kill(pid,SIGKILL);
	sleep(1);
	waitpid(pid,NULL,WNOHANG);
      }
    }

  }
#endif /* defined(VXWORKS) || defined(__WIN32__) */

done:
#if defined(__WIN32__)
  if (sockd) closesocket(sockd);
#else
  if (sockd) close(sockd);
#endif
  return r;
} /* erl_start_sys() */