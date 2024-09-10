/*
 * The main function implements a loader for applications which use UNO.
 *
 * <p>This code runs on the Windows platform only.</p>
 *
 * <p>The main function detects a UNO installation on the system and adds the
 * program directory of the UNO installation to the PATH environment variable.
 * After that, the application process is loaded and started, whereby the
 * new process inherits the environment of the calling process, including
 * the modified PATH environment variable. The application's executable name
 * must be the same as the name of this executable, prefixed by '_'.</p>
 *
 * <p>A UNO installation can be specified by the user by setting the UNO_PATH
 * environment variable to the program directory of the UNO installation.
 * If no installation is specified by the user, the default installation on
 * the system will be taken. The default installation is read from the
 * default value of the key "Software\LibreOffice\UNO\InstallPath" from the
 * root key HKEY_CURRENT_USER in the Windows Registry. If this key is missing,
 * the key is read from the root key HKEY_LOCAL_MACHINE.</p>
 */
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPWSTR lpCmdLine, int nCmdShow )
{
    (void) hInstance; /* unused */
    (void) hPrevInstance; /* unused */
    (void) nCmdShow; /* unused */

    /* get the path of the UNO installation */
    wchar_t* path = getPath();

    if ( path != NULL )
    {
        wchar_t cmd[
            MY_LENGTH(L"\"") + MAX_PATH +
            MY_LENGTH(L"\\unoinfo.exe\" c++")];
            /* hopefully does not overflow */
        cmd[0] = L'"';
        wcscpy(cmd + 1, path);
        if (wcschr(cmd + 1, L'"') != NULL) {
            free(path);
            writeError("Error: bad characters in UNO installation path!\n");
            closeErrorFile();
            return 1;
        }
        size_t pathsize = wcslen(cmd);
        wcscpy(
            cmd + pathsize,
            &L"\\unoinfo.exe\" c++"[
                pathsize == 1 || cmd[pathsize - 1] != L'\\' ? 0 : 1]);
        SECURITY_ATTRIBUTES sec;
        sec.nLength = sizeof (SECURITY_ATTRIBUTES);
        sec.lpSecurityDescriptor = NULL;
        sec.bInheritHandle = TRUE;
        HANDLE stdoutRead;
        HANDLE stdoutWrite;
        HANDLE temp;
        if (CreatePipe(&temp, &stdoutWrite, &sec, 0) == 0 ||
            DuplicateHandle(
                GetCurrentProcess(), temp, GetCurrentProcess(), &stdoutRead, 0,
                FALSE, DUPLICATE_CLOSE_SOURCE | DUPLICATE_SAME_ACCESS) == 0)
        {
            free(path);
            writeError("Error: CreatePipe/DuplicateHandle failed!\n");
            closeErrorFile();
            return 1;
        }
        STARTUPINFOW startinfo;
        PROCESS_INFORMATION procinfo;
        memset(&startinfo, 0, sizeof(startinfo));
        startinfo.cb = sizeof(startinfo);
        startinfo.lpDesktop = L"";
        startinfo.dwFlags = STARTF_USESTDHANDLES;
        startinfo.hStdOutput = stdoutWrite;
        BOOL ret = CreateProcessW(
            NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &startinfo, &procinfo);
        if (ret != FALSE) {
            // Release result of GetPath()
            free(path);

            char * buf = NULL;
            char * tmp;
            DWORD n = 1000;
            DWORD k = 0;
            DWORD exitcode;
            CloseHandle(stdoutWrite);
            CloseHandle(procinfo.hThread);
            for (;;) {
                DWORD m;
                tmp = realloc(buf, n);
                if (tmp == NULL) {
                    free(buf);
                    writeError(
                        "Error: out of memory reading unoinfo output!\n");
                    closeErrorFile();
                    return 1;
                }
                buf = tmp;
                if (!ReadFile(stdoutRead, buf + k, n - k, &m, NULL))
                {
                    DWORD err = GetLastError();
                    if (err == ERROR_HANDLE_EOF || err == ERROR_BROKEN_PIPE) {
                        break;
                    }
                    writeError("Error: cannot read unoinfo output!\n");
                    closeErrorFile();
                    return 1;
                }
                if (m == 0) {
                    break;
                }
                k += m;
                if (k >= n) {
                    if (n >= MAXDWORD / 2) {
                        writeError(
                            "Error: out of memory reading unoinfo output!\n");
                        closeErrorFile();
                        return 1;
                    }
                    n *= 2;
                }
            }
            if ((k & 1) == 1) {
                writeError("Error: bad unoinfo output!\n");
                closeErrorFile();
                return 1;
            }
            CloseHandle(stdoutRead);
            if (!GetExitCodeProcess(procinfo.hProcess, &exitcode) ||
                exitcode != 0)
            {
                writeError("Error: executing unoinfo failed!\n");
                closeErrorFile();
                return 1;
            }
            path = (wchar_t*)realloc(buf, k + sizeof(wchar_t));
            if (path == NULL)
            {
                free(buf);
                writeError(
                    "Error: out of memory zero-terminating unoinfo output!\n");
                closeErrorFile();
                return 1;
            }
            path[k / 2] = L'\0';
        } else {
            if (GetLastError() != ERROR_FILE_NOT_FOUND) {
                free(path);
                writeError("Error: calling unoinfo failed!\n");
                closeErrorFile();
                return 1;
            }
            CloseHandle(stdoutRead);
            CloseHandle(stdoutWrite);
        }

        /* get the value of the PATH environment variable */
        const wchar_t* ENVVARNAME = L"PATH";
        const wchar_t* PATHSEPARATOR = L";";
        wchar_t* value = _wgetenv( ENVVARNAME );

        /*
         * add the UNO installation path to the PATH environment variable;
         * note that this only affects the environment variable of the current
         * process, the command processor's environment is not changed
         */
        size_t size = wcslen( ENVVARNAME ) + wcslen( L"=" ) + wcslen( path ) + 1;
        if ( value != NULL )
            size += wcslen( PATHSEPARATOR ) + wcslen( value );
        wchar_t* envstr = (wchar_t*) malloc( size*sizeof(wchar_t) );
        wcscpy( envstr, ENVVARNAME );
        wcscat( envstr, L"=" );
        wcscat( envstr, path );
        if ( value != NULL )
        {
            wcscat( envstr, PATHSEPARATOR );
            wcscat( envstr, value );
        }
        _wputenv( envstr );
        free( envstr );
        free( path );
    }
    else
    {
        writeError( "Warning: no UNO installation found!\n" );
    }

    /* create the command line for the application process */
    wchar_t* cmdline = createCommandLine( lpCmdLine );
    if ( cmdline == NULL )
    {
        writeError( "Error: cannot create command line!\n" );
        closeErrorFile();
        return 1;
    }

    /* create the application process */
    STARTUPINFOW startup_info;
    PROCESS_INFORMATION process_info;
    memset( &startup_info, 0, sizeof(startup_info) );
    startup_info.cb = sizeof(startup_info);
    BOOL bCreate = CreateProcessW( NULL, cmdline, NULL,  NULL, FALSE, 0, NULL, NULL,
        &startup_info, &process_info );
    free( cmdline );
    if ( !bCreate )
    {
        writeError( "Error: cannot create process!\n" );
        closeErrorFile();
        return 1;
    }

    /* close the error file */
    closeErrorFile();

    return 0;
}