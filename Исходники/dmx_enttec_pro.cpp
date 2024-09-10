int Open_ProIn()
{
 	char com_str[10];
	sprintf(com_str,"%s:",DeviceNameIN); 
	LPSTR lpszPortName = _T(com_str);
	com_handle_IN = CreateFile(
		lpszPortName, 
		GENERIC_READ | GENERIC_WRITE, 
		0,								// DWORD dwShareMode, 
		NULL,							// LPSECURITY_ATTRIBUTES lpSecurityAttributes, 
		OPEN_EXISTING,					// DWORD dwCreationDispostion, 
		0, //FILE_FLAG_OVERLAPPED,		// DWORD dwFlagsAndAttributes, 
		NULL							// HANDLE hTemplateFile
	);
	
	int iRetIn = (int)(com_handle_IN );
	
	if (iRetIn<0)
	{
    com_handle_IN = NULL;
	sprintf(string_display_dmx_params,"Impossible to open interface, is it PLUGGED ?");
    return(0);
	}
	 else {sprintf(string_display_dmx_params,"Enttec Pro IN  %s is now Open",DeviceNameIN);} 

	// SetCommState & Timeout
    Enttec_Pro_SetCommParamsIN();

	// flush rx & tx buffers
	resIn = FlushFileBuffers(com_handle_IN);
	if (!resIn)
	{ 
    sprintf(string_display_dmx_params,"\ENTTEC PRO IN %s: Flush file buffers failed...",DeviceNameIN);
	CloseHandle(com_handle_IN); com_handle_IN = NULL;
	return(0);
	}