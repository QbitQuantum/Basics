void
CMSWindowsRelauncher::mainLoop(void*)
{
	SendSas sendSasFunc = NULL;
	HINSTANCE sasLib = LoadLibrary("sas.dll");
	if (sasLib) {
		LOG((CLOG_DEBUG "found sas.dll"));
		sendSasFunc = (SendSas)GetProcAddress(sasLib, "SendSAS");
	}

	DWORD sessionId = -1;
	bool launched = false;

	SECURITY_ATTRIBUTES saAttr; 
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL; 

	if (!CreatePipe(&m_stdOutRead, &m_stdOutWrite, &saAttr, 0)) {
		throw XArch(new XArchEvalWindows());
	}

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	while (m_running) {

		HANDLE sendSasEvent = 0;
		if (sasLib && sendSasFunc) {
			// can't we just create one event? seems weird creating a new
			// event every second...
			sendSasEvent = CreateEvent(NULL, FALSE, FALSE, "Global\\SendSAS");
		}

		DWORD newSessionId = getSessionId();

		// only enter here when id changes, and the session isn't -1, which
		// may mean that there is no active session.
		if (((newSessionId != sessionId) && (newSessionId != -1)) || m_commandChanged) {
			
			m_commandChanged = false;

			if (launched) {
				LOG((CLOG_DEBUG "closing existing process to make way for new one"));
				shutdownProcess(pi, 10);
				launched = false;
			}

			// ok, this is now the active session (forget the old one if any)
			sessionId = newSessionId;

			SECURITY_ATTRIBUTES sa;
			ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));

			// get the token for the user in active session, which is the
			// one receiving input from mouse and keyboard.
			HANDLE userToken = getCurrentUserToken(sessionId, &sa);

			if (userToken != 0) {
				LOG((CLOG_DEBUG "got user token to launch new process"));

				std::string cmd = command();
				if (cmd == "") {
					LOG((CLOG_WARN "nothing to launch, no command specified."));
					continue;
				}

				// in case reusing process info struct
				ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

				STARTUPINFO si;
				ZeroMemory(&si, sizeof(STARTUPINFO));
				si.cb = sizeof(STARTUPINFO);
				si.lpDesktop = "winsta0\\default";
				si.hStdError = m_stdOutWrite;
				si.hStdOutput = m_stdOutWrite;
				si.dwFlags |= STARTF_USESTDHANDLES;

				LPVOID environment;
				BOOL blockRet = CreateEnvironmentBlock(&environment, userToken, FALSE);
				if (!blockRet) {
					LOG((CLOG_ERR "could not create environment block (error: %i)", 
						GetLastError()));
					continue;
				}
				else {

					DWORD creationFlags = 
						NORMAL_PRIORITY_CLASS |
						CREATE_NO_WINDOW |
						CREATE_UNICODE_ENVIRONMENT;

					// re-launch in current active user session
					BOOL createRet = CreateProcessAsUser(
						userToken, NULL, LPSTR(cmd.c_str()),
						&sa, NULL, TRUE, creationFlags,
						environment, NULL, &si, &pi);

					DestroyEnvironmentBlock(environment);
					CloseHandle(userToken);

					if (!createRet) {
						LOG((CLOG_ERR "could not launch (error: %i)", GetLastError()));
						continue;
					}
					else {
						LOG((CLOG_DEBUG "launched in session %i (cmd: %s)", 
							sessionId, cmd.c_str()));
						launched = true;
					}
				}
			}
		}

		if (sendSasEvent) {
			// use SendSAS event to wait for next session.
			if (WaitForSingleObject(sendSasEvent, 1000) == WAIT_OBJECT_0 && sendSasFunc) {
				LOG((CLOG_DEBUG "calling SendSAS"));
				sendSasFunc(FALSE);
			}
			CloseHandle(sendSasEvent);
		}
		else {
			// check for session change every second.
			ARCH->sleep(1);
		}
	}

	if (launched) {
		LOG((CLOG_DEBUG "terminated running process on exit"));
		shutdownProcess(pi, 10);
	}
}