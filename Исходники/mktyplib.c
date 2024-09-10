// created this from the WIN32 docs, using info on WinExec and CreateProcess
// WARNING: the example given in the WIN32 docs on CreateProcess is bogus.
VOID NEAR DoPreProcess
(
)
{
    char szBuffer[512];
    BOOL fSuccess;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa;
    DWORD  dw;
    DWORD  dwExitCode;
    HANDLE hProcess;
    HANDLE hOutput;

    memset (&si, 0, sizeof(si));
    memset (&pi, 0, sizeof(pi));
    memset (&sa, 0, sizeof(sa));

    szTempFile = strdup(tempnam(".", "~mki"));	// for pre-processed output

    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;

    hOutput = CreateFile(szTempFile, GENERIC_WRITE, 0, &sa,
			 CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

    if (hOutput == INVALID_HANDLE_VALUE)
	ParseError(ERR_CPP);

    sprintf(szBuffer, "%s %s%s %s",
		   szCppExe, szCppOpts, szCppDefs, szInputFile);

    // init si structure
    si.cb = sizeof(si);
    si.lpTitle = "MkTypLib: C pre-processor";
    //si.dwX = 100;		// just guessing...
    //si.dwY = 100;
    //si.dwXSize = 1000;
    //si.dwYSize = 1000;
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdOutput = hOutput;
    //si.hStdError = hOutputError;	// CONSIDER: show this to the user?
    //si.wShowWindow = SW_SHOWMINIMIZED;
    si.wShowWindow = SW_HIDE;

    // Setting the Inherit Handles flag to TRUE so that it works when
    // run under nmake with our output redirected. 
    fSuccess = CreateProcess(NULL, szBuffer, NULL, NULL, TRUE,
			     // this gives us a window'ed CL
			     //DETACHED_PROCESS,
			     0,

			     NULL, NULL,
			     &si, &pi);

    if (!fSuccess) {
        CloseHandle(hOutput);
	ParseError(ERR_CPP);
    }

    // if we were successful, now wait for it to be done
    hProcess = pi.hProcess;

    // wait for the process to complete (120 second timeoout)
    dw = WaitForSingleObject(pi.hProcess, 120000L);

#ifndef STATUS_SUCCESS
	#define STATUS_SUCCESS 0
#endif

    if (dw == STATUS_SUCCESS)
	fSuccess = GetExitCodeProcess(pi.hProcess, &dwExitCode);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    CloseHandle(hOutput);

    // report any error
    if (dw != STATUS_SUCCESS || !fSuccess || dwExitCode != 0) 
	ParseError(ERR_CPP);
}