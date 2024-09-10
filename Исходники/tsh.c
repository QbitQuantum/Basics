/* 
 * eval - Evaluate the command line that the user has just typed in
 * 
 * If the user has requested a built-in command (quit, jobs, bg or fg)
 * then execute it immediately. Otherwise, fork a child process and
 * run the job in the context of the child. If the job is running in
 * the foreground, wait for it to terminate and then return.  Note:
 * each child process must have a unique process group ID so that our
 * background children don't receive SIGINT (SIGTSTP) from the kernel
 * when we type ctrl-c (ctrl-z) at the keyboard.  
 */
void eval(char *cmdline) 
{
    int bg;              /* should the job run in bg or fg? */
    struct cmdline_tokens tok;
    pid_t pid;
    sigset_t mask;

    /* Parse command line */
    bg = parseline(cmdline, &tok); 

    if (bg == -1) return;               /* parsing error */
    if (tok.argv[0] == NULL)  return;   /* ignore empty lines */
    
    sigemptyset(&mask);
    sigaddset(&mask,SIGCHLD);
    sigaddset(&mask,SIGINT);
    sigaddset(&mask,SIGTSTP);
    sigprocmask(SIG_BLOCK,&mask,NULL);
    
    if(!builtin_handler(tok))
      {
	if((pid=Fork())==0)
	  {
	    /*restore default handlers*/
	    Signal(SIGINT,SIG_DFL);
	    Signal(SIGTSTP,SIG_DFL);
	    sigprocmask(SIG_UNBLOCK,&mask,NULL);
	    
	    /*Put child process in its own group*/
	    Setpgid(0,0);

	    IO_redirection(tok);
	      
	    Execve(tok.argv[0],tok.argv,environ);
	    
	  }
	else /*Shell Processing*/
	  {
	    if(bg)
	      {
		addjob(job_list,pid,BG,cmdline);
		printf("[%d] (%d) %s\n", pid2jid(pid), pid, cmdline);
		sigprocmask(SIG_UNBLOCK,&mask,NULL);
		
	      }
	    else
	      {
		addjob(job_list,pid,FG,cmdline);
		sigprocmask(SIG_UNBLOCK,&mask,NULL);
		while(fgpid(job_list) != 0)
		  {
		  }

		
	      }
	  }
      }

    


}