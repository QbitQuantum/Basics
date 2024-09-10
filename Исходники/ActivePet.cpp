int ActivePet::launch(std::wstring exePath, std::wstring originalDocPath){

	wchar_t commandLine[4096] = { '\0' };
	if (originalDocPath != L"") {

		// Build the command line.
	    std::wstring editableDocPath = edit(originalDocPath);
		wcscat(commandLine, L"\"");
		wcscat(commandLine, exePath.c_str());
		wcscat(commandLine, L"\" \"");
		wcscat(commandLine, editableDocPath.c_str());
		wcscat(commandLine, L"\"");
	}
    auto_close<void*, &::DestroyEnvironmentBlock> environment(NULL);
	if (!CreateEnvironmentBlock(&environment, m_session.get(), FALSE)) {
        printf("CreateEnvironmentBlock() failed: %d", GetLastError());
		return -30;
	}
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi = {};
	if (!CreateProcessAsUser(m_session.get(),
							 exePath.c_str(),
							 commandLine,
							 NULL,
							 NULL,
							 FALSE,
							 CREATE_SUSPENDED | CREATE_UNICODE_ENVIRONMENT | CREATE_NEW_CONSOLE,
							 environment.get(),
							 NULL, // lpCurrentDirectory,
							 &si,
							 &pi)) {
        printf("CreateProcessAsUser() failed: %d", GetLastError());
		return -30;
	}
	if (!AssignProcessToJobObject(m_job.get(), pi.hProcess)) {
        printf("AssignProcessToJobObject() failed: %d", GetLastError());
		return -30;
	}
	if (!ResumeThread(pi.hThread)) {
        printf("ResumeThread() failed: %d", GetLastError());
		return -30;
	}
    if (WaitForInputIdle(pi.hProcess, INFINITE) != ERROR_SUCCESS) {
        printf("WaitForInputIdle() failed: %d", GetLastError());
		return -30;
	}
    InjectAndCall(pi.hProcess, "ApplyHooks", 10000);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

    return 0;
}