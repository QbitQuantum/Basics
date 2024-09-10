void WriteOnNamedSignal(const char *name, uint32_t *addr)
{
	HANDLE m_namedSharedObject;

	SECURITY_DESCRIPTOR sd;
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&sd, TRUE, 0, FALSE);

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;
	sa.lpSecurityDescriptor = &sd;

	m_namedSharedObject = CreateEventA(&sa, FALSE, FALSE, name);
	if(m_namedSharedObject == NULL){
		LPVOID lpMsgBuf;
		FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPSTR) &lpMsgBuf, 0, NULL );
		fputs((const char*)lpMsgBuf, stderr);
		return;
	}
	sig_data = new SignalData(addr, m_namedSharedObject);
	spyRunning = true;
	CreateThread(NULL, 0, WaitForMemorySignal, NULL, 0, NULL);
}