bool PlatformSpecificProgramIdentifierHelper::_isExePathRelatedToProcess(DWORD dwPID, QString exePath)
{
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    FLAG_FOR_REVIEW_WITH_HINT("https://bitbucket.org/shadevampire/easyapps/issue/238/bug-termination-fails-for-some-64-bit-apps");

    // Take a snapshot of all modules in the specified process.
#ifdef __MINGW32__
    hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE/* | TH32CS_SNAPMODULE32*/, dwPID );
#else // MSVC
    hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwPID );
#endif
    if( hModuleSnap == INVALID_HANDLE_VALUE )
    {
        DLog("Failed, retry if error-bad-length...");
        bool isSuccess = false;
        int lastErrorCode = GetLastError();
        while( (lastErrorCode = GetLastError()) == ERROR_BAD_LENGTH) {
            // retry while failes
            // it's hilarious, but this is what the docs says...
            //  http://msdn.microsoft.com/en-us/library/windows/desktop/ms682489(v=vs.85).aspx
            DLog("Retry while it's error-bad-length, as the docs says...") << lastErrorCode;

#ifdef __MINGW32__
            hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE/* | TH32CS_SNAPMODULE32*/, dwPID );
#else // MSVC
            hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwPID );
#endif
            if( hModuleSnap == INVALID_HANDLE_VALUE )
            {
                // retry if error-bad-length
            }
            else {
                isSuccess = true;
            }
        }

        if(!isSuccess) {
            DLog("FAILED: CreateToolhelp32Snapshot (of modules). Last error code: ") << lastErrorCode;
            return( false );
        }
    }

    // Set the size of the structure before using it.
    me32.dwSize = sizeof( MODULEENTRY32 );

    // Retrieve information about the first module,
    // and exit if unsuccessful
    if( !Module32First( hModuleSnap, &me32 ) )
    {
        DLog("FAILED: Module32First");  // show cause of failure
        CloseHandle( hModuleSnap );           // clean the snapshot object
        return( false );
    }

    bool isFound = false;
    // Now walk the module list of the process,
    // and display information about each module
    do
    {
//        _tprintf( TEXT("\n\n     MODULE NAME:     %s"),   me32.szModule );
//        _tprintf( TEXT("\n     Executable     = %s"),     me32.szExePath );
//        _tprintf( TEXT("\n     Process ID     = 0x%08X"),         me32.th32ProcessID );
//        _tprintf( TEXT("\n     Ref count (g)  = 0x%04X"),     me32.GlblcntUsage );
//        _tprintf( TEXT("\n     Ref count (p)  = 0x%04X"),     me32.ProccntUsage );
//        _tprintf( TEXT("\n     Base address   = 0x%08X"), (DWORD) me32.modBaseAddr );
//        _tprintf( TEXT("\n     Base size      = %d"),             me32.modBaseSize );

        if(me32.th32ProcessID == dwPID) {
            QString processRelatedExePath = QString::fromWCharArray(me32.szExePath);
            processRelatedExePath = QDir().absoluteFilePath(processRelatedExePath);
            processRelatedExePath = PathHelper::cleanThisPath(processRelatedExePath);
            QString absoluteReferenceExePath = QDir().absoluteFilePath(exePath);
            absoluteReferenceExePath = PathHelper::cleanThisPath(absoluteReferenceExePath);
//            DLogS << "proc related exe-path: " << processRelatedExePath << " reference path: " << absoluteReferenceExePath;
            if(processRelatedExePath == absoluteReferenceExePath) {
                isFound = true;
                break;
            }
        }
    } while( Module32Next( hModuleSnap, &me32 ) );

    CloseHandle( hModuleSnap );
    return( isFound );
}