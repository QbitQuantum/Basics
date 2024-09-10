/** wait for cron process to finish */
static void
waitforit(PROCESS_INFORMATION* pinfo)
{
	DWORD ret = WaitForSingleObject(pinfo->hProcess, INFINITE);
	verbose(VERB_ALGO, "cronaction done");
	if(ret != WAIT_OBJECT_0) {
		return; /* did not end successfully */
	}
	if(!GetExitCodeProcess(pinfo->hProcess, &ret)) {
		log_err("GetExitCodeProcess failed");
		return;
	}
	verbose(VERB_ALGO, "exit code is %d", (int)ret);
	if(ret != 1) {
		if(!WSASetEvent(service_stop_event))
			log_err("Could not WSASetEvent: %s",
			wsa_strerror(WSAGetLastError()));
	}
}