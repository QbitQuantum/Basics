int __cdecl main(int argc,char *argv[])
{
	int i,arg, currit, modes, modenr;
	paramT *p;

#ifdef SHAREDMEM
	int shmid;
#endif

#ifdef WIN32
	DWORD procID;
	HANDLE hProcess;
	HANDLE hThread[10];
	DWORD IDThread;
	LARGE_INTEGER lpFrequency;
#endif

	p = (paramT*) malloc(MXPROC*sizeof(paramT));

	/* default initialisation */
	modes=0;
	p[0].mode=0;
	p[0].npes=NPES;
	p[0].mxsize=MXRUNSZ;
	p[0].minsize=MINRUNSZ;
	p[0].mxstrds=MXSTRDS;
	p[0].mxiters=MXIT;
	p[0].currentrep=1;
#ifdef HAVEOPT
	p[0].useoptasm=OPTASM;
#else
	p[0].useoptasm=0;
#endif
	arg=1;
	chartrev=CHARTREV;
	printf("\nECT memperf - Extended Copy Transfer Characterization\n");
	printf("Memory Performance Characterization Toolkit %s\n\n",VERSION);

#ifdef WIN32
	/* lookup clock frequency */
	QueryPerformanceFrequency(&lpFrequency);
	tic = (lpFrequency.LowPart / 1000000.0);
	tic += (lpFrequency.HighPart * (2^32) / 1000000.0);
#else
	tic=getcpufrequency();
#endif

	if (argc<2) {
#ifdef WIN32
		printf("Usage: %s -m <mode> [-p] [-s] [-n] [-r] [-i] [-c] [-o]\n",argv[0]);
#elif defined HAVEOPT
		printf("Usage: %s -m <mode> [-p] [-s] [-n] [-r] [-i] [-t] [-c] [-a] [-o]\n",argv[0]);
#else
		printf("Usage: %s -m <mode> [-p] [-s] [-n] [-r] [-i] [-t] [-c] [-o]\n",argv[0]);
#endif /*WIN32*/
		printf("       -m <mode>    :   0 = load sum test\n");
		printf("                        1 = const store test\n");
		printf("                        2 = load copy test\n");
		printf("                        3 = copy store test\n");
		printf("                        9 = all tests\n");
		printf("       [-c <nofrep> ]   Default: %d\n", NROFREP);
#ifdef HAVEOPT
		printf("       [-a <optasm> ]   0/1 = use/don't use special instructions\n");
		printf("                        2 = both methods, Default: %d\n", OPTASM);
#endif
		printf("       [-p <nProc>  ]   Default: %d\n",NPES);
		printf("       [-s <mxstrds>]   Default: %d\n",MXSTRDS);
		printf("       [-n <mxsize> ]   Default: %d (%d Bytes)\n",MXRUNSZ,8<<MXRUNSZ);
		printf("       [-r <minsize>]   Default: %d (%d Bytes)\n",MINRUNSZ,8<<MINRUNSZ);
		printf("       [-i <mxiters>]   Default: %d\n",MXIT);
		printf("       [-o          ]   Reversed Output\n");
#ifdef WIN32
		printf("       Evaluated clock resolution [MHz]: %.2f\n",tic);
#else
		printf("       [-t <tics/us>]   Default: %.2f\n",tic);
#endif
		exit(2);
	}

	while (arg<argc) {
		if (argv[arg][0]=='-') {
			if (argv[arg][1]=='p' && (arg+1)<argc) {
				arg++; p[0].npes=atoi(argv[arg]);
			}
			if (argv[arg][1]=='s' && (arg+1)<argc) {
				arg++; p[0].mxstrds=atoi(argv[arg]);
			}
			if (argv[arg][1]=='m' && (arg+1)<argc) {
				arg++; modes=atoi(argv[arg]);
			}
			if (argv[arg][1]=='n' && (arg+1)<argc) {
				arg++; p[0].mxsize=atoi(argv[arg]);
			}
			if (argv[arg][1]=='r' && (arg+1)<argc) {
				arg++; p[0].minsize=atoi(argv[arg]);
			}
			if (argv[arg][1]=='i' && (arg+1)<argc) {
				arg++; p[0].mxiters=atoi(argv[arg]);
			}
			if (argv[arg][1]=='o') {
				chartrev=1;
			}
			if (argv[arg][1]=='a' && (arg+1)<argc) {
				arg++;
#ifdef HAVEOPT
				p[0].useoptasm=atoi(argv[arg]);
#endif
			}
			if (argv[arg][1]=='c' && (arg+1)<argc) {
				arg++; nrofrep=atoi(argv[arg]);
			}
			if (argv[arg][1]=='t' && (arg+1)<argc) {
				arg++;
#ifndef WIN32
				tic=atof(argv[arg]);
#endif
			}
		}
		arg++;
	}

	p[0].mxsize=1<<p[0].mxsize;
	p[0].minsize=1<<p[0].minsize;

	/* set high process priority */
#ifdef WIN32
	procID = GetCurrentProcessId ();
	hProcess = OpenProcess(PROCESS_ALL_ACCESS,TRUE,procID);
	SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);
