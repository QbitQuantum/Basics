void main(int argc, char *argv[])
{
	clock_t startCPU;
	time_t startTime;
	double elapsedTime, cpuTime;
	uint64_t clock_reg;

	int pf0 = getPagefault();	

#ifdef SMARTHEAP
	MemRegisterTask();
#endif

	setbuf(stdout, NULL);  /* turn off buffering for output */

	if (argc > 1)
		fin = fopen(argv[1], "r");
	else
		fin = stdin;
	if (argc > 2)
		fout = fopen(argv[2], "w");
	else
		fout = stdout;

	if(fin == NULL || fout == NULL) {
		fprintf(stderr, "Could not open file(s): ");
		int i=1;
		for(i=1; i<argc;i++) {
			fprintf(stderr, "%s ", argv[i]);
		}
		fprintf(stderr, "\n");
		exit(-1);
	}

	ulCallCount = promptAndRead("call count", ulCallCount, 'u');
	uMinBlockSize = (unsigned)promptAndRead("min block size",uMinBlockSize,'u');
	uMaxBlockSize = (unsigned)promptAndRead("max block size",uMaxBlockSize,'u');

#ifdef HEAPALLOC_WRAPPER
	LoadLibrary("shsmpsys.dll");
#endif

#ifdef SYS_MULTI_THREAD
	{
		unsigned i;
		void *threadArg = NULL;
		ThreadID *tids;

#ifdef WIN32
		//unsigned uCPUs = promptAndRead("CPUs (0 for all)", 0, 'u');

		if (uCPUs)
		{
			DWORD m1, m2;

			if (GetProcessAffinityMask(GetCurrentProcess(), &m1, &m2))
			{
				i = 0;
				m1 = 1;

				/*
				 * iterate through process affinity mask m2, counting CPUs up to
				 * the limit specified in uCPUs
				 */
				do
					if (m2 & m1)
						i++;
				while ((m1 <<= 1) && i < uCPUs);

				/* clear any extra CPUs in affinity mask */
				do
					if (m2 & m1)
						m2 &= ~m1;
				while (m1 <<= 1);

				if (SetProcessAffinityMask(GetCurrentProcess(), m2))
					fprintf(fout,
							"\nThreads in benchmark will run on max of %u CPUs", i);
			}
		}
#endif /* WIN32 */

		uThreadCount = uCPUs;//(int)promptAndRead("threads", GetNumProcessors(), 'u');

		if (uThreadCount < 1)
			uThreadCount = 1;
		ulCallCount /= uThreadCount;
		if ((tids = malloc(sizeof(ThreadID) * uThreadCount)) != NULL)
		{
			startCPU = clock();
			startTime = time(NULL);
			clock_reg = rdtsc();
                        UPDATENETMEM(mallinfo().uordblks + ulCallCount * sizeof(void *));

			for (i = 0;  i < uThreadCount;  i++) {
				if (THREAD_EQ(tids[i] = RunThread(doBench, threadArg),THREAD_NULL))
				{
					fprintf(fout, "\nfailed to start thread #%d", i);
					break;
				}
			}
			WaitForThreads(tids, uThreadCount);
			free(tids);
		}
		if (threadArg)
			free(threadArg);
	}
#else
        UPDATENETMEM(mallinfo().uordblks + ulCallCount * sizeof(void *));
	startCPU = clock();
	startTime = time(NULL);
	clock_reg = rdtsc();
	doBench(NULL);
#endif

	uint64_t cpuTime_reg = (rdtsc() - clock_reg);
	elapsedTime = difftime(time(NULL), startTime);
	cpuTime = (double)(clock()-startCPU) / (double)CLK_TCK;
//	cpuTime = (double)(clock()-startCPU);
//	uint64_t cpuTime_reg = (rdtsc() - clock_reg) / 2246796049;

	fprintf_silent(fout, "\n");
#ifdef PRINTTHROUGHPUT
	fprintf(fout, "throughput %ld", (long) (cpuTime_reg));
#endif
	fprintf(fout, "\nTotal elapsed time"
#ifdef SYS_MULTI_THREAD
			" for %d threads"
#endif
			": %.2f (%.4f CPU) (%ld clock ticks read from register)\n",
#ifdef SYS_MULTI_THREAD
			uThreadCount,
#endif
			elapsedTime, cpuTime, cpuTime_reg);

	if (fin != stdin)
		fclose(fin);
	if (fout != stdout)
		fclose(fout);
	
	printf("Occurred page faults: %d\n", getPagefault() - pf0);
}