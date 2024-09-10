///////////////////////////////////////////////////////////////
//
// DelTree
//
//
//
///////////////////////////////////////////////////////////////
bool SharedUtil::DelTree ( const SString& strPath, const SString& strInsideHere )
{
    // Safety: Make sure strPath is inside strInsideHere
    if ( strPath.ToLower ().substr ( 0, strInsideHere.length () ) != strInsideHere.ToLower () )
    {
        assert ( 0 );
        return false;
    }

    DWORD dwBufferSize = strPath.length () + 3;
    char *szBuffer = static_cast < char* > ( alloca ( dwBufferSize ) );
    memset ( szBuffer, 0, dwBufferSize );
    strncpy ( szBuffer, strPath, strPath.length () );
    SHFILEOPSTRUCT sfos;

    sfos.hwnd = NULL;
    sfos.wFunc = FO_DELETE;
    sfos.pFrom = szBuffer;
    sfos.pTo = NULL;
    sfos.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT | FOF_ALLOWUNDO;

    int status = SHFileOperation(&sfos);
    return status == 0;
}