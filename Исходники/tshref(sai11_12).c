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
    char *argv[MAXARGS];    //argv array
    int bg;                 //0 run in fg, 1 run in bg or blank
    sigset_t mask;          //use to set Signal in blocked
    pid_t pid;              //process ID

    bg = parseline(cmdline, argv);   

    if (!(builtin_cmd(argv)))
    {
        //This is not a built-in comand -> Fork a child process and run the program in this process

        //Block SIGCHLD signal to avoid race conditions
        if (sigemptyset(&mask) < 0)
        {
            printf("sigemptyset error"); //Error handling
        }
        if (sigaddset(&mask, SIGCHLD))
        {
            printf("sigaddset error"); //Error handling
        }           
        if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0)
        {           
            printf("sigprocmask error"); //Error handling
        }
        
        //Fork child process    
        if ((pid = fork()) == 0)    
        {
            //Child process       
            setpgid(0,0);                            //Set new process group ID
            sigprocmask(SIG_UNBLOCK, &mask, NULL);   //Unblock SIGCHLD signals  before execute the pjob
            if (execve(argv[0],argv,environ) == -1)  //execute job
            {
                printf("%s: Command not found\n", argv[0]);
                exit(0); // Terminate child
            }
        }       
        else
        {
            //Parent process    
            if (bg == 0)
            {
                //Run child process in foreground   
                addjob(jobs, pid, FG, cmdline);     //Add child job to job list
                sigprocmask(SIG_UNBLOCK, &mask, NULL);  //Unblock SIGCHLD signals in parent process 
                waitfg(pid);                        //Parent waits while child in fg
            }

            else if (bg == 1)
            {
                //Run child process in background
                addjob(jobs, pid, BG, cmdline);     //Add child to job list
                sigprocmask(SIG_UNBLOCK, &mask, NULL);  //After that, Unblock SIGCHLD signals to allow parent process to reap the child
                printf("[%d] (%d) %s", pid2jid(pid), pid, cmdline); //BG process info

            }
        }

    }
    return;
}