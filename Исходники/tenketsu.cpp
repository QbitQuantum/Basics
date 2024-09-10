DWORD WINAPI tenkBackChannel(LPVOID lpvParam) {
	HANDLE		hPipe;
	TCHAR		buf[BUFSIZE+1];
	ULONG		bytesRead, bytesWritten;
	BOOL		fSuccess;
	ULONG64		funcAddr64;
	ULONG		*funcAddr, i;
	

	struct AllocateStruct	*aStruct = (struct AllocateStruct *)buf;
	struct ReallocateStruct	*rStruct = (struct ReallocateStruct *)buf;
	struct FreeStruct		*fStruct = (struct FreeStruct *)buf;
	struct CreateStruct		*cStruct = (struct CreateStruct *)buf;
	struct DestroyStruct	*dStruct = (struct DestroyStruct *)buf;
	struct CoalesceStruct	*cfbStruct = (struct CoalesceStruct *)buf;

	
	hPipe = (HANDLE) lpvParam;
	
	dprintf("[Byakugan] Waiting for named pipe connection...\n");

	for(;!ConnectNamedPipe(hPipe, NULL) == TRUE;) { dprintf("[B] waiting for connection...\n"); }

	dprintf("[Byakugan] Connected to back channel. :)\n");

	// Load addresses from symbols if possible for undoumented interfaces
	i = 0;
	while (undocdFunc[i] != NULL) {
		dprintf("[T] Sending address of %s\n", undocdFunc[i]);
		fSuccess = WriteFile(hPipe, &(undocdAddr[i]), sizeof(ULONG), &bytesWritten, NULL);
		if (!fSuccess || bytesWritten != sizeof(ULONG))
			dprintf("[T] Failed to send address of %s\n", undocdFunc[i]);
		i++;
	}
	//FlushFileBuffers(hPipe);
	dprintf("[T] Sent addresses of %d undocumented functions.\n", i);

	initializeHeapModel(&heapModel);

#undef THREEDHEAPFU_ENABLED //Place this in setup.bat

#if 0 //#ifdef THREEDHEAPFU_ENABLED
//Create a heap event proxy, play these back out to 3dheapfu
LPTSTR	lpszProxyPipename = TEXT("\\\\.\\pipe\\tenketsuProxy");
BOOL	fProxySuccess;
DWORD	dwProxyMode	= PIPE_READMODE_MESSAGE;
ULONG   bytesProxyWritten;
static BOOL	fDontAttemptProxyWrite = false;

HANDLE hProxyPipe = CreateFile(lpszProxyPipename,
								GENERIC_READ | GENERIC_WRITE,
								0,
								NULL,
								OPEN_EXISTING,
								0,
								NULL);

			if (hProxyPipe == INVALID_HANDLE_VALUE)
					dprintf("hProxyPipe == invalid handle\n");
			else
					dprintf("hProxyPipe == good\n");
			SetNamedPipeHandleState(hProxyPipe, &dwProxyMode, NULL, NULL); //?

#endif

	while (1) {
		fSuccess = ReadFile(	hPipe,
								buf,
								BUFSIZE*sizeof(TCHAR),
								&bytesRead,
								NULL);
		if (!fSuccess || bytesRead == 0) {
			dprintf("[Byakugan] ReadFile failed, or read 0 bytes.\n");
			continue;
		}
#if 0 //#ifdef THREEDHEAPFU_ENABLED
		//dprintf("jc: receieved an event of size %d. Forwarding on to ProxyPipe\n", bytesRead);
		//WriteFile(hPipe, &freeinfo, sizeof(struct FreeStruct), &bytesWritten, NULL);

		if (!fDontAttemptProxyWrite)
		{
			fProxySuccess = WriteFile(hProxyPipe, buf, bytesRead, &bytesProxyWritten, NULL); 
			if (bytesRead != bytesProxyWritten)
			{
				dprintf("Partial write to proxy on last event! ;(\n");
				dprintf("event size was %d. wrote %d\n", bytesRead, bytesProxyWritten);
				dprintf("Disabling message proxying until explicitly enabled.\n");
				fDontAttemptProxyWrite = true;
			}
		}

#endif
		switch ( *((BYTE *) buf) ) {
			case ALLOCATESTRUCT:
				//dprintf("[T] New Chunk @ 0x%08x\n", aStruct->ret);
				//dprintf("Heap: 0x%08x\tFlags: 0x%08x\tSize: 0x%08x\n\n", 
				//		aStruct->heapHandle, aStruct->flags, aStruct->size);
				if (heapModel.state & MODEL) heapAllocate(&heapModel, aStruct);
				if (heapModel.state & LOG) logAllocate(&heapModel, aStruct);
				break;

			case REALLOCATESTRUCT:
				//dprintf("[T] Realloc'd Chunk @ 0x%08x\n", rStruct->ret);
				//dprintf("Heap: 0x%08x\tFlags: 0x%08x\tSize: 0x%08x\n", 
				//		rStruct->heapHandle, rStruct->flags, rStruct->size);
				//if (rStruct->ret !=  (PVOID) rStruct->memoryPointer)
				//	dprintf("Replaces chunk @ 0x%08x\n", rStruct->memoryPointer);
				//dprintf("\n");
				if (heapModel.state & MODEL) heapReallocate(&heapModel, rStruct);
				if (heapModel.state & LOG) logReallocate(&heapModel, rStruct);
				break;

			case FREESTRUCT:
				//dprintf("[T] Free'd Chunk @ 0x%08x\n", fStruct->memoryPointer);
				//dprintf("Heap: 0x%08x\tFlags: 0x%08x\n\n", fStruct->heapHandle, fStruct->flags);
				if (heapModel.state & MODEL) heapFree(&heapModel, fStruct);
				if (heapModel.state & LOG) logFree(&heapModel, fStruct);
				break;

			case CREATESTRUCT:
				dprintf("[T] New Heap: 0x%08x\n", cStruct->ret);
				dprintf("Base: 0x%08x\tReserve: 0x%08x\tFlags: 0x%08x\n",
						cStruct->base, cStruct->reserve, cStruct->flags);
				//dprintf("Commit: 0x%08x\tLock: 0x%08x\n\n", cStruct->commit, cStruct->lock);
				if (heapModel.state & MODEL) heapCreate(&heapModel, cStruct);
				break;

			case DESTROYSTRUCT:
				dprintf("[T] Heap Destroyed: 0x%08x\n\n", dStruct->heapHandle);
				if (heapModel.state & MODEL) heapDestroy(&heapModel, dStruct);
				break;
			
			case COALESCESTRUCT:
				//dprintf("[T] Free Block Consolidation (returned 0x%08x)\n", cfbStruct->ret);
				//dprintf("Heap: 0x%08x\tArg2: 0x%08x\tArg3: 0x%08x\tArg4: 0x%08x\n\n",
				//		cfbStruct->heapHandle, cfbStruct->arg2, cfbStruct->arg3, cfbStruct->arg4);
				if (heapModel.state & MODEL) heapCoalesce(&heapModel, cfbStruct);
				break;

			default:
				dprintf("[Byakugan] Tenketsu: Unrecognized data was returned.\n");
		}

	}


	return (0);
}