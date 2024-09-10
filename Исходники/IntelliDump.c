BOOL __stdcall DumpProcessRange( IN DWORD dwProcessId, IN void* pStartAddr, IN DWORD dwcBytes, OUT void* pDumpedBytes, OUT char* szErrorStr)
{
	BOOL                       bRet;
	HANDLE                     hProc;
	DWORD                      cb, cbFailure = 0, cb2Do, dwBlockSize;
	MEMORY_BASIC_INFORMATION   minfo;
	char                       cBuff[100];

	// get process handle
	hProc = OpenProcess( PROCESS_VM_READ, FALSE, dwProcessId );
	if ( !hProc )
	{
		lstrcpy( szErrorStr, "Error while querying process handle !" );
		return FALSE; // ERR
	}

	//
	// first let's try 2 dump the whole block directly
	//
	bRet = ReadProcessMemory( hProc, pStartAddr, pDumpedBytes, dwcBytes, &cb );
	CloseHandle( hProc );
	if ( bRet )
		goto TidyUp;

	//
	// scan the memory information
	//
	hProc = OpenProcess( PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, dwProcessId );
	if ( !hProc )
	{
		lstrcpy( szErrorStr, "Error while querying process handle !" );
		return FALSE; // ERR
	}

	cb2Do              = dwcBytes;
	minfo.BaseAddress  = pStartAddr;
	while ( cb2Do )
	{
		// get memory info
		bRet = VirtualQueryEx(
			hProc,
			minfo.BaseAddress,
			&minfo, sizeof(minfo));
		if ( !bRet )
		{
			lstrcpy( szErrorStr, "VirtualQueryEx() failed !" );
			goto TidyUp; // ERR
		}

		#define f  minfo.Protect

		dwBlockSize = min( minfo.RegionSize, cb2Do );
		if ( pStartAddr ) // first region dump ?
			dwBlockSize -= (DWORD)pStartAddr - (DWORD)minfo.BaseAddress;

		if ( ((f & PAGE_GUARD)     != 0) || // do we have access there ?
			 ((f & PAGE_NOACCESS)  != 0) )
		{
			//
			// don't try 2 dump this memory part
			//

			// zero not dumped part in output buffer
			memset(
				MakePtr( PVOID, pDumpedBytes, dwcBytes - cb2Do ),
				0,
				dwBlockSize);
			cbFailure += dwBlockSize;
		}
		else
		{
			//
			// dump normally
			//

			bRet = ReadProcessMemory(
				hProc,
				pStartAddr ? pStartAddr : minfo.BaseAddress,
				MakePtr( PVOID, pDumpedBytes, dwcBytes - cb2Do ),
				dwBlockSize,
				&cb);
			if ( pStartAddr ) // only non-zero  on first region dump
				pStartAddr = NULL;
			if ( !bRet )
			{
				// OK,no...zero not dumped part in output buffer
				memset(
					MakePtr( PVOID, pDumpedBytes, dwcBytes - cb2Do ),
					0,
					dwBlockSize);
				cbFailure += dwBlockSize;				
			}
		}

		// adjust vars
		minfo.BaseAddress   = MakePtr( PVOID, minfo.BaseAddress, minfo.RegionSize );
		cb2Do              -= dwBlockSize;
	}

	bRet = TRUE; // ret an OK

	if ( cbFailure ) // were any bytes not dumpable ?
	{
		wsprintf(
			cBuff,
			"0x%X of 0x%X bytes could not be dumped\nand were padded with zeros.",
			cbFailure, dwcBytes);
		MessageBox( GetActiveWindow(), cBuff, "IntelliDump", MB_ICONWARNING );
	}

	//
	// tidy up
	//
TidyUp:
	CloseHandle( hProc );

	return bRet;
}