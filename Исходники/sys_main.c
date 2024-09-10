/*
=================
Sys_Error
=================
*/
void Sys_Error(const char *error, ...)
{
	va_list argptr;
	char    string[1024];
#if defined (USE_WINDOWS_CONSOLE)
	MSG msg;
#endif

	va_start(argptr, error);
	Q_vsnprintf(string, sizeof(string), error, argptr);
	va_end(argptr);

#if defined (USE_WINDOWS_CONSOLE)
	Conbuf_AppendText(string);
	Conbuf_AppendText("\n");

	Sys_Splash(qfalse);
	Sys_SetErrorText(string);
	Sys_ShowConsole(1, qtrue);

	timeEndPeriod(1);

	IN_Shutdown();

	// wait for the user to quit
	while (1)
	{
		if (!GetMessage(&msg, NULL, 0, 0))
		{
			Com_Quit_f();
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sys_DestroyConsole();
#endif

	Sys_ErrorDialog(string);

	Sys_Exit(3);
}