#else /* unix */
	setpriority(PRIO_PROCESS, 0,-20);    /* linux has no bind_to_cpu call */
#endif


#ifdef WIN32
	printf(  "Evaluated Clock Resolution: %.2f MHz\n\n",tic);
#else
	printf(  "Specified/Evaluated Clock Resolution (Option -t): %.2f MHz\n\n",tic);
#endif

	/* allocate shared memory (only once for all repetitions/modes */
#ifdef SHAREDMEM
	printf("Allocation of Shared Memory!\n");
	if ((shmid=shmget(IPC_PRIVATE,sizeof(double)*p[0].mxsize,IPC_CREAT | 0666))
		==-1) {perror("shmget");exit(99);}
	if ((shared = (double *) shmat(shmid,0,SHM_RND))==(double *) -1) {
		perror("shmat\n"); exit(99);
	}
#endif /* SHAREDMEM */

	for (modenr=0;modenr<=3;modenr++) {
		if ((modenr==modes) || (modes==9)) {
			p[0].mode=modenr;

			for (currit=1;currit<=nrofrep;currit++) {
				p[0].currentrep=currit;
				for (i=1;i<MXPROC;i++) {
					memcpy (&p[i],&p[0], sizeof(paramT));
				}

				switch (p[0].mode) {
				case 0:
					printf("Load Sum (%d)    - Working Set: %.0f KByte; Strides: %d\n",currit, (float) p[0].mxsize*8/1024,p[0].mxstrds);
					break;
				case 1:
					printf("Const Store (%d) - Working Set: %.0f KByte; Strides: %d\n",currit, (float) p[0].mxsize*8/1024,p[0].mxstrds);
					break;
				case 2:
					printf("Load Copy (%d)   - Working Set: 2*%.0f KByte; Strides: %d\n",currit, (float) p[0].mxsize*8/1024,p[0].mxstrds);
					break;
				case 3:
					printf("Copy Store (%d)  - Working Set: 2*%.0f KByte; Strides: %d\n",currit, (float) p[0].mxsize*8/1024,p[0].mxstrds);
					break;
				}
				if (p[0].npes==1)
					printf("                  Starting 1 process...\n                  Test running...\n");
				else
					printf("                  Starting %d processes...\n                  Tests running...\n", p[0].npes );

	/* start parallel execution */
#ifdef WIN32
				for (i=0;i<p[0].npes;i++) {

					p[i].par_cid=i;
				/*printf("Proc: %d, parcid: %d\n",i,p[i].par_cid);
				printf("Address %d\n",&p[i]);
				fflush(stdout);
				*/
					hThread[i]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)memop,&p[i],0,&IDThread);

					if (hThread[i]==NULL) {
						fprintf(stderr, "Create Thread error\n");
						exit(0);
					}
				}

			/* wait for termination of child-threads */
				WaitForMultipleObjects (p[0].npes, hThread, TRUE, INFINITE);

#else  /* unix */

			/* init semaphores for barrier */
				sem_init();

				begin_parallel(p[0].npes);
				p[par_cid].par_cid=par_cid;

   /*
			printf("Proc: %d, parcid: %d\n",par_cid,p[par_cid].par_cid);
			printf("Address %d\n",&p[par_cid]);
			*/

				memop(&p[par_cid]);
				barrier();
				end_parallel();

				sem_deinit();

#endif /* WIN32 */
			}
		 analyze_rep(&p[0]);
		}
	}

	/* detach & destroy shared memory */
#ifdef SHAREDMEM
	if ((shmdt(shared))==-1) {
		perror("shmdt\n"); exit(99);
	}
	if ((shmctl(shmid,IPC_RMID,0))==-1) {
		perror("ShmRelease"); exit(99);
	}
#endif /* SHAREDMEM */

	free(p);
	return 0;
}