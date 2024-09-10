/// <summary>
///	Creates a console object and starts the child process </summary>
///
/// <param name="ac">
/// Uninitialized console object </param>
/// <param name="tzClientPath">
/// Path to client, in an inject environment this should not be relative </param>
///
/// <returns>
/// If child could be created </returns>
BOOL ImAllocConsole(OUT IM_CONSOLE* ac, IN const TCHAR* tzClientPath) {
       
    SecureZeroMemory(ac->tzClientPipe, MAX_NAME);

    // generate a random name (tmpnam has a forward slash and is not necessarily alphanumeric)
    for (register size_t i = 0; i < rand() % MAX_NAME; ++i) {
        ac->tzClientPipe[i] = rand() % 26 + 'A'; // make random letter
        ac->tzClientPipe[i] ^= rand() % 1 << 5;  // randomly toggle 0x20 (upper/lowercase)
    }
        
    { // create job object and set information
        JOBOBJECT_EXTENDED_LIMIT_INFORMATION joELI;

        ac->hJob = CreateJobObject(NULL, ac->tzClientPipe);
        if (ac->hJob == NULL)
            return FALSE;

	    joELI.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
	    if(!SetInformationJobObject(ac->hJob, JobObjectExtendedLimitInformation, &joELI, sizeof(JOBOBJECT_EXTENDED_LIMIT_INFORMATION))) {
            CloseHandle(ac->hJob), ac->hJob = NULL;
            return FALSE;
        }
    }

    { // create child process
        SECURITY_ATTRIBUTES sa = {0};

        sa.nLength = sizeof(sa);
        sa.bInheritHandle = TRUE;
        //  sa.lpSecurityDescriptor = NULL;

        if (!CreatePipe(&ac->hRead, &ac->hWrite, &sa, BUFSIZ)) {
            CloseHandle(ac->hJob), ac->hJob = NULL;
            return FALSE;
        }

        STARTUPINFO siCon = {0};
        PROCESS_INFORMATION piCon = {0};

        siCon.cb = sizeof(siCon);
        siCon.hStdInput = ac->hRead;
        siCon.dwFlags |= STARTF_USESTDHANDLES;

        if (!CreateProcess(tzClientPath, NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE | CREATE_BREAKAWAY_FROM_JOB | CREATE_UNICODE_ENVIRONMENT, NULL, NULL, &siCon, &piCon)) {
            CloseHandle(ac->hJob), ac->hJob = NULL;
            return FALSE;
        }

        DuplicateHandle(GetCurrentProcess(), piCon.hProcess, GetCurrentProcess(), &ac->hChildProcess, 0, FALSE, DUPLICATE_SAME_ACCESS);
        CloseHandle(piCon.hThread);
        CloseHandle(piCon.hProcess);
    }

    return AssignProcessToJobObject(ac->hJob, ac->hChildProcess);
}