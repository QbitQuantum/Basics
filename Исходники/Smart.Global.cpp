BOOL Smart::Global::CCrashDump::IsDataSectionNeeded( const WCHAR* pModuleName ) 
{
    // Check parameters 
    if( pModuleName == NULL ) 
    {
        return FALSE; 
    }

    WCHAR szModule[512];
    GetModuleFileName(NULL, szModule, 512);
    if( _wcsicmp(szModule, pModuleName) == 0)
    {
        return TRUE;
    }

    // Extract the module name 
    WCHAR szFileName[_MAX_FNAME] = L""; 
    _wsplitpath_s( pModuleName, NULL, 0, NULL, 0, szFileName, _MAX_FNAME, NULL, 0 ); 

    // Compare the name with the list of known names and decide 
    if( _wcsicmp( szFileName, L"ntdll" ) == 0 ) 
    {
        return TRUE; 
    }

    // Complete 
    return FALSE; 
}