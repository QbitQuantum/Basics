DWORD WINAPI BlackWindow(LPVOID lpParam)
{
 	// TODO: Place code here.
	HDESK desktop;
	desktop = OpenInputDesktop(0, FALSE,
								DESKTOP_CREATEMENU | DESKTOP_CREATEWINDOW |
								DESKTOP_ENUMERATE | DESKTOP_HOOKCONTROL |
								DESKTOP_WRITEOBJECTS | DESKTOP_READOBJECTS |
								DESKTOP_SWITCHDESKTOP | GENERIC_WRITE
								);

	if (desktop == NULL)
		vnclog.Print(LL_INTERR, VNCLOG("OpenInputdesktop Error \n"));
	else 
		vnclog.Print(LL_INTERR, VNCLOG("OpenInputdesktop OK\n"));

	HDESK old_desktop = GetThreadDesktop(GetCurrentThreadId());
	DWORD dummy;

	char new_name[256];
	if (desktop)
	{
		if (!GetUserObjectInformation(desktop, UOI_NAME, &new_name, 256, &dummy))
		{
			vnclog.Print(LL_INTERR, VNCLOG("!GetUserObjectInformation \n"));
		}

		vnclog.Print(LL_INTERR, VNCLOG("SelectHDESK to %s (%x) from %x\n"), new_name, desktop, old_desktop);

		if (!SetThreadDesktop(desktop))
		{
			vnclog.Print(LL_INTERR, VNCLOG("SelectHDESK:!SetThreadDesktop \n"));
		}
	}

	create_window();
	MSG msg;
	while (GetMessage(&msg,0,0,0) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	vnclog.Print(LL_INTERR, VNCLOG("end BlackWindow \n"));
	SetThreadDesktop(old_desktop);
	if (desktop) CloseDesktop(desktop);

	return 0;
}