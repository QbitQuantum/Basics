int
main(int argc, char *argv[])
{
  fd_set rfds;                  /* the structure for the select call */
  int code;                    /* return code from system calls */
  char out_buff[MAXLINE];       /* from child and stdin */
  int out_flag[MAXLINE] ; /* initialize the output flags */
  char *program;          /* a string to hold the child program invocation */
  char **pargs = 0;             /* holds parts of the command line */
  int not_command = 1;          /* a flag while parsing the command line */



  /* try to get a pseudoterminal to play with */
  if (ptyopen(&contNum, &serverNum, controllerPath, serverPath) == -1) {
    perror("ptyopen failed");
    exit(-1);
  }

  /* call the routine that handles signals */
  catch_signals();

  /* parse the command line arguments - as with the aixterm  the command
     argument -e should be last on the line. */

  while(*++argv && not_command) {
    if(!strcmp(*argv, "-f"))
      load_wct_file(*++argv);
    else if(!strcmp(*argv, "-e")) {
      not_command = 0;
      pargs = ++argv;
    }
    else {
      fprintf(stderr, "usage: clef [-f fname] -e command\n");
      exit(-1);
    }
  }
  skim_wct();

#ifdef log
  sprintf(logpath, "/tmp/cleflog%d", getpid());
  logfd = open(logpath, O_CREAT | O_RDWR, 0666);
#endif

  /* get the original termio settings, so the child has them */

  if(tcgetattr(0,&childbuf) == -1) {
    perror("clef trying to get the initial terminal settings");
    exit(-1);
  }

  /* start the child process */

  child_pid = fork();
  switch(child_pid) {
  case -1 :
    perror("clef can't create a new process");
    exit(-1);
  case 0:
    /* CHILD */
    /* Dissasociate form my parents group so all my child processes
       look at my terminal as the controlling terminal for the group */
    setsid();

    serverNum = open(serverPath,O_RDWR);
    if (serverNum == -1) perror("open serverPath failed");

    /* since I am the child, I can close ptc, and dup pts for all it
       standard descriptors */
    if (dup2(serverNum, 0) == -1) perror("dup2 0 failed");
    if (dup2(serverNum, 1) == -1) perror("dup2 1 failed");
    if (dup2(serverNum, 2) == -1) perror("dup2 2 failed");
    if( (dup2(serverNum, 0) == -1)  ||
        (dup2(serverNum, 1) == -1) ||
        (dup2(serverNum, 2) == -1)  ) {
      perror("clef trying to dup2");
      exit(-1);
    }

    /* since they have been duped, close them */
    close(serverNum);
    close(contNum);


    /* To make sure everything is nice, set off enhedit */
    /*    childbuf.c_line = 0; */

    /* reconfigure the child's terminal get echoing */
    if(tcsetattr(0, TCSAFLUSH, &childbuf) == -1) {
      perror("clef child trying to set child's terminal");
      exit(-1);
    }

    /* fire up the child's process */
    if(pargs){
      execvp( pargs[0], pargs);
      perror("clef trying to execvp its argument");
      fprintf(stderr, "Process --> %s\n", pargs[0]);
    }
    else{
      program = getenv("SHELL");
      if (!program)
        program = strdup("/bin/sh");
      else
        program = strdup (program);
      execlp( program,program, 0);
      perror("clef trying to execlp the default child");
      fprintf(stderr, "Process --> %s\n", program);
    }
    exit(-1);
    break;
    /* end switch */
  }
  /* PARENT */
  /* Since I am the parent, I should start to initialize some stuff.
     I have to close the pts side for it to work properly */

  close(serverNum);
  ppid = getppid();

  /* Iinitialize some stuff for the reading and writing */
  init_flag(out_flag, MAXLINE);
  define_function_keys();
  init_reader();
  PTY = 1;
  init_parent();

  /* Here is the main loop, it simply starts reading characters from
     the std input, and from the child. */

  while(1)  {           /* loop forever */

    /* use select to see who has stuff waiting for me to handle */
    /* set file descriptors for ptc and stdin */
    FD_ZERO(&rfds);
    FD_SET(contNum,&rfds);
    FD_SET(0,&rfds);
    set_function_chars();
#ifdef log
    {
      char modepath[30];
      sprintf(modepath, "\nMODE = %d\n", MODE);
      write(logfd, modepath, strlen(modepath));
    }
#endif
#ifdef logterm
    {
      struct termio ptermio;
      char pbuff[1024];
      tcgetattr(contNum, &ptermio);
      sprintf(pbuff, "child's settings: Lflag = %d, Oflag = %d, Iflag = %d\n",
              ptermio.c_lflag, ptermio.c_oflag, ptermio.c_iflag);
      write(logfd, pbuff, strlen(pbuff));
    }
#endif

    code = select(FD_SETSIZE,(void *) &rfds, NULL, NULL, NULL);
    for(; code < 0 ;) {
      if(errno == EINTR) {
        check_flip();
        code = select(FD_SETSIZE,(void *) &rfds, NULL, NULL, NULL);
      }
      else  {
        perror("clef select failure");
        exit(-1);
      }
    }

    /* reading from the child **/
    if( FD_ISSET(contNum,&rfds)) {
      if( (num_read = read(contNum, out_buff, MAXLINE)) == -1) {
        num_read = 0;
      }
#ifdef log
      write(logfd, "OUT<<<<<", strlen("OUT<<<<<"));
      write(logfd, out_buff, num_read);
#endif
      if(num_read > 0) {
        /* now do the printing to the screen */
        if(MODE!= CLEFRAW) {
          back_up(buff_pntr);
          write(1,out_buff, num_read);
          print_whole_buff();    /* reprint the input buffer */
        }
        else write(1,out_buff, num_read);
      }
    } /* done the child stuff */
    /* I should read from std input */
    else  {
      if(FD_ISSET(0,&rfds)) {
        num_read = read(0, in_buff, MAXLINE);
#ifdef log
        write(logfd, "IN<<<<<", strlen("IN<<<<<"));
        write(logfd, in_buff, num_read);
#endif
        check_flip();
        if(MODE == CLEFRAW )
          write(contNum, in_buff, num_read);
        else
          do_reading();
      }
    }
  }
}