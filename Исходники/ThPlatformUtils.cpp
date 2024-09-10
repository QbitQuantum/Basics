//----------------------------------------------------------------------------------------
bool IsDataSectionNeeded( const WCHAR* pModuleName ) 
{
	
	// Check parameters
	if( pModuleName == 0 ) 
	{		
		return false; 
	}
	
	WCHAR curDir[MAX_PATH] = L"";
	GetCurrentDirectoryW(MAX_PATH-1, curDir);
	wcscat(curDir, L"\\");

	// Extract the module name 
	WCHAR drive[_MAX_DRIVE] = L"";
	WCHAR dir[_MAX_DIR]=L"";
	WCHAR fileName[_MAX_FNAME]=L"";
	_wsplitpath( pModuleName, drive, dir, fileName, 0 );

	WCHAR modulePath[_MAX_DRIVE + _MAX_DIR]=L"";
	wcscat(modulePath, drive);	
	wcscat(modulePath, dir);	

	// Compare the name with the list of known names and decide 	
	if( wcsicmp( curDir, modulePath ) == 0 ) 
	{		
		return true; 
	}
	else if( wcsicmp( fileName, L"ntdll" ) == 0 ) 
	{
		return true; 
	}	

	return false;
}