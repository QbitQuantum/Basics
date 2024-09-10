tCHAR F_API INPKBGetAscii(u8 kCode)
{ 
	
	tCHAR retvalue = L'';
	char asciichar[256];

	memset(asciichar,0, sizeof(char)*256);

	HKL layout = GetKeyboardLayout(0);
	u8 State[256];
	u32  scancode;
	memset(State, 0, sizeof (u8) * 256);
	u32 vk = MapVirtualKeyEx(kCode,1,layout);
	bool returnvaluegetkeyb = GetKeyboardState(State);  //This function returns crap if we are in exclusive mode

	//CODE TO CHECK OS VERSION,
	//ToUnicodeEx doesn't work in win98,me
   

	OSVERSIONINFO osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx((OSVERSIONINFO*)&osvi); //Should move this function to initialization

   //VER_PLATFORM_WIN32_NT //WinNT4 to Win2003
   //VER_PLATFORM_WIN32_WINDOWS //Windows 95, Windows 98, or Windows Me.
   if ( osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) //Crappy Versions of Windows Without Unicode
   {
	   int returnvalascii = ToAsciiEx(vk, kCode, State, (unsigned short *)asciichar, 0, layout);
		if(returnvalascii > 0)
		{
			int retrunvaluembtowcs = mbstowcs(&retvalue, asciichar, 1);
			if(retrunvaluembtowcs == -1) //some error
				retvalue = L'';
		}
		else
			retvalue = L'';
   }
   else //Good versions of widnows with Unicode
   {
	   s32 retvalunicode = ToUnicodeEx(vk, kCode, State, &retvalue, 1, 0, layout);
	   if(retvalunicode <= 0) // -1 or 0 mean error or no character was translated
		   retvalue = L'';
   }


/*
   HKL layout = GetKeyboardLayout(0);
   unsigned char State[256];
   if (GetKeyboardState(State)==FALSE)
      return 0;
   unsigned int vk = MapVirtualKeyEx(scancode,1,layout);
   return ToAsciiEx(vk,scancode,State,(unsigned short *)result,0,layout);
*/
/*
BOOL bIsWindowsVersionOK(DWORD dwMajor, DWORD dwMinor, DWORD dwSPMajor )
{
OSVERSIONINFO osvi;
 
// Initialize the OSVERSIONINFO structure.
//
ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
GetVersionEx((OSVERSIONINFO*)&osvi);
 
// First the major version
if ( osvi.dwMajorVersion > dwMajor )
   return TRUE;
else if ( osvi.dwMajorVersion == dwMajor )
   {
   // Then the minor
   if (osvi.dwMinorVersion > dwMinor )
      return TRUE;
   else if (osvi.dwMinorVersion == dwMinor )
      {
      // OK, better check the Service Pack
      if ( dwSPMajor && 
        osvi.dwPlatformId == VER_PLATFORM_WIN32_NT )
         {
         HKEY   hKey;
         DWORD dwCSDVersion;
          DWORD dwSize;
         BOOL   fMeetsSPRequirement = FALSE;
 
         if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
            System\\CurrentControlSet\\Control\\Windows",
0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
            {
            dwSize = sizeof(dwCSDVersion);
            if (RegQueryValueEx(hKey, "CSDVersion",
               NULL, NULL,
(unsigned char*)&dwCSDVersion, 
&dwSize) == ERROR_SUCCESS)
               {
               fMeetsSPRequirement = 
(LOWORD(dwCSDVersion) >= dwSPMajor);
               }
           RegCloseKey(hKey);
           }
         return fMeetsSPRequirement;
         }
      return TRUE;
      }
   }
return FALSE;
}

*/

   return retvalue;
}