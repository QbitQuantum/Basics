//**************************************************************************
int main()
{

	
	// catch signals so we can clean up everything before exitting
	// signals defined in /usr/include/signal.h
	// e.g. when we recieved an interrupt signal SIGINT, call die()
	sigset(SIGINT,die);		// catch kill signals 
	sigset(SIGBUS,die);		// catch bus errors
	sigset(SIGHUP,die);		
	sigset(SIGILL,die);		// illegal instruction
	sigset(SIGQUIT,die);
	sigset(SIGABRT,die);
	sigset(SIGTERM,die);
	sigset(SIGSEGV,die);	// catch segmentation faults

	sigset(SIGALRM,tick_handler);

    alarm(1);

	// signal from keyboard reader is SIGUSR1 (user-defined signal)
	// When there is input from the keyboard, call the kbd_handler() routine
	sigset(SIGUSR1,kbd_handler);	
	
	
	/* Create a new mmap file for read/write access with permissions restricted
	to owner rwx access only */
	fid = open(sfilename, O_RDWR | O_CREAT | O_EXCL, (mode_t) 0755 );
	if (fid < 0){
		printf("Bad Open of mmap file <%s>\n", sfilename);
		exit(0);
	};

	fid2 = open(cfilename, O_RDWR | O_CREAT | O_EXCL, (mode_t) 0755 );
	if (fid2 < 0){
		printf("Bad Open of mmap file <%s>\n", cfilename);
		exit(0);
	};


	// make the file the same size as the buffer 
	status = ftruncate(fid, bufsize ); 
	if (status){
		printf("Failed to ftruncate the file <%s>, status = %d\n", sfilename, status );
		exit(0);
	}
	
	status = ftruncate(fid2, bufsize ); 
	if (status){
		printf("Failed to ftruncate the file <%s>, status = %d\n", cfilename, status );
		exit(0);
	}


	// pass parent's process id and the file id to child
	char childarg1[20], childarg2[20]; // arguments to pass to child process(es)
	int mypid = getpid();			// get current process pid
  
	sprintf(childarg1, "%d", mypid); // convert to string to pass to child
    sprintf(childarg2, "%d", fid);   // convert the file identifier
  

	// now start doing whatever work you are supposed to do
	// in this case, do nothing; only the keyboard handler will do work
	
	printf("\nWelcome to the CCI, the OS is at your disposal: \n");

	// create the keyboard reader process
	// fork() creates a second process identical to the current process,
	// except that the "parent" process has in_pid = new process's ID,
	// while the new (child) process has in_pid = 0.
	// After fork(), we do execl() to start the actual child program.
	// (see the fork and execl man pages for more info)

	in_pid_keyboard = fork();
	if (in_pid_keyboard == 0)	// is this the child process ?
	{
		execl("./keyboard", "keyboard", childarg1, childarg2, (char *)0);
		// should never reach here
		fprintf(stderr,"kernal: can't exec keyboard, errno %d\n",errno);
		cleanup();
		exit(1);
	};
	
	// pass parent's process id and the file id to child CRT
  
	sprintf(childarg1, "%d", mypid); // convert to string to pass to child
    sprintf(childarg2, "%d", fid2);   // convert the file identifier
	
	in_pid_crt = fork();
	if (in_pid_crt == 0)	// is this the child process ?
	{
		execl("./crt", "crt", childarg1, childarg2, (char *)0);
		// should never reach here
		fprintf(stderr,"kernal: can't exec crt, errno %d\n",errno);
		cleanup();
		exit(1);
	};
	
	// the parent process continues executing here

	// sleep for a second to give the child process time to start
	sleep(1);

	// allocate a shared memory region using mmap 
	// the child process also uses this region
	
	mmap_ptr_keyboard = mmap((caddr_t) 0,   /* Memory location, 0 lets O/S choose */
		    bufsize,              /* How many bytes to mmap */
		    PROT_READ | PROT_WRITE, /* Read and write permissions */
		    MAP_SHARED,    /* Accessible by another process */
		    fid,           /* the file associated with mmap */
		    (off_t) 0);    /* Offset within a page frame */
	if (mmap_ptr_keyboard == MAP_FAILED){
		printf("Parent's memory map has failed for keyboard, about to quit!\n");
		die(0);  // do cleanup and terminate
	};
	
	in_mem_p_key = (inputbuf *) mmap_ptr_keyboard;   // pointer to shared memory
	// we can now use 'in_mem_p' as a standard C pointer to access 
	// the created shared memory segment 
	
	in_mem_p_key->ok_flag = 0;
	
	
	// allocate a shared memory region using mmap 
	// the child process also uses this region
	
	mmap_ptr_crt = mmap((caddr_t) 0,   /* Memory location, 0 lets O/S choose */
		    bufsize,              /* How many bytes to mmap */
		    PROT_READ | PROT_WRITE, /* Read and write permissions */
		    MAP_SHARED,    /* Accessible by another process */
		    fid2,           /* the file associated with mmap */
		    (off_t) 0);    /* Offset within a page frame */
	if (mmap_ptr_crt == MAP_FAILED){
		printf("Parent's memory map has failed for CRT, about to quit!\n");
		die(0);  // do cleanup and terminate
	};
	
	in_mem_p_crt = (outputbuf *) mmap_ptr_crt;   // pointer to shared memory
	// we can now use 'in_mem_p' as a standard C pointer to access 
	// the created shared memory segment 
	

	in_mem_p_crt->ok_flag = 0;
	
	
	while (1);

	// should never reach here, but in case we do, clean up after ourselves
	cleanup();
	exit(1);
} // main