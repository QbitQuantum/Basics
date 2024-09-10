int spawn_shell(PROCESS_INFORMATION *pi, HANDLE *out_read, HANDLE *in_write)
{
	SECURITY_ATTRIBUTES sattr;
	STARTUPINFOA si;
	HANDLE in_read, out_write;

	memset(&si, 0x00, sizeof(SECURITY_ATTRIBUTES));
	memset(pi, 0x00, sizeof(PROCESS_INFORMATION));
    
	// create communication pipes  
	memset(&sattr, 0x00, sizeof(SECURITY_ATTRIBUTES));
	sattr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	sattr.bInheritHandle = TRUE; 
	sattr.lpSecurityDescriptor = NULL; 

	if (!CreatePipe(out_read, &out_write, &sattr, 0)) {
		return STATUS_PROCESS_NOT_CREATED;
	}
	if (!SetHandleInformation(*out_read, HANDLE_FLAG_INHERIT, 0)) {
		return STATUS_PROCESS_NOT_CREATED;
	}

	if (!CreatePipe(&in_read, in_write, &sattr, 0)) {
		return STATUS_PROCESS_NOT_CREATED;
	}
	if (!SetHandleInformation(*in_write, HANDLE_FLAG_INHERIT, 0)) {
		return STATUS_PROCESS_NOT_CREATED;
	}

	// spawn process
	memset(&si, 0x00, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO); 
	si.hStdError = out_write;
	si.hStdOutput = out_write;
	si.hStdInput = in_read;
	si.dwFlags |= STARTF_USESTDHANDLES;

	if (!CreateProcessA(NULL, "cmd", NULL, NULL, TRUE, 0, NULL, NULL, (LPSTARTUPINFOA) &si, pi)) {
		return STATUS_PROCESS_NOT_CREATED;
	}

	CloseHandle(out_write);
	CloseHandle(in_read);

	return STATUS_OK;
}