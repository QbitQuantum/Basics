BOOLEAN FBaseMain(
		 IN PVOID DllHandle,
		 ULONG Reason,
		 IN PCONTEXT Context OPTIONAL)
					
{
	static TCHAR szDumpFile[15];
	USHORT Type;
	void FreeMemoryOfHandle();

	// if process is attaching, initialize the dll
    if (Reason == DLL_PROCESS_ATTACH) {
   		GdiSetBatchLimit (1);
		FileSyncProfInitDll();
	}
    else if (Reason == DLL_THREAD_ATTACH) {
   		GdiSetBatchLimit (1);
	}
    else if (Reason == DLL_PROCESS_DETACH) {

		lstrcpy ((LPTSTR)szDumpFile, MODULE_NAME);
		lstrcat ((LPTSTR)szDumpFile, L".end");
		FileSyncProfDumpData ((LPTSTR)szDumpFile);
		WaitForSingleObject ( hMutex, INFINITE );
		FreeMemoryOfList (phInactive);
		FreeMemoryOfList (phActive);
		FreeMemoryOfHandle (phDuplicated);
		phActive = phInactive = phDuplicated = (PFP_Handle) NULL;
		ReleaseMutex ( hMutex );
		for ( Type = 0; Type < NUMOFSYNC; ) {
			WaitForSingleObject ( hSMutex[Type], INFINITE );
			FreeMemoryOfSList (phSInactive[Type]);
			FreeMemoryOfSList (phSActive[Type]);
			FreeMemoryOfSHandle (phSDuplicated[Type]);
			phSActive[Type] = phSInactive[Type] = phSDuplicated[Type]
			                = (PSP_Handle) NULL;
			ReleaseMutex ( hSMutex[Type++] );
		}

        // Clean-up

        CloseHandle ( hDumpEvent );
        CloseHandle ( hClearEvent );
        UnmapViewOfFile ( (LPVOID) tszDumpFileName );
        CloseHandle ( hDumpFileMapping );
        CloseHandle ( hWaitingForDumpThread );
        CloseHandle ( hWaitingForClearThread );

        CloseHandle ( hMutex );
		for ( Type = 0; Type < NUMOFSYNC; )
		CloseHandle ( hSMutex[Type++] );
	}
	return(TRUE);
}