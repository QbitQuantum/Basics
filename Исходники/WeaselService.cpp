void WeaselService::Start(DWORD dwArgc = 0, PWSTR * pszArgv = NULL)
{
	try
	{
		// Tell SCM that the service is starting.
		SetServiceStatus(SERVICE_START_PENDING);

		// Perform service-specific initialization.
		if (IsWindowsVistaOrGreater())
		{
			PRAR RegisterApplicationRestart = (PRAR)::GetProcAddress(::GetModuleHandle(_T("kernel32.dll")), "RegisterApplicationRestart");
			RegisterApplicationRestart(NULL, 0);
		}
		boost::thread{ [this] {
			app.Run();
		} };
		// Tell SCM that the service is started.
		SetServiceStatus(SERVICE_RUNNING);

	}
	catch (DWORD dwError)
	{
		// Set the service status to be stopped.
		SetServiceStatus(SERVICE_STOPPED, dwError);
	}
	catch (...)
	{
		// Set the service status to be stopped.
		SetServiceStatus(SERVICE_STOPPED);
	}
}