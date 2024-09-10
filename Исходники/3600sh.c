void readCommand() {
	/* allocate files used for redirection of stderr, stdin, stdout */
	char  **file = calloc(3, sizeof(char*));
  	if (!file) {
  		memoryError();
  	}

	for (int i = 0; i < 3; i++)
	{
	    file[i] = calloc(MAX_INPUT_LENGTH + 1, sizeof(char));
	    if (!file[i]) {
	      	memoryError();
	    }
	}

	/* initialize status to designate different modes as identified in #defines */
	status parseStatus = 0;
	
	char** args = readArgs(&parseStatus, file); 	
	
	/* determine whether shell should exit after executing command */
	bool terminate = EOF_FOUND & parseStatus;
	//Bit masking is used to use a single value for status.
	switch(parseStatus & (INVALID_SYNTAX | INVALID_ESCAPE)){
		case INVALID_SYNTAX:
			printf("Error: Invalid syntax.\n");
			if (terminate)
				do_exit();			
			return;
		case INVALID_ESCAPE:
			printf("Error: Unrecognized escape sequence.\n");
			if (terminate)
				do_exit();			
			return;
	}

	/* if "exit" is inputted, quit the shell */
	if (args[0]) {
		if (args[1] == NULL && strncmp(args[0], EXIT_COMMAND, strlen(EXIT_COMMAND)) == 0) {
			do_exit();
		}
	}
	
 	int restore_stdout = 0;
	int restore_stdin = 0; 
	int restore_stderr = 0; 
 	int f = -1;
	
	/* check if any redirection was requested and set up proper files */
	if (parseStatus & REDIR_STDOUT)
	{ 
		/*open afile with read and write permissions for the user. */
		/*Create it if needed, and truncate it if opened*/
		f = open(file[STDOUT],O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR); 
		if (f == -1) //-1 indicates that there was a problem with the file
		{
			printf("Error: Invalid syntax.\n");
			if (terminate) {//if it is EOF, terminate
				do_exit();
			}
			return; //otherwise, print another prompt
		}
		/*Open a file with the path "file" and the intention to read and write from it. */
		/*If it does not exist create it and give read and write permissions to the user*/
        	restore_stdout = dup(STDOUT); //keep a copy of STDOUT
        	close(STDOUT); //Close STDOUT
		dup(f); //Copy the same file descriptor but set it to the newly closed STDOUT
		close(f); //Close original file
	}
	if (parseStatus & REDIR_STDERR)
	{
		f = open(file[STDERR],O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR); 
		if (f == -1)
		{
			printf("Error: Invalid syntax.\n");
			if (terminate) {
				do_exit();
			}
			return;
		}
        	restore_stderr = dup(STDERR); //keep a copy of STDOUT
        	close(STDERR); //Close STDOUT
		dup(f); //Copy the same file descriptor but set it to the newly closed STDOUT
		close(f); //Close original file
	}
	if (parseStatus & REDIR_STDIN)//type==(2<<STDIN))
	{ 
		/*Do not create a file, as it would be empty and useless to STDIN*/
		/*Open as read only because it is an input source*/
		f = open(file[STDIN],O_RDONLY); 
		if (f == -1)
		{
			printf("Error: Unable to open redirection file.\n");
			if (terminate) {
				do_exit();
			}
			return;
		}
        	restore_stdin = dup(STDIN); 
        	close(STDIN); 
		dup(f); 
		close(f); 
	}

  /* workaround to allow 'cd' command */
  if(args[0] && strncmp(args[0], "cd", 2) == 0)
  {
     int error = 0; 
     if(args[1])
     	  error = chdir(args[1]);
     else
	error = chdir("/home");
     if(error)
	printf("cd: %s: No such file or directory\n",args[1]);
	
	return;
  }
  
  pid_t parent = fork();
  
  if (parent < 0) {
    printf("Error: process creation failed");  
    do_exit();
  }

  /* if we are in the child process, execute the command */
  else if (!parent) {
    if (execvp(args[0], args)) {
    	if((*args)[0]) {
          printf("Error: ");
          switch(errno) { //based on values in `man errno`
            case 1: printf("Permission denied.\n"); break;
            case 2: printf("Command not found.\n"); break;
	    case 13: printf("Permission denied.\n"); break;
            default: printf("Unkown error.\n"); break;
    	    }
      }
    }
    exit(0);
  } else {
	/* in parent, wait for child if not a background process */
	if (!(parseStatus & BACKGROUND)) {  
    		waitpid(parent, NULL, 0);
	}
    	if (terminate) {
      		do_exit();
   	}
  }

  /* restore any file redirections as necessary */
  if(restore_stdin)
  {
  	close(STDIN);
  	dup(restore_stdin);
  	close(restore_stdin);
  }
  if(restore_stdout)
  {
  	close(STDOUT);
  	dup(restore_stdout);
  	close(restore_stdout);
  }
  if(restore_stderr)
  {
  	close(STDERR);
  	dup(restore_stderr);
  	close(restore_stderr);
  }

  /* free all allocated memory */
  for (int i = 0; i < 3; i++) {
    free(file[i]);
  }
  free(file);
  deleteArgs(args);
  free(args);
}