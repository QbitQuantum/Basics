int main()
{
	char	str[128];
	char	compiler[128];
	char	fpath[MAX_PATH+1];
	char*	path = ".";
	char*	glob_pattern = "*wrap*";
	int		i;
	int		ch;
	uint	u;
	time_t	t;
	glob_t	g;
	DIR*	dir;
	DIRENT*	dirent;
	thread_data_t thread_data;
	int	fd;
	int	fd2;
	int	canrelock=0;
	clock_t	ticks;

	/* Show platform details */
	DESCRIBE_COMPILER(compiler);
	printf("%-15s: %s\n","Platform",PLATFORM_DESC);
	printf("%-15s: %s\n","Version",os_version(str));
	printf("%-15s: %s\n","Compiler"	,compiler);
	printf("%-15s: %d\n","Random Number",xp_random(1000));

	for(i=0;i<3;i++) {
		if(_beginthread(
			  sopen_child_thread	/* entry point */
			 ,0  					/* stack size (0=auto) */
			 ,(void*)i				/* data */
			 )==(unsigned long)-1)
			printf("_beginthread failed\n");
		else
			SLEEP(1);
	}
	printf("Waiting for all sopen_child_threads to close...\n");
	SLEEP(5000);	/* wait for all threads to quit */

	/* Exclusive sopen test */
	printf("\nsopen() test\n");
	if((fd=sopen(LOCK_FNAME,O_RDWR|O_CREAT,SH_DENYRW,S_IREAD|S_IWRITE))==-1) {
		perror(LOCK_FNAME);
		return(errno);
	}
	printf("%s is opened with an exclusive (read/write) lock\n",LOCK_FNAME);
	getkey();
	if(_beginthread(
		  sopen_test_thread	/* entry point */
		 ,0  				/* stack size (0=auto) */
		 ,NULL				/* data */
		 )==(unsigned long)-1)
		printf("_beginthread failed\n");
	else
		SLEEP(1000);
	close(fd);

	/* sopen()/lock test */
	printf("\nlock() test\n");
	if((fd=sopen(LOCK_FNAME,O_RDWR|O_CREAT,SH_DENYNO,S_IREAD|S_IWRITE))==-1) {
		perror(LOCK_FNAME);
		return(errno);
	}
	write(fd,"lock testing\n",LOCK_LEN);
	if(lock(fd,LOCK_OFFSET,LOCK_LEN)==0)
		printf("lock() succeeds\n");
	else
		printf("!FAILURE: lock() non-functional (or file already locked)\n");
	if(lock(fd,LOCK_OFFSET,LOCK_LEN)==0)  {
		printf("!FAILURE: Subsequent lock of region was allowed (will skip some tests)\n");
		canrelock=1;
	}
		
	if(_beginthread(
		  lock_test_thread	/* entry point */
		 ,0  				/* stack size (0=auto) */
		 ,NULL				/* data */
		 )==(unsigned long)-1)
		printf("_beginthread failed\n");
	else
		SLEEP(1000);
	if(canrelock)
		printf("?? Skipping some tests due to inability to detect own locks\n");
	else  {
		if(lock(fd,LOCK_OFFSET,LOCK_LEN))
			printf("Locks in first thread survive open()/close() in other thread\n");
		else
			printf("!FAILURE: lock() in first thread lost by open()/close() in other thread\n");
		if(lock(fd,LOCK_OFFSET+LOCK_LEN+1,LOCK_LEN))
			printf("!FAILURE: file locking\n");
		else
			printf("Record locking\n");
	}
	if((fd2=sopen(LOCK_FNAME,O_RDWR,SH_DENYRW))==-1) {
		printf("Cannot reopen SH_DENYRW while lock is held\n");
		close(fd2);
	}
	else  {
		printf("!FAILURE: can reopen SH_DENYRW while lock is held\n");
	}
	if(unlock(fd,LOCK_OFFSET,LOCK_LEN))
		printf("!FAILURE: unlock() non-functional\n");
	if(lock(fd,LOCK_OFFSET+LOCK_LEN+1,LOCK_LEN))
		printf("Cannot re-lock after non-overlapping unlock()\n");
	else
		printf("!FAILURE: can re-lock after non-overlappping unlock()\n");
	if(lock(fd,LOCK_OFFSET,LOCK_LEN))
		printf("!FAILURE: cannot re-lock unlocked area\n");
	close(fd);

	/* getch test */
	printf("\ngetch() test (ESC to continue)\n");
	do {
		ch=getch();
		printf("getch() returned %d\n",ch);
	} while(ch!=ESC);

	/* kbhit test */
	printf("\nkbhit() test (any key to continue)\n");
	while(!kbhit()) {
		printf(".");
		fflush(stdout);
		SLEEP(500);
	}
	getch();	/* remove character from keyboard buffer */

	/* BEEP test */
	printf("\nBEEP() test\n");
	getkey();
	for(i=750;i>250;i-=5)
		BEEP(i,15);
	for(;i<1000;i+=5)
		BEEP(i,15);

	/* SLEEP test */
	printf("\nSLEEP(5 second) test\n");
	getkey();
	t=time(NULL);
	printf("sleeping... ");
	fflush(stdout);
	ticks=msclock();
	SLEEP(5000);
	printf("slept %ld seconds (%ld according to msclock)\n",time(NULL)-t,(msclock()-ticks)/MSCLOCKS_PER_SEC);

	/* Thread SLEEP test */
	printf("\nThread SLEEP(5 second) test\n");
	getkey();
	i=0;
	if(_beginthread(
		  sleep_test_thread	/* entry point */
		 ,0					/* stack size (0=auto) */
		 ,&i				/* data */
		 )==(unsigned long)-1)
		printf("_beginthread failed\n");
	else {
		SLEEP(1);			/* yield to child thread */
		while(i==0) {
			printf(".");
			fflush(stdout);
			SLEEP(1000);
		}
	}

	/* glob test */
	printf("\nglob(%s) test\n",glob_pattern);
	getkey();
	i=glob(glob_pattern,GLOB_MARK,NULL,&g);
	if(i==0) {
		for(u=0;u<g.gl_pathc;u++)
			printf("%s\n",g.gl_pathv[u]);
		globfree(&g);
	} else
		printf("glob(%s) returned %d\n",glob_pattern,i);

	/* opendir (and other directory functions) test */
	printf("\nopendir(%s) test\n",path);
	getkey();
	printf("\nDirectory of %s\n\n",FULLPATH(fpath,path,sizeof(fpath)));
	dir=opendir(path);
	while(dir!=NULL && (dirent=readdir(dir))!=NULL) {
		t=fdate(dirent->d_name);
		printf("%.24s %10lu  %06o  %s%c\n"
			,ctime(&t)
			,flength(dirent->d_name)
			,getfattr(dirent->d_name)
			,dirent->d_name
			,isdir(dirent->d_name) ? '/':0
			);
	}
	if(dir!=NULL)
		closedir(dir);
	printf("\nFree disk space: %lu kbytes\n",getfreediskspace(path,1024));

	/* Thread (and inter-process communication) test */
	printf("\nSemaphore test\n");
	getkey();
	if(sem_init(&thread_data.parent_sem
		,0 /* shared between processes */
		,0 /* initial count */
		)) {
		printf("sem_init failed\n");
	}
	if(sem_init(&thread_data.child_sem
		,0	/* shared between processes */
		,0	/* initial count */
		)) {
		printf("sem_init failed\n");
	}
	if(_beginthread(
		  sem_test_thread	/* entry point */
		 ,0					/* stack size (0=auto) */
		 ,&thread_data		/* data */
		 )==(unsigned long)-1)
		printf("_beginthread failed\n");
	else {
		sem_wait(&thread_data.child_sem);	/* wait for thread to begin */
		for(i=0;i<10;i++) {
			printf("<parent>");
			sem_post(&thread_data.parent_sem);
			sem_wait(&thread_data.child_sem);
		}
		sem_wait(&thread_data.child_sem);	/* wait for thread to end */
	}
	sem_destroy(&thread_data.parent_sem);
	sem_destroy(&thread_data.child_sem);

	printf("\nSemaphore blocking test\n");
	getkey();
	sem_init(&thread_data.parent_sem
		,0 /* shared between processes */
		,0 /* initial count */
		);
	sem_init(&thread_data.child_sem
		,0	/* shared between processes */
		,0	/* initial count */
		);
	if(_beginthread(
		  sem_test_thread_block	/* entry point */
		 ,0					/* stack size (0=auto) */
		 ,&thread_data		/* data */
		 )==(unsigned long)-1)
		printf("_beginthread failed\n");
	else {
		sem_wait(&thread_data.child_sem);	/* wait for thread to begin */
		for(i=0;i<10;i++) {
			printf("<parent>");
			SLEEP(5000);
			sem_post(&thread_data.parent_sem);
			sem_wait(&thread_data.child_sem);
		}
		sem_wait(&thread_data.child_sem);	/* wait for thread to end */
	}
	printf("\nsem_trywait_block test...");
	t=time(NULL);
	sem_trywait_block(&thread_data.parent_sem,5000);
	printf("\ntimed-out after %ld seconds (should be 5 seconds)\n",time(NULL)-t);
	sem_destroy(&thread_data.parent_sem);
	sem_destroy(&thread_data.child_sem);
	printf("\nendian check...");
	memcpy(&i,"\x01\x02\x03\x04",4);
	if(LE_LONG(i)==67305985) {
		printf("OK!\n");
	}
	else {
		printf("FAILED!\n");
	}
	return 0;
}