int CSysinfo::GetTIDs (pid_t pid, ExtArray<DWORD> & tids)
{
	DWORD s = 0;

	if ( !IsWin2k ) {
		/*** Window NT 4.0 Specific Code -- this does not work on Win2k! ***/
		DWORD *block;
		Refresh();
		block = FindBlock (pid);
		if (!block)
			return 0;
		for (s=0; s < *(block+1); s++)
		{
			tids[s] = *(block+43+s*16);	
			// tstatus[s] = *(block+48+s*16) + (*(block+47+s*16)<<8);
		}
		return (int)s;
	}
			
	/******** Win2k Specific Code -- use spiffy new Toolhelp32 calls ***/

	HANDLE        hThreadSnap = NULL; 
    THREADENTRY32 te32        = {0}; 
 
    // Take a snapshot of all threads currently in the system. 

    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); 
    if (hThreadSnap == (HANDLE)-1) 
	{
		// dprintf(D_DAEMONCORE,"CreateToolhelp32Snapshot failed\n");
        return 0;
	}
 
    // Fill in the size of the structure before using it. 

    te32.dwSize = sizeof(THREADENTRY32); 
 
    // Walk the thread snapshot to find all threads of the process. 
    // If the thread belongs to the process, add its information 
    // to the list.
    if (Thread32First(hThreadSnap, &te32)) 
    { 
        do 
        { 
            if (te32.th32OwnerProcessID == pid) 
            { 
				tids[s] = te32.th32ThreadID;	
				s++;
            } 
        } 
        while (Thread32Next(hThreadSnap, &te32)); 
    } 
 
    // Do not forget to clean up the snapshot object. 
	CloseHandle (hThreadSnap); 
	
	return (int)s;		
}