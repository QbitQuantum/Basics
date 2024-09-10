void CrashHandlerImpl::fillBasicCrashInfo() {
	m_pCrashInfo->architecture = ARX_ARCH;
	m_pCrashInfo->processId = getProcessId();

	strcpy(m_pCrashInfo->crashReportFolder, "crashes");

	strncpy(m_pCrashInfo->executablePath, getExecutablePath().c_str(), sizeof(m_pCrashInfo->executablePath));
	m_pCrashInfo->executablePath[sizeof(m_pCrashInfo->executablePath)-1] = 0; // Make sure our string is null terminated

	strncpy(m_pCrashInfo->executableVersion, version.c_str(), sizeof(m_pCrashInfo->executableVersion));
	m_pCrashInfo->executableVersion[sizeof(m_pCrashInfo->executableVersion)-1] = 0; // Make sure our string is null terminated
	
}