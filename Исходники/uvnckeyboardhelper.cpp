bool SelectDesktop()
{
		HDESK desktop;
		HDESK old_desktop;
		DWORD dummy;
		char new_name[256];
		desktop = OpenInputDesktop(0, FALSE,
				DESKTOP_CREATEMENU | DESKTOP_CREATEWINDOW |
				DESKTOP_ENUMERATE | DESKTOP_HOOKCONTROL |
				DESKTOP_WRITEOBJECTS | DESKTOP_READOBJECTS |
				DESKTOP_SWITCHDESKTOP | GENERIC_WRITE);
		if (desktop == NULL) return FALSE;
		old_desktop = GetThreadDesktop(GetCurrentThreadId());
		if (!GetUserObjectInformation(desktop, UOI_NAME, &new_name, 256, &dummy)) {
			CloseDesktop(desktop);
			return FALSE;
		}
		if(!SetThreadDesktop(desktop)) {
			CloseDesktop(desktop);
			return FALSE;
		}
		CloseDesktop(old_desktop);			
		return TRUE;

}