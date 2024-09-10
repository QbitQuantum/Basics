int CamuleDaemonApp::OnExit()
{
#ifdef AMULED28
	/*
	 * Stop all socket threads before entering
	 * shutdown sequence.
	 */
	delete listensocket;
	listensocket = 0;
	if (clientudp) {
		delete clientudp;
		clientudp = NULL;
	}
#endif

	ShutDown();

#ifndef __WXMSW__
	int ret = sigaction(SIGCHLD, &m_oldSignalChildAction, NULL);
	if (ret == -1) {
		AddDebugLogLineC(logStandard, CFormat(wxT("CamuleDaemonApp::OnRun(): second sigaction() failed: %m.")));
	} else {
		AddDebugLogLineN(logGeneral, wxT("CamuleDaemonApp::OnRun(): Uninstallation of SIGCHLD callback with sigaction() succeeded."));
	}
#endif // __WXMSW__
	
	// lfroen: delete socket threads
	if (ECServerHandler) {
		ECServerHandler = 0;
	}

	delete core_timer;
	
	return CamuleApp::OnExit();
}