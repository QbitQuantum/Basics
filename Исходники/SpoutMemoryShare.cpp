//---------------------------------------------------------
bool spoutMemoryShare::Initialize()
{
	#ifdef CONSOLE_DEBUG
	DWORD errnum;
	#endif

	// Have semaphore names been set ?
	if(!szShareMemoryName[0]) {
		setSharedMemoryName("spoutMemoryShare");
	}

	// Create or open read semaphore depending, on whether it already exists or not
	hReadSemaphore = CreateSemaphoreA ( 
						NULL,	// default security attributes
						1,		// initial count (do not allow a read until write allows it)
						1,		// maximum count
						(LPSTR)szReadSemaphoreName);

    if (hReadSemaphore == NULL) {
		#ifdef CONSOLE_DEBUG
        printf("Create Read Semaphore error\n");
		#endif
        return false;
    }
	#ifdef CONSOLE_DEBUG
	else {
		errnum = GetLastError();
		// printf("Read Semaphore GetLastError() = %d\n", errnum);
		if(errnum == ERROR_INVALID_HANDLE) {
			printf("Read Semaphore invalid handle\n");
		}
		if(errnum == ERROR_ALREADY_EXISTS) {
			printf("Read Semaphore [%s] already exists\n", szReadSemaphoreName);
		}
		else {
			printf("Read Semaphore [%s] created\n", szReadSemaphoreName);
		}
	}
	#endif

	hWriteSemaphore = CreateSemaphoreA ( 
						NULL,   // default security attributes
						1,		// initial count (allow write)
						1,		// maximum count
						(LPSTR)szWriteSemaphoreName);

    if (hWriteSemaphore == NULL) {
		#ifdef CONSOLE_DEBUG
        printf("Create Write Semaphore error\n");
		#endif
        return false;
    }
	#ifdef CONSOLE_DEBUG
	else {
		errnum = GetLastError();
		// printf("Write Semaphore GetLastError() = %d\n", errnum);
		if(errnum == ERROR_INVALID_HANDLE) {
			printf("Write Semaphore invalid handle\n");
		}
		if(errnum == ERROR_ALREADY_EXISTS) {
			printf("Write Semaphore [%s] already exists\n", szWriteSemaphoreName);
		}
		else {
			printf("Write Semaphore [%s] created\n", szWriteSemaphoreName);
		}
	}
	#endif

	// Each time a thread completes a wait for a semaphore object, 
	// the count of the semaphore object is decremented by one. 
	// When the thread has finished, it calls the ReleaseSemaphore function, 
	// which increments the count of the semaphore object.
     
    // Set up Shared Memory
	// allocate space for an rgb bitmap the size of the desktop, then nothing will be bigger
	DWORD size = (DWORD)( sizeof(BITMAPINFOHEADER)+GetSystemMetrics(SM_CXSCREEN)*GetSystemMetrics(SM_CYSCREEN)*3 );

    // Create or open shared memory, depending on whether it already exists or not
	// Must be CreateFileMappingA, not CreateFileMapping or it doesn't work
    hSharedMemory = CreateFileMappingA ( INVALID_HANDLE_VALUE,			// use paging file
										 NULL,							// default security 
										 PAGE_READWRITE,				// read/write access
										 0,								// max. object size 
										 size,							// buffer size  
										 (LPCSTR)szShareMemoryName);	// name of mapping object
	
    if (hSharedMemory == NULL || hSharedMemory == INVALID_HANDLE_VALUE) { 
		#ifdef CONSOLE_DEBUG
		printf("Error occured while creating file mapping object : %d\n", GetLastError() );
		#endif
        return false;
    }
	#ifdef CONSOLE_DEBUG
	else {
		errnum = GetLastError();
		// printf("map name = %s : GetLastError() = %d\n", szShareMemoryName, errnum);
		if(errnum == ERROR_INVALID_HANDLE) {
			printf("map invalid handle\n");
		}
		if(errnum == ERROR_ALREADY_EXISTS) {
			printf("map already exists\n");
			// here we can set bIsClient also
		}
		else {
			printf("map created OK\n");
		}
	}
	#endif

    pBuffer = (LPTSTR)MapViewOfFile(	hSharedMemory,			// handle to map object
										FILE_MAP_ALL_ACCESS,	// read/write permission
										0,                   
										0,                   
										size);

    if (NULL == pBuffer) { 
		#ifdef CONSOLE_DEBUG
		printf("Error occured while mapping view of the file : %d\n", GetLastError() );
		#endif
        return false;
    }

	// ==== SEMAPHORES ====

     
    return true;

} // end Initialize