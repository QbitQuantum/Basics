//
// Create a memory-mapping to the Freetrack data.
// It contains the tracking data, a handle to the main-window and the program-name of the Game!
//
//
bool FTCreateMapping()
{
	bool bMappingExists = false;

	//
	// Memory-mapping already exists!
	//
	if ( pMemData != NULL ) {
		return true;
	}

    dbg_report("FTCreateMapping request (pMemData == NULL).\n");

	//
	// A FileMapping is used to create 'shared memory' between the FTClient and the FTServer.
	//
	// Try to create a FileMapping to the Shared Memory. This is done to check if it's already there (what
	// may mean the face-tracker program is already running).
	//
	// If one already exists: close it and open the file-mapping to the existing one.
	//
	hFTMemMap = CreateFileMappingA( INVALID_HANDLE_VALUE , 00 , PAGE_READWRITE , 0 , 
		                           sizeof( FTMemMap ), 
								   (LPCSTR) FT_MM_DATA );

	if ( ( hFTMemMap != 0 ) && ( GetLastError() == ERROR_ALREADY_EXISTS ) ) {
		dbg_report("FTCreateMapping: Mapping already exists.\n");
		bMappingExists = true;				// So the server was (probably) already started!
		CloseHandle( hFTMemMap );
		hFTMemMap = 0;
	}

	//
	// Create a new FileMapping, Read/Write access
	//
    hFTMemMap = OpenFileMappingA( FILE_MAP_WRITE , false , (LPCSTR) FT_MM_DATA );
	if ( ( hFTMemMap != 0 ) ) {
		dbg_report("FTCreateMapping: Mapping opened.\n");
        pMemData = (FTMemMap *) MapViewOfFile(hFTMemMap, FILE_MAP_WRITE, 0, 0, sizeof( FTMemMap ) );
	    hFTMutex = CreateMutexA(NULL, false, FREETRACK_MUTEX);
	}
	else {
		return false;
	}
	return true;
}