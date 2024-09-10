bool CATDbgHelper::AddressToLine( CATMemoryAddress* result )
{
	LOG_FUNC_ENTRY("CATDbgHelper::AddressToLine");
	
	// Set state out of range
	result->SetAddressToLineState( CATMemoryAddress::OUT_OF_RANGE );

	// check that dbghelper has been initialized successfully.
	if ( ! CDBGHELPER_OPEN )
		return false;

	// Check has binary been moved, if so unload and load to new base address.
	if ( result->GetModuleStartAddress() + AT_VIRTUAL_OFFSET_DBGHELPER != m_BaseAddress )
	{
		// Unload.
		if ( SymUnloadModule64( GetCurrentProcess(), m_BaseAddress ) )
		{
			// Set new base address.
			m_BaseAddress = result->GetModuleStartAddress() + AT_VIRTUAL_OFFSET_DBGHELPER;
			// (Re)load.
			DWORD64 loading = SymLoadModule64( GetCurrentProcess(), NULL, m_pBinaryFile, NULL, m_BaseAddress, NULL );
			if ( loading != m_BaseAddress  && loading != 0)	
			{
				LOG_STRING("Dbghelp:Module load failed " << (int) GetLastError());
				return false;
			}
		}
		else
			LOG_STRING("Dbghelp:Module unload failed " << (int) GetLastError() );
	}
	// Address to find (offset+given address).
	unsigned long iAddressToFind = result->GetAddress() + AT_VIRTUAL_OFFSET_DBGHELPER;
	// Displacements of line/symbol information.
	DWORD64 displacementSymbol;
	DWORD displacementLine;
	// Structure to get symbol information.
	CSymbolInfo symbol;
	// Structure to get line information.
	CLineInfo line;
	// Find Symbol for given address 
	if( ! SymFromAddr( GetCurrentProcess(), iAddressToFind , &displacementSymbol, &symbol.si ) )
	{
		LOG_STRING("Failed to find symbol information for given line.");
		return AddressToFunction( result );
	}
	// Find line information
	if( ! SymGetLineFromAddr64( GetCurrentProcess(), iAddressToFind, &displacementLine, &line ) )
	{
		// If it fails get symbol line information
		LOG_STRING("Dbghelp:Failed to find line information for address, trying for symbol of address.");
		if( ! SymGetLineFromAddr64( GetCurrentProcess(), symbol.si.Address, &displacementLine, &line ) )
		{
			LOG_STRING("Dbghelp:Failed to find line information for symbol address.");
			return AddressToFunction( result );
		}
	}
	// Set the results.
	result->SetFileName( string( line.FileName ) );
	result->SetFunctionName( string( symbol.si.Name ) );
	result->SetExactLineNumber( (int) line.LineNumber );
	result->SetAddressToLineState( CATMemoryAddress::EXACT );
	// Return.
	return true;
}