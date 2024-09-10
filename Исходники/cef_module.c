int cef_rds_module_start(rdsModule* module)
{
	BOOL status;
	rdsModuleCef* cef;
	rdpSettings* settings;
	rdsConnector* connector;
	char lpCommandLine[256];
	const char* endpoint = "CEF";

	cef = (rdsModuleCef*) module;
	connector = (rdsConnector*) module;

	WLog_Print(cef->log, WLOG_DEBUG, "RdsModuleStart: SessionId: %d Endpoint: %s",
			(int) module->SessionId, endpoint);

	settings = connector->settings;

	freerds_named_pipe_clean(module->SessionId, endpoint);

	ZeroMemory(&(cef->si), sizeof(STARTUPINFO));
	cef->si.cb = sizeof(STARTUPINFO);
	ZeroMemory(&(cef->pi), sizeof(PROCESS_INFORMATION));

	sprintf_s(lpCommandLine, sizeof(lpCommandLine), "%s /session-id:%d /width:%d /height:%d",
			"freerds-cef", (int) module->SessionId, settings->DesktopWidth, settings->DesktopHeight);

	WLog_Print(cef->log, WLOG_DEBUG, "Starting process with command line: %s", lpCommandLine);

	status = CreateProcessA(NULL, lpCommandLine,
			NULL, NULL, FALSE, 0, NULL, NULL,
			&(cef->si), &(cef->pi));

	WLog_Print(cef->log, WLOG_DEBUG, "Process created with status: %d", status);

	module->hClientPipe = freerds_named_pipe_connect(module->SessionId, "CEF", 5 * 1000);

	if (!module->hClientPipe)
	{
		WLog_Print(cef->log, WLOG_ERROR, "Failed to connect to service");
		return -1;
	}

	return 0;
}