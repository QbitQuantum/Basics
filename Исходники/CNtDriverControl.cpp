bool CNtDriverControl::IsWindowsNt()
{
	OSVERSIONINFOEX  OSVer;

	OSVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	OSVer.dwOSVersionInfoSize = sizeof(OSVer);

	if (!GetVersionExA((OSVERSIONINFOA *)&OSVer))
		return false;

	switch(OSVer.dwPlatformId << 16 | OSVer.dwMajorVersion << 8 | OSVer.dwMinorVersion)
	{

	  case VER_PLATFORM_WIN32_NT     <<16|0x0500| 1:
		  if(!GetSystemMetrics(87))
			return TRUE;
		  
	  default:
		  MessageBox (0
			  , _T("DeepMonitor designed only for Windows XP !")
			  , _T("Information")
			  , MB_OK);
		  return false;
	
	}
	
	return false;
	
}