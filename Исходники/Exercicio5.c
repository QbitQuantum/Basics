BOOL MEMINFO_API C_GetProcMemInfo(_In_  DWORD  dwProcId, _Out_  PPROCMEMINFO_C pProcMemInfo){
	HANDLE hProc = NULL;
	MEMORYSTATUSEX status;
	PROCESS_MEMORY_COUNTERS procMemCtr;

	printf("\n\n~~~~ INFORMACAO LOCAL DO PROCESSO ~~~~~");

	status.dwLength = sizeof (status);

	if (hProc = OpenProcess(PROCESS_VM_READ|PROCESS_QUERY_INFORMATION, FALSE, dwProcId) == NULL || !GlobalMemoryStatusEx(&status) ||
		!GetProcessMemoryInfo(hProc, &procMemCtr, sizeof(PROCESS_MEMORY_COUNTERS))){
		printf("ERROR: %s\n", GetLastError());
		return FALSE;
	}

	printf("\nProcess ID = %u", GetProcessId(hProc));
	printf("\nTotal de espaco de enderecamento virtual existente: %llu KiB = %llu MiB", status.ullTotalVirtual / KiloB, status.ullTotalVirtual / MegaB);
	printf("\nTotal de espaco de enderecamento virtual disponivel: %llu KiB = %llu MiB", status.ullAvailVirtual / KiloB, status.ullAvailVirtual / MegaB);
	printf("\nDimensao do Working Set: %u KiB = %.2f MiB", procMemCtr.WorkingSetSize / KiloB, (double)procMemCtr.WorkingSetSize / MegaB);

	// Afectar a struct _out_
	pProcMemInfo->processId = dwProcId;
	pProcMemInfo->workingSetSize = procMemCtr.WorkingSetSize;
	pProcMemInfo->totalVirtualSpace = status.ullTotalVirtual;
	pProcMemInfo->availableVirtualSpace = status.ullAvailVirtual;

	printf("\n\nClique em qualquer tecla para terminar..."); getchar();
	CloseHandle(hProc);
	return TRUE;
}