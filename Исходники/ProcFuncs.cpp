DWORD ListThreadProcess(DWORD PID)
{
	HANDLE hThreadSnap;
	THREADENTRY32 t;
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	t.dwSize = sizeof(THREADENTRY32);
	if (!Thread32First(hThreadSnap, &t))
		return (-1);
	do
	{
		if (t.th32OwnerProcessID == PID)
		{
			printf("#### THREAD %d ####\n",t.th32ThreadID);
			printf("\tThread FLAG           : %d\n", t.dwFlags);
			printf("\tThread USAGE          : %d\n", t.cntUsage);
			printf("\tThread BASE PRIORITY  : %d\n", t.tpBasePri);
			printf("\tThread DELTA PRIORITY : %d\n\n", t.tpDeltaPri);
		}
	} while (Thread32Next(hThreadSnap, &t));
	return(1);
}