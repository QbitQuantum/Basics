main (void)
{
	pid_t	pid_gui;
	pid_t	pid_sim;
	pid_t	pid_pport;
	
	int		simChid;

	
	int		kill_gui;
	int		kill_sim;
	int		kill_pport;
	
	int		s_return;	
	
	//---thread paramters--------------//
	pthread_attr_t attr;
	pthread_t timerThreadID;
	pthread_t keyboardThreadID;
	pthread_t blockIDThreadID;
	
	do
	{
	printf("\n=========================================================\n");
	printf("Please Selet the Operating Mode:\n");
	printf("1: Basic Orientation Mode for Block: 0-10).\n");
	printf("2: Rotated Orientation Mode for Block:0-6). (alaph version)\n");
	printf("===========================================================\n");
	flushall();
	scanf ("%c",&programMode);
	printf("You have selected: Mode %c.\n\n",programMode);
	flushall();
	if((programMode != '1' )&&(programMode !='2'))
	{
		printf("Invalid Selection, Please Enter!\n");
		flushall();
	}
	}
	while(programMode != '1'&&programMode !='2');
	
	


// ----------------Share Memory----------------------------------------
	shMem=shm_open("shared_memory", OFLAGS, 0777);
	if (shMem == -1)
	{
		printf("shared_memory failed to open...\n");
		flushall();
	}
	else
	{
		if (ftruncate (shMem,SIZE) == -1)
		{
			printf ("Failed to set size for -- shmem -- \n");
			flushall();
		}
		else
		{
			//mapping a shared memory location
			memLocation = mmap (0,  SIZE, PROT, MFLAGS, shMem, 0);
			if (memLocation == MAP_FAILED)
			{
				printf (" Failed to map to shared memory...\n");
				flushall();
			}
		}	
	}
// ---------------Semorphore-------------------------------------
	// semorphore for shared memory
	sem = sem_open ("shared_sem", O_CREAT, S_IRWXG | S_IRWXO | S_IRWXU, 0);
	if (sem == (sem_t *)(-1)) 
	{
	   	printf ("User: Memory Semaphore failed to open....\n");
	  	flushall();
	}
	else
	{
		sem_post(sem);
	}
// -----------------------channel creation---------------------------
    // Create a channels for the simulator and Gui
    // The ChannelCreate function returns the channel ID
	ChannelCreate(0);
	ChannelCreate(0);
	//ChannelCreate(0);//for pport
	
	simChid = 1;
	sleep(1);
	
	// Spawing a process for the GUI and Simulator
	pid_gui = spawnl(P_NOWAIT, "/usr/local/bin/gui_g", "gui_g", NULL);
	pid_sim = spawnl(P_NOWAIT, "/usr/local/bin/newGUIPport_g", "sim", NULL);
	pid_pport = spawnl(P_NOWAIT, "/usr/local/bin/testPport_g", "pport",NULL);
	
	sleep(1);
	//The Gui process automatically connect to the channel
	//Thus we only need to attach the simulator process to the created channel
	coidsim = ConnectAttach(0,pid_sim,simChid,0,0);
	// Display error message if connection failed
	if (coidsim == -1)
	{
		printf("coidsim error\n");
		flushall();
		exit(EXIT_FAILURE);
	}
	coidpport = ConnectAttach(0,pid_pport,simChid,0,0);
	// Display error message if connection failed
	if (coidpport == -1)
	{
		printf("coidpport error\n");
		flushall();
		exit(EXIT_FAILURE);
	}

// --------------------------timer code----------------------------------
	// Create a channel for sending a pulse to myself when timer expires
	timerChid = ChannelCreate(_NTO_CHF_UNBLOCK);
	if(timerChid == -1)
	{
		printf("timer Channel create failed\n");		
	    	flushall();
	}
	timerCoid = ConnectAttach ( 0, getpid ( ), timerChid, 0, 0);
   	if(timerCoid == -1 ) 
   	{
       	printf ("Channel attach failed!\n");
		flushall();
		perror ( NULL ); 
		exit ( EXIT_FAILURE);
   	}
	//	Set up pulse event for delivery when the first timer expires; pulse code = 8, pulse value  = 0;
	SIGEV_PULSE_INIT (&timerEvent, timerCoid, SIGEV_PULSE_PRIO_INHERIT, 8, 0);
	//	Create Timer
	if (timer_create (CLOCK_REALTIME, &timerEvent, &timerid) == -1) 
   	{
   		printf ( "Failed to create a timer for pulse delivery\n");
		flushall();
   		perror (NULL);
   		exit ( EXIT_FAILURE);
   	}
	// Setup one time timer for 2 second
	timer.it_value.tv_sec = 2;
	timer.it_value.tv_nsec = 0;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_nsec = 0;
// --------------------------timer2 code----------------------------------
	// Create a channel for sending a pulse to myself when timer expires
	timerChid2 = ChannelCreate(_NTO_CHF_UNBLOCK);
	if(timerChid2 == -1)
	{
		printf("timer Channel create failed\n");		
	    	flushall();
	}
	timerCoid2 = ConnectAttach ( 0, getpid ( ), timerChid2, 0, 0);
   	if(timerCoid2 == -1 ) 
   	{
       	printf ("Channel attach failed!\n");
		flushall();
		perror ( NULL ); 
		exit ( EXIT_FAILURE);
   	}
	// Set up pulse event for delivery when the first timer expires; pulse code = 8, pulse value  = 0;
	SIGEV_PULSE_INIT (&timerEvent2, timerCoid2, SIGEV_PULSE_PRIO_INHERIT, 8, 0);
	// Create Timer
	if (timer_create (CLOCK_REALTIME, &timerEvent2, &timerid2) == -1) 
   	{
   		printf ( "Failed to create a timer for pulse delivery\n");
		flushall();
   		perror (NULL);
   		exit ( EXIT_FAILURE);
   	}
//-------------------timer monitor thread--------------------
	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	pthread_create(&timerThreadID,&attr,timer_thread,NULL);
	if(timerThreadID == -1)
	{
		printf("Fail to create timer thread!");
		flushall();
	}
	else
	{
		printf("The timer thread ID is %i \n",timerThreadID);
		flushall();
	}
	pthread_create(&timerThreadID,&attr,timer2_thread,NULL);
	if(timerThreadID == -1)
	{
		printf("Fail to create timer thread2!");
		flushall();
	}
	else
	{
		printf("The timer thread2 ID is %i \n",timerThreadID);
		flushall();
	}
//
//----start the block Identification thread-----------------
//	pFile = fopen("Blocks.txt","w+");
	pthread_create(&blockIDThreadID,&attr,blockID,NULL);
		if(blockIDThreadID == -1)
	{
		printf("Fail to create block indeptification thread!");
		flushall();
	}
	else
	{
		printf("The BlockID's thread ID is %i \n",blockIDThreadID);
		flushall();
	}
	delay(10);
//---------------------keyboard thread------------------------
	pthread_create(&keyboardThreadID,&attr,keyboard_input,NULL);
		if(keyboardThreadID == -1)
	{
		printf("Fail to create keyboard input!");
		flushall();
	}
	else
	{
		printf("The keyboard_input ID is %i \n",timerThreadID);
		flushall();
	}
	delay(10);
//----------------GUI Monitor Thread---------------------
	pthread_create(NULL,&attr,GUI_thread,NULL);
	delay(10);
// --------------------SIM pulse Handler Loop Thread----------
	pthread_create(NULL,&attr,Handlerloop_thread,NULL);
	delay(10);
// --------------------SIM Monitor Thread---------------------
	pthread_create(NULL,&attr,SIM_thread,NULL);
	delay(10);
// --------------------Auto mode thread-----------------------
	pthread_create(NULL,&attr,auto_thread,NULL);
	delay(10);
// --------------------others---------------------------------
	// call mainLoop()
	mainLoop();
	// sleep for 10sec
	printf("Sleep the program for 10 seconds\n");
	flushall;
	sleep(10);
	// start release system resourse
	printf("Clean up and release system resourse\n");
	flushall;
	// Kill the existing processes
	kill_gui = kill(pid_gui, 0);
	kill_sim = kill(pid_sim, 0);
	kill_pport = kill(pid_pport, 0);
    if (kill_gui == -1)
	{
		printf("GUI Kill failed\n");
		flushall();
	}
	if (kill_sim == -1)
	{
		printf("SIM Kill failed\n");
		flushall();
	} 
	if (kill_pport == -1)
	{
		printf("PPort Kill failed\n");
		flushall();
	}
	// Close and unlink Semorphore
	sem_close(sem);
	s_return = sem_unlink("/dev/sem/home/quad6/workspace/Project_S1/shared_sem");
	// Display error messae if semorphonre unlink is failed
	if (s_return == -1)
	{
		printf("a: %s\n", strerror( errno ));
		flushall();
	}
	// Close, unmap, and unlink shared memory
	shm_close(shMem);
	munmap(shmLocation,SIZE);
	shm_unlink("shared_memory");
	// Detach the connections and destroy the channels
	ConnectDetach(coidGui);
    ConnectDetach(coidsim);
    ConnectDetach(coidpport);
    ChannelDestroy(guiChid);
    ChannelDestroy(simChid);
    
//    fclose(pFile);
}	