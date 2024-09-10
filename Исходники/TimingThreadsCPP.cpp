ULONG WINAPI Delegate(__in PVOID p){
	int finalTime;
	ULONG timeEnd, timeStart;
	__int64 startCycleClock, endCycleClock;
	HANDLE t1, t2;
	printf("-----------------------------------------\n");
	printf("Switching Windows Threads\n");
	
	t1 = CreateThread( NULL, 0, Switch, NULL, CREATE_SUSPENDED, NULL);
	t2 = CreateThread( NULL, 0, Switch, NULL, CREATE_SUSPENDED, NULL);

	startCycleClock = __rdtsc();
	timeStart = GetTickCount();
	
	ResumeThread(t1);
	ResumeThread(t2);
	WaitForSingleObject(t1, INFINITE);
	WaitForSingleObject(t2, INFINITE);

	timeEnd = GetTickCount();
	endCycleClock = __rdtsc();

	finalTime = (int)(((timeEnd-timeStart) * 1000000) / (COUNT*2));
	printf("Absolute Time is %d ns\n", finalTime);
	printf("Number of Cycles %d\n",(endCycleClock-startCycleClock)/(COUNT*2));
	return 0;
}