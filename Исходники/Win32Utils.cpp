BOOL CALLBACK MyEnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char class_name[256];
	GetClassName(hwnd, class_name, 256);
	
	static const char * upp_class = "UPP-CLASS";
	for(int i = 0; i < (int) strlen(upp_class); i++)
		if(upp_class[i] != class_name[i])
			return TRUE;
		
	DWORD process_id;
	int thread_id = GetWindowThreadProcessId(hwnd, &process_id);
	if(g_process_id == process_id)
	{
		g_process_hwnd = hwnd;
		return FALSE;
	}
	else
		return TRUE;
}