char* rdp_rds_module_start(RDS_MODULE_COMMON* module)
{
	BOOL status;
	rdsModuleRdp* rdp;
	char lpCommandLine[256];
	const char* endpoint = "RDP";
	long xres, yres,colordepth;
	char* pipeName = (char*) malloc(256);

	rdp = (rdsModuleRdp*) module;

	rdp->SessionId = rdp->commonModule.sessionId;

	WLog_Print(rdp->log, WLOG_DEBUG, "RdsModuleStart: SessionId: %d Endpoint: %s",
			(int) rdp->commonModule.sessionId, endpoint);

	freerds_named_pipe_get_endpoint_name((int) rdp->commonModule.sessionId, endpoint, pipeName, 256);
	freerds_named_pipe_clean(pipeName);

	ZeroMemory(&(rdp->si), sizeof(STARTUPINFO));
	rdp->si.cb = sizeof(STARTUPINFO);
	ZeroMemory(&(rdp->pi), sizeof(PROCESS_INFORMATION));

	initResolutions(rdp->commonModule.baseConfigPath, &g_Config,
			&rdp->commonModule.envBlock, &xres, &yres, &colordepth);

	sprintf_s(lpCommandLine, sizeof(lpCommandLine), "%s /tmp/rds.rdp /size:%dx%d",
			"freerds-rdp", (int) xres, (int) yres);

	WLog_Print(rdp->log, WLOG_DEBUG, "Starting process with command line: %s", lpCommandLine);

	status = CreateProcessA(NULL, lpCommandLine,
			NULL, NULL, FALSE, 0, rdp->commonModule.envBlock, NULL,
			&(rdp->si), &(rdp->pi));

	WLog_Print(rdp->log, WLOG_DEBUG, "Process created with status: %d", status);

	if (!WaitNamedPipeA(pipeName, 5 * 1000))
	{
		fprintf(stderr, "WaitNamedPipe failure: %s\n", pipeName);
		return NULL;
	}

	return pipeName;
}