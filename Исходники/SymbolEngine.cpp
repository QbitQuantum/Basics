bool
CSymbolEngine::LoadModuleSymbols( 
	HANDLE hFile, 
	const TString& ImageName, 
	DWORD64 ModBase, 
	DWORD ModSize 
	)
{
	// Check preconditions 

	if( m_hProcess == NULL )
	{
		_ASSERTE( !_T("Symbol engine is not yet initialized.") );
		m_LastError = ERROR_INVALID_FUNCTION;
		return false;
	}


	// In Unicode build, ImageName parameter should be translated to ANSI

#ifdef _UNICODE
	char* pImageName = 0;
	if( !ImageName.empty() )
	{
		size_t BufSize = 2 * ImageName.length();
		pImageName = (char*)_alloca( BufSize + 2 );
		size_t res = wcstombs( pImageName, ImageName.c_str(), BufSize );
		pImageName[BufSize] = 0;
		if( res == -1 )
		{
			_ASSERTE( !_T("Module name has bad format.") );
			m_LastError = ERROR_INVALID_PARAMETER;
			return false;
		}
	}
#else
	const char* pImageName = ImageName.empty() ? 0 : ImageName.c_str();
#endif //_UNICODE


	// Load symbols for the module
#pragma TODO("replace SymLoadModule64 with SymLoadModuleEx ")
	DWORD64 rv = SymLoadModule64( m_hProcess, hFile, pImageName, NULL, ModBase, ModSize );

	if( rv == 0 )
	{
		m_LastError = GetLastError();
		_ASSERTE( !_T("SymLoadModule64() failed.") );
		return false;
	}


	// Complete 

	return true;
}