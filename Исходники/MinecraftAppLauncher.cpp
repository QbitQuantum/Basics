/* Launches Minecraft and invokes mod injection */
HRESULT MinecraftAppLauncher::LaunchApplicationAndInjectMods(PDWORD processId_ptr, BOOL _doInject)
{
	CComPtr<IApplicationActivationManager> spAppActivationManager;
	HRESULT result = E_INVALIDARG;

	/* Initialize IApplicationActivationManager */
	result = CoCreateInstance(CLSID_ApplicationActivationManager,
		NULL,
		CLSCTX_LOCAL_SERVER,
		IID_IApplicationActivationManager,
		(LPVOID*)&spAppActivationManager);

	if (SUCCEEDED(result))
	{
		/* This call ensures that the app is launched as the foreground window */
		result = CoAllowSetForegroundWindow(spAppActivationManager, NULL);

		/* Launch the app */
		if (SUCCEEDED(result))
		{
			DWORD hInjectModsThreadId;
			HANDLE hInjectModsThread;

			/* Inject mods if activated */
			if (_doInject)
			{
				/* Begin thread to find Minecraft and inject mods */
				hInjectModsThread = CreateThread(0, 0, InjectMods_Threaded, NULL, NULL, &hInjectModsThreadId);

				/* Set thread priority to the highest priority to reduce the amount of context switching */
				SetThreadPriority(hInjectModsThread, THREAD_PRIORITY_TIME_CRITICAL);
			}

			/* Initialize the application with mods */
			result = spAppActivationManager->ActivateApplication(MINECRAFT_APP_NAME, NULL, AO_NONE, processId_ptr);
		}
	}

	return result;
}