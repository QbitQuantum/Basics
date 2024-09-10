void main(void)
{
	const int nTimerUnitsPerSecond = 10000000;
	int cAbrasionCount = 0;
	SYSTEMTIME st;
	LARGE_INTEGER li;
	
	HANDLE hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	GetLocalTime(&st);
	printf("Start time: \t\t%.2d:%.2d:%.2d\n\n", st.wHour, st.wMinute, st.wSecond);
	li.QuadPart = -(15 * nTimerUnitsPerSecond);
	if (SetWaitableTimer(hTimer, &li, 15 * 1000, NULL, NULL, FALSE)){
		while (TRUE){
			GetLocalTime(&st);
			cAbrasionCount++;
			printf("%d.Timer abrasion: \t%.2d:%.2d:%.2d\n", cAbrasionCount, st.wHour, st.wMinute, st.wSecond);

			hSecThread = CreateThread(NULL, 0, ThreadFunc1, (LPVOID)cAbrasionCount, 0, &dwSecThreadId);
			
			DWORD dw = WaitForSingleObject(hTimer, INFINITE);
			
			TerminateThread(hSecThread, 1001);
			hSecThread = NULL;
			dwSecThreadId = 0;
		}
	}
}