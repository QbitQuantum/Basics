static int 
init_compile( int  what_todo,		 /* do a compile or clean             */
              char *base_dir,            /* base directory of the test        */
              char *hname)		 /* hostname of the machine           */
{
    int 	status;		/* return status of execve process            */
    pid_t	pid;		/* pid of the process that does compile       */
    char	*dirname;	/* location where compile is initated         */
    char	*command;	/* make or make clean command.                */

    if ((dirname = malloc(sizeof(char) * 1024)) == NULL) /* just paranoid */
    {
        perror("init_compile(): dirname malloc()");
        return 1;
    }

    if ((command = malloc(1024)) == NULL) 		/* just paranoid */
    {
        perror("init_compile(): dirname malloc()");
        return 1;
    }

    what_todo ? sprintf(command, "make -s") : sprintf(command, "make -s clean");
    
    sprintf(dirname, "%s/%s.%ld", base_dir, hname, gettid());

    if (chdir(dirname) == -1)
    {
        dprt("pid[%d]: init_compile(): dir name = %s\n", gettid(), dirname);
        perror("init_compile() chdir()");
        free(dirname);
        return 1;
    }
    
    dprt("pid[%d]: init_compile(): command = %s\n", gettid(), command);

    if ((pid = fork()) == -1) 
    {
        perror("init_compile(): fork()");
        return 1;
    }
    if (!pid)
    {
        char *argv[4];
        char *envp[1];

        argv[0] = "/bin/sh";
        argv[1] = "-c";
        argv[2] = command;
        argv[3] = 0;

     
	if (execv("/bin/sh", argv) == -1)
        {
	  perror("init_compile(): execv()");
            return 1;
        }
    }
    do
    {
        if (waitpid(pid, &status, 0) == -1)
        {
            if (errno != EINTR)
            { 
                fprintf(stderr, "init_compile(): waitpid() failed\n");
                return 1;
            }
        }
        else
        {
            if (chdir(base_dir) == -1)
            {
                dprt("pid[%d]: init_compile(): dir = %s\n", gettid(), dirname);
                perror("init_compile(): chdir()");
                return 1;
            }

            dprt("pid[%d]: init_compile(): status = %d\n", status);
            dprt("we are here %d\n", __LINE__);
            return status;
        }
           
    } while(1);
}