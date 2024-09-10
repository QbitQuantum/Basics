int main(int argc, const char* argv[])
{
	InitCommonControls();

	if (AttachConsole(ATTACH_PARENT_PROCESS))
	{
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
	}

	uifiber = ConvertThreadToFiber(NULL);
	assert(uifiber);

	appfiber = CreateFiber(0, application_cb, NULL);
	assert(appfiber);

	realargc = argc;
	realargv = argv;

	/* Run the application fiber. This will deschedule when it wants an
	 * event.
	 */

	SwitchToFiber(appfiber);

	/* And now the event loop. */

	int oldtimeout = -1;
	for (;;)
	{
		MSG msg;

		dpy_flushkeys();

		if (timeout != oldtimeout)
		{
			if (timeout == -1)
				KillTimer(window, TIMEOUT_TIMER_ID);
			else
				SetTimer(window, TIMEOUT_TIMER_ID, timeout*1000, NULL);
			oldtimeout = timeout;
		}

		GetMessageW(&msg, NULL, 0, 0);

		if (DispatchMessageW(&msg) == 0)
			TranslateMessage(&msg);
	}

	return 0;
}