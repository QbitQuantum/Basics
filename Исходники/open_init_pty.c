int
main(int argc, char *argv[])
{
  pid_t child_pid;
  struct termios tty_attr;
  struct winsize window_size;
  int pty_master;
  int retval = 0;

  /* for select */
  fd_set readfds;
  fd_set writefds;
  fd_set exceptfds;


  int err_count = 0;

  /* for sigtimedwait() */
  struct timespec timeout;
  char buf[16384];

  if (argc == 1)
    {
      printf("usage: %s PROGRAM [ARGS]...\n", argv[0]);
      exit(1);
    }

  sigset_t  signal_set;
  siginfo_t signalinfo;

  /* set up SIGCHLD */
  sigemptyset(&signal_set);      /* no signals */
  sigaddset(&signal_set, SIGCHLD); /* Add sig child  */
  sigprocmask(SIG_BLOCK, &signal_set, NULL); /* Block the signal */

  /* Set both to 0, so sigtimed wait just does a poll */
  timeout.tv_sec=0;
  timeout.tv_nsec=0;

  if(isatty(fileno(stdin)))
   {
     /* get terminal parameters associated with stdout */
     if(tcgetattr(fileno(stdout), &tty_attr) < 0)
      {
        perror("tcgetattr:");
        exit(EX_OSERR);
      } /* end of if(tcsetattr(&tty_attr)) */

     /* get window size */
     if( ioctl(fileno(stdout), TIOCGWINSZ, &window_size) < 0 ) {
       perror("ioctl stdout:");
       exit(1);
     }

     child_pid = forkpty(&pty_master, NULL, &tty_attr, &window_size);
   } /* end of if(isatty(fileno(stdin))) */
  else
   {                            /* not interactive */
     child_pid = forkpty(&pty_master, NULL, NULL, NULL);
   }

  if(child_pid < 0)
   {
     perror("Fork:");
     fflush(stdout);
     fflush(stderr);
     exit(EX_OSERR);
   } /* end of if(child_pid < 0) */
  if(child_pid == 0)
   {
     /* in the child */
     struct termios s_tty_attr;
     if(tcgetattr(fileno(stdin), &s_tty_attr))
      {
        perror("Child:");
        fflush(stdout);
        fflush(stderr);
        exit(EXIT_FAILURE);
      }
     /* Turn off echo */
     s_tty_attr.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
     /* Also turn of NL to CR?LF on output */
     s_tty_attr.c_oflag &= ~(ONLCR);
     if(tcsetattr(fileno(stdin), TCSANOW, &s_tty_attr))
      {
        perror("Child:");
        exit(EXIT_FAILURE);
      }
     { /* There is no reason to block sigchild for the process we
          shall exec here */
       sigset_t  chld_signal_set;
       /* release SIGCHLD */
       sigemptyset(&chld_signal_set);        /* no signals */
       sigaddset(&chld_signal_set, SIGCHLD); /* Add sig child  */
       sigprocmask(SIG_UNBLOCK, &chld_signal_set, NULL); /* Unblock the signal */
     }

     if ( execvp(argv[1], argv + 1) ) {
       perror("Exec:");
       fflush(stdout);
       fflush(stderr);
       exit(EXIT_FAILURE);
     }
   } /* end of if(child_pid == 0) */

  /* 
   * OK. Prepare to handle IO from the child. We need to transfer
   * everything from the child's stdout to ours.
   */

  FD_ZERO(&readfds);
  FD_ZERO(&writefds);
  FD_ZERO(&exceptfds);

  /*
   * Read current file descriptor flags, preparing to do non blocking reads
   */
  retval=fcntl(pty_master,F_GETFL);
  if(retval<0) {
    perror("fcntl_get");
    fflush(stdout);
    fflush(stderr);
    exit(EX_IOERR);
  }

  /* Set the connection to be non-blocking */
  if(fcntl(pty_master,F_SETFL, retval | O_NONBLOCK) < 0) {
    perror("fcnt_setFlag_nonblock:");
    fflush(stdout);
    fflush(stderr);
    exit(1);
  }

  FD_SET(pty_master, &readfds);
  FD_SET(pty_master, &writefds);
  FD_SET(fileno(stdin), &readfds);
  if(isatty(fileno(stdin)))
   {
     if(tty_semi_raw(fileno(stdin)) < 0)
      {
        perror("Error: settingraw mode:");
        fflush(stdout);
        fflush(stderr);
      } /* end of if(tty_raw(fileno(stdin)) < 0) */
     if(atexit(tty_atexit) < 0)
      {
        perror("Atexit setup:");
        fflush(stdout);
        fflush(stderr);
      } /* end of if(atexit(tty_atexit) < 0) */
   }


  /* ignore return from nice, but lower our priority */
  int ignore __attribute__ ((unused)) = nice(19);

  /* while no signal, we loop around */
  int done = 0;
  while(! done) {
    struct timeval interval;
    fd_set t_readfds;
    fd_set t_writefds;
    fd_set t_exceptfds;
    /*
     * We still use a blocked signal, and check for SIGCHLD every
     * loop, since waiting infinitely did not really help the load
     * when running, say, top. 
     */
    interval.tv_sec  = 0;
    interval.tv_usec = 200000;    /* so, check for signals every 200 milli
                                   seconds */

    t_readfds   = readfds;
    t_writefds  = writefds;
    t_exceptfds = exceptfds;

    /* check for the signal */
    retval = sigtimedwait(&signal_set, &signalinfo,&timeout);

    if( retval == SIGCHLD ) {
      /* child terminated */
      done = 1;                 /* in case they do not close off their
                                   file descriptors */
    }
    else
     {
       if( retval < 0 ) {
         if(errno != EAGAIN) {
           perror("sigtimedwait");
           fflush(stdout);
           fflush(stderr);
           exit(EX_IOERR);
         }
         else
          {
            /* No signal in set was delivered within the timeout period specified */
          }
       }
     } /* end of else */

    if(select (pty_master + 1, &t_readfds, &t_writefds, &t_exceptfds, 
               &interval) < 0)
     {
       perror("Select:");
       fflush(stdout);
       fflush(stderr);
       exit (EX_IOERR);
     }

    if(FD_ISSET(pty_master, &t_readfds))
     {
       retval = read(pty_master, buf, (unsigned int)16384);
       if(retval < 0)
        {
          if(errno != EINTR && errno != EAGAIN) 
           {                    /* Nothing left to read?  */
             fflush(stdout);
             fflush(stderr);
             /* fprintf(stderr, "DEBUG: %d: Nothing left to read?\n", __LINE__);*/
             exit (EXIT_SUCCESS);
           } /* end of else */
        } /* end of if(retval < 0) */
       else
        {
          if(retval == 0)
           {
             if(++err_count > 5)
              {                 /* child closed connection */
                fflush(stdout);
                fflush(stderr);
                /*fprintf(stderr, "DEBUG: %d: child closed connection?\n", __LINE__);*/
                exit (EXIT_SUCCESS);
              }
           } /* end of if(retval == 0) */
          else
           {
             ssize_t  nleft    = retval;
             ssize_t  nwritten = 0;
             char *   ptr      = buf;
             while(nleft > 0)
              {
                if((nwritten = write(fileno(stdout), ptr,
                                     (unsigned int)nleft)) <= 0)
                 {
                   if(errno == EINTR)
                    {
                      nwritten = 0;
                    } /* end of if(errno == EINTR) */
                   else
                    {
                      perror("write");
                      fflush(stdout);
                      fflush(stderr);
                      exit (EXIT_SUCCESS);
                    } /* end of else */
                 } /* end of if((nwritten = write(sockfd, ptr, nleft)) <= 0) */
                nleft -= nwritten;
                ptr += nwritten;
              } /* end of while(nleft > 0) */

             /* fprintf(stderr, "DEBUG: %d: wrote %d\n", __LINE__, retval);*/
             fflush(stdout);
           } /* end of else */
        } /* end of else */
     }
    if(FD_ISSET(fileno(stdin), &t_readfds))
     {
       if(FD_ISSET(pty_master, &t_writefds))
        {
          retval = read(fileno(stdin), buf, (unsigned int)16384);
          if(retval < 0)
           {
             if(errno != EINTR && errno != EAGAIN)
              {                 /* Nothing left to read?  */
                fflush(stdout);
                fflush(stderr);
                exit (EXIT_SUCCESS);
              } /* end of else */
           } /* end of if(retval < 0) */
          else
           {
             if(retval == 0)
              {
                if(++err_count > 5)
                 {              /* lost controlling tty */
                   fflush(stdout);
                   fflush(stderr);
                   exit (EXIT_SUCCESS);
                 }
              } /* end of if(retval == 0) */
             else
              {
                ssize_t  nleft    = retval;
                ssize_t  nwritten = 0;
                char *   ptr      = buf;
                while(nleft > 0)
                 {
                   if((nwritten = write(pty_master, ptr,
                                        (unsigned int)nleft)) <= 0)
                    {
                      if(errno == EINTR)
                       {
                         nwritten = 0;
                       } /* end of if(errno == EINTR) */
                      else
                       {
                         perror("write");
                         fflush(stdout);
                         fflush(stderr);
                         exit (EXIT_SUCCESS);
                       } /* end of else */
                    } /* end of if((nwritten = write(sockfd, ptr, nleft)) <= 0) */
                   nleft -= nwritten;
                   ptr += nwritten;
                 } /* end of while(nleft > 0) */

                fflush(stdout);
              } /* end of else */
           } /* end of else */
        } /* end of if(FD_ISSET(pty_master, &writefds)) */
     }    /* something to read on stdin */
  } /* Loop */

  fflush(stdout);
  fflush(stderr);

  exit(EXIT_SUCCESS);
} /* end of main() */