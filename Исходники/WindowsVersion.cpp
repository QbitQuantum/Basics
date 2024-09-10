CWindowsVersion::CWindowsVersion()
{
	m_osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  
    if(!GetVersionEx(&m_osv))
    {
        ASSERT(0);
        // make sure nothing bad will happen trying to interpret OSVERSIONINFO
        memset((void*)&m_osv, 0, sizeof(m_osv));
    }
    else
    {
        switch(m_osv.dwPlatformId)
        {
        case VER_PLATFORM_WIN32s: //Win32s on Windows 3.1. 
            m_winVer = WV_32S;
            break;

        case VER_PLATFORM_WIN32_WINDOWS: //WIN32 on 95 or 98 or ME
            if(m_osv.dwMinorVersion == 0)
            {
                m_winVer = WV_95;
            }
            else if(m_osv.dwMinorVersion == 10)
            {
                m_winVer = WV_98;
            }
            if(m_osv.dwMinorVersion == 90)
            {
                m_winVer = WV_ME;
            }
            break;

        case VER_PLATFORM_WIN32_NT: //Win32 on Windows NT. 

            if(m_osv.dwMajorVersion == 4) 
            {
                m_winVer = WV_NT4;
            }
            else if(m_osv.dwMajorVersion >= 5)
            {
                m_winVer = WV_2K;
            }
            break;

        default: 
            m_winVer = WV_UNKNOWN;
            break;
        }
    }

    // get the language
    m_UILang = 0;
    switch(m_winVer)
    {
    case WV_2K:
        {
        // Disable this section to emulate Windows NT before Windows 2000, when testing
        // on Windows 2000
        // Use GetUserDefaultUILanguage to find the user's prefered UI language

        // Declare function pointer
        LANGID (WINAPI *pfnGetUserDefaultUILanguage) () = NULL ;

        HMODULE hMKernel32 = LoadLibraryW(L"kernel32.dll") ;
        
        pfnGetUserDefaultUILanguage = 
            (unsigned short (WINAPI *)(void)) 
                GetProcAddress(hMKernel32, "GetUserDefaultUILanguage") ;

        if(NULL != pfnGetUserDefaultUILanguage)
            m_UILang = pfnGetUserDefaultUILanguage() ;
        }
        break;
    case WV_NT4:
        {
            // Running on Windows NT 4.0 or earlier. Get UI language
            // from locale of .default user in registry:
            // HKEY_USERS\.DEFAULT\Control Panel\International\Locale
            CRegKeyEx key;
            if(ERROR_SUCCESS == key.Open(HKEY_USERS, _T(".DEFAULT\\Control Panel\\International"), KEY_READ))
            {
                CString value = key.QueryValueString(_T("Locale"));
                m_UILang = (LANGID)_tcstol(value,NULL,16);
            };
            
        }
        break;
    case WV_95:
    case WV_98:
    case WV_ME:
        {
            // Running on Windows 9x. Get the system UI language from registry:
            CRegKeyEx key;
            if(ERROR_SUCCESS == key.Open(HKEY_USERS, _T(".Default\\Control Panel\\desktop\\ResourceLocale"), KEY_READ))
            {
                CString value = key.QueryValueString(_T(""));
                m_UILang = (LANGID)_tcstol(value, 0, 16);
            };
            
        }
        break;
    }
	// get the common controls dll version
	m_comCtl32Version = GetDllVersion(_T("comctl32.dll"));
}