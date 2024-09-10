void main(int argc,char* argv[])
{
	signal(SIGKILL,wrapup);
	signal(SIGINT,wrapup);
	signal(SIGTERM,wrapup);
	signal(SIGQUIT,wrapup);

	int num_ATMs,i;

	if(argc!=2)
	{
		printf("Please enter : %s <number_of_ATMs>\n", argv[0]);
		exit(0);
	}
	else
		sscanf(argv[1],"%d",&num_ATMs);

	createLocatorFile();

	semID = semget((key_t)SEMAPHORE_KEY,num_ATMs,IPC_CREAT|0666);
	if(semID==-1) perror("Error in semget !\n");

	mssgQ_ID=msgget((key_t)MASTER_MSSG_Q_KEY,IPC_CREAT|0666);
	if(mssgQ_ID==-1) perror("Error in msgget !\n");

	globl_shmID = shmget((key_t)GLOBAL_SHARED_MEMORY_KEY,MAX_CLIENTS*sizeof(struct balance_record),IPC_CREAT|0666);
	if(globl_shmID==-1) perror("Error in shmget !\n");

	globl_shm_ptr = shmat(globl_shmID,NULL,0);
	globl_shm_end_record = globl_shm_ptr; // initially NO client record

	initializeAllSubSemaphoreValues(num_ATMs);

	for(i=0;i<num_ATMs;i++)
	{
		int index,KEY; // the same KEY will be used for both the ATM - Client Message Queue as well as the shared memory of the ATM process

		int pid = fork();
		if(pid == 0)
			{			
				// ATM (forked child) process
				index = getpid() - getppid();
				KEY = 10*index;

				char buf[10];
				sprintf(buf,"%d",KEY);

				//int retv = execlp("atm.c","./atm",buf,NULL);
				int retv = execlp("./atm","./atm",buf,NULL);	
				if(retv == -1) {perror("Error in execlp ! \n"); exit(1);}
			}
		else
		{
			// master(parent) process
			index = pid - getpid();
			KEY = 10*index;

			appendToLocatorFile(index,KEY,index-1,KEY);
			
		}

		//sleep(1);	// sleep for 1 second before generating another process
	}

	while(1)
	{
		int pid;
		int atm_pid;

		struct mssg buffer;
		struct msqid_ds qstat;

		msgrcv(mssgQ_ID,&buffer,sizeof(buffer),getpid(),0);
		msgctl(mssgQ_ID,IPC_STAT,&qstat);

		printf("Master Process received message %s from ATM%d\n\n",buffer.mtext,qstat.msg_lspid-getpid());

		if(sscanf(buffer.mtext,"CHCK_ACCOUNT %d",&pid)==1)
			checkClientAccount(pid);
		else if(strcmp(buffer.mtext,"GLOBAL_CONSISTENCY_CHECK_REQUEST")==0)
		{
			performGlobalConsistencyCheck();

			buffer.mtype=qstat.msg_lspid;
			strcpy(buffer.mtext,"GLOBAL CONSISTENCY CHECK COMPLETION CONFIRMATION ");
			msgsnd(mssgQ_ID,&buffer,sizeof(buffer),0);

		}
		else printf("Invalid Message !\n\n");

	}

	wrapup();
}