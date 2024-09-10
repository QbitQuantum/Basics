int
main()
{
    DWORD dwRead, dwWrite;
    char *cmdLine;
    HANDLE hStdInput, hStdOutput, hStdError;
    HANDLE hFileInput, hFileOutput, hFileError;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char buf[8192];
    DWORD result;

    hFileInput = INVALID_HANDLE_VALUE;
    hFileOutput = INVALID_HANDLE_VALUE;
    hFileError = INVALID_HANDLE_VALUE;
    result = 1;

    /*
     * Don't get command line from argc, argv, because the command line
     * tokenizer will have stripped off all the escape sequences needed
     * for quotes and backslashes, and then we'd have to put them all
     * back in again.  Get the raw command line and parse off what we
     * want ourselves.  The command line should be of the form:
     *
     * stub16.exe program arg1 arg2 ...
     */

    cmdLine = strchr(GetCommandLine(), ' ');
    if (cmdLine == NULL) {
	return 1;
    }
    cmdLine++;

    hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    hStdError = GetStdHandle(STD_ERROR_HANDLE);

    if (GetFileType(hStdInput) == FILE_TYPE_PIPE) {
	hFileInput = CreateTempFile();
	if (hFileInput == INVALID_HANDLE_VALUE) {
	    goto cleanup;
	}
	while (ReadFile(hStdInput, buf, sizeof(buf), &dwRead, NULL) != FALSE) {
	    if (dwRead == 0) {
		break;
	    }
	    if (WriteFile(hFileInput, buf, dwRead, &dwWrite, NULL) == FALSE) {
		goto cleanup;
	    }
	}
	SetFilePointer(hFileInput, 0, 0, FILE_BEGIN);
	SetStdHandle(STD_INPUT_HANDLE, hFileInput);
    }
    if (GetFileType(hStdOutput) == FILE_TYPE_PIPE) {
	hFileOutput = CreateTempFile();
	if (hFileOutput == INVALID_HANDLE_VALUE) {
	    goto cleanup;
	}
	SetStdHandle(STD_OUTPUT_HANDLE, hFileOutput);
    }
    if (GetFileType(hStdError) == FILE_TYPE_PIPE) {
	hFileError = CreateTempFile();
	if (hFileError == INVALID_HANDLE_VALUE) {
	    goto cleanup;
	}
	SetStdHandle(STD_ERROR_HANDLE, hFileError);
    }

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    if (CreateProcess(NULL, cmdLine, NULL, NULL, TRUE, 0, NULL, NULL, &si, 
	    &pi) == FALSE) {
	goto cleanup;
    }

    WaitForInputIdle(pi.hProcess, 5000);
    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &result);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (hFileOutput != INVALID_HANDLE_VALUE) {
	SetFilePointer(hFileOutput, 0, 0, FILE_BEGIN);
	while (ReadFile(hFileOutput, buf, sizeof(buf), &dwRead, NULL) != FALSE) {
	    if (dwRead == 0) {
		break;
	    }
	    if (WriteFile(hStdOutput, buf, dwRead, &dwWrite, NULL) == FALSE) {
		break;
	    }
	}
    }
    if (hFileError != INVALID_HANDLE_VALUE) {
	SetFilePointer(hFileError, 0, 0, FILE_BEGIN);
	while (ReadFile(hFileError, buf, sizeof(buf), &dwRead, NULL) != FALSE) {
	    if (dwRead == 0) {
		break;
	    }
	    if (WriteFile(hStdError, buf, dwRead, &dwWrite, NULL) == FALSE) {
		break;
	    }
	}
    }

cleanup:
    if (hFileInput != INVALID_HANDLE_VALUE) {
	CloseHandle(hFileInput);
    }
    if (hFileOutput != INVALID_HANDLE_VALUE) {
	CloseHandle(hFileOutput);
    }
    if (hFileError != INVALID_HANDLE_VALUE) {
	CloseHandle(hFileError);
    }
    CloseHandle(hStdInput);
    CloseHandle(hStdOutput);
    CloseHandle(hStdError);
    ExitProcess(result);
    return 1;
}