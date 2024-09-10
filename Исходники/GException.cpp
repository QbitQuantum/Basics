GCallStack::GCallStack(HANDLE hThread, CONTEXT& c)
{
	DWORD imageType = IMAGE_FILE_MACHINE_I386;
	HANDLE hProcess = GetCurrentProcess();

	int frameNum; // counts walked frames

#if defined(_LINUX64) || defined(_WIN64) || defined(_IOS)
	unsigned __int64 offsetFromSymbol; // tells us how far from the symbol we were
#else
	DWORD offsetFromSymbol; // tells us how far from the symbol we were
#endif



	DWORD symOptions; // symbol handler settings
	IMAGEHLP_SYMBOL *pSym = (IMAGEHLP_SYMBOL *) malloc( IMGSYMLEN + MAXNAMELEN );
	char undFullName[MAXNAMELEN]; // undecorated name with all shenanigans

	IMAGEHLP_MODULE Module;
	IMAGEHLP_LINE Line;
	std::string symSearchPath;
	char *tt = 0, *p;

	STACKFRAME s; // in/out stackframe
	memset( &s, '\0', sizeof s );

	tt = new char[TTBUFLEN];

	// build symbol search path from:
	symSearchPath = "";
	// current directory
	if ( GetCurrentDirectory( TTBUFLEN, tt ) )
		symSearchPath += tt + std::string( ";" );
	// dir with executable
	if ( GetModuleFileName( 0, tt, TTBUFLEN ) )
	{
		for ( p = tt + strlen( tt ) - 1; p >= tt; -- p )
		{
			// locate the rightmost path separator
			if ( *p == '\\' || *p == '/' || *p == ':' )
				break;
		}
		// if we found one, p is pointing at it; if not, tt only contains
		// an exe name (no path), and p points before its first byte
		if ( p != tt ) // path sep found?
		{
			if ( *p == ':' ) // we leave colons in place
				++ p;
			*p = '\0'; // eliminate the exe name and last path sep
			symSearchPath += tt + std::string( ";" );
		}
	}
	// environment variable _NT_SYMBOL_PATH
	if ( GetEnvironmentVariable( "_NT_SYMBOL_PATH", tt, TTBUFLEN ) )
		symSearchPath += tt + std::string( ";" );
	// environment variable _NT_ALTERNATE_SYMBOL_PATH
	if ( GetEnvironmentVariable( "_NT_ALTERNATE_SYMBOL_PATH", tt, TTBUFLEN ) )
		symSearchPath += tt + std::string( ";" );
	// environment variable SYSTEMROOT
	if ( GetEnvironmentVariable( "SYSTEMROOT", tt, TTBUFLEN ) )
		symSearchPath += tt + std::string( ";" );

	if ( symSearchPath.size() > 0 ) // if we added anything, we have a trailing semicolon
		symSearchPath = symSearchPath.substr( 0, symSearchPath.size() - 1 );

	// why oh why does SymInitialize() want a writeable string?
	strncpy( tt, symSearchPath.c_str(), TTBUFLEN );
	tt[TTBUFLEN - 1] = '\0'; // if strncpy() overruns, it doesn't add the null terminator

	// init symbol handler stuff (SymInitialize())
	if ( ! SymInitialize( hProcess, tt, false ) )
	{
		goto tagCleanUp;
	}

	symOptions = SymGetOptions();
	symOptions |= SYMOPT_LOAD_LINES;
	symOptions &= ~SYMOPT_UNDNAME;
	SymSetOptions( symOptions ); // SymSetOptions()

	enumAndLoadModuleSymbols( hProcess, GetCurrentProcessId() );

	// init STACKFRAME for first call
	// Notes: will have to be #ifdef-ed for Alphas; MIPSes are dead anyway,
#ifndef _WIN64
	s.AddrPC.Offset = c.Eip;
	s.AddrPC.Mode = AddrModeFlat;
	s.AddrFrame.Offset = c.Ebp;
	s.AddrFrame.Mode = AddrModeFlat;
#endif

	memset( pSym, '\0', IMGSYMLEN + MAXNAMELEN );
	pSym->SizeOfStruct = IMGSYMLEN;
	pSym->MaxNameLength = MAXNAMELEN;

	memset( &Line, '\0', sizeof Line );
	Line.SizeOfStruct = sizeof Line;

	memset( &Module, '\0', sizeof Module );
	Module.SizeOfStruct = sizeof Module;

	offsetFromSymbol = 0;

	for ( frameNum = 0; ;)
	{
		// get next stack frame (StackWalk(), SymFunctionTableAccess(), SymGetModuleBase())
		// if this returns ERROR_INVALID_ADDRESS (487) or ERROR_NOACCESS (998), you can
		// assume that either you are done, or that the stack is so hosed that the next
		// deeper frame could not be found.
		if ( ! StackWalk( imageType, hProcess, hThread, &s, &c, NULL,
			SymFunctionTableAccess, SymGetModuleBase, NULL ) )
			break;

		if ( s.AddrPC.Offset != 0 )
		{ // we seem to have a valid PC
			// show procedure info (SymGetSymFromAddr())
			if ( ! SymGetSymFromAddr( hProcess, s.AddrPC.Offset, &offsetFromSymbol, pSym ) )
			{
				break;
			}
			else
			{
				// UnDecorateSymbolName()
				UnDecorateSymbolName( pSym->Name, undFullName, MAXNAMELEN, UNDNAME_COMPLETE );
				if (!frameNum && strstr(undFullName, "Exception"))
					continue;
				_stk += undFullName;
			}
		} // we seem to have a valid PC

		// no return address means no deeper stackframe
		if ( s.AddrReturn.Offset == 0 )
		{
			// avoid misunderstandings in the printf() following the loop
			SetLastError( 0 );
			break;
		}
		++frameNum;
	}

	// de-init symbol handler etc. (SymCleanup())
	SymCleanup( hProcess );
	free( pSym );
tagCleanUp:;	
	delete [] tt;
}