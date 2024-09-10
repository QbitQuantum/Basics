version get_version()
{
#if (_MSC_VER >= oVS2015_VER)

	bool is_server = IsWindowsServer();

	//if (IsWindows10OrGreater())             return is_server ? windows::version::win10             : windows::version::win10;
	if (IsWindows8Point1OrGreater())        return is_server ? windows::version::server_2012_sp1   : windows::version::win8_1;
	if (IsWindows8OrGreater())              return is_server ? windows::version::server_2012       : windows::version::win8;
	if (IsWindows7SP1OrGreater())           return is_server ? windows::version::server_2008r2_sp1 : windows::version::win7_sp1;
	if (IsWindows7OrGreater())              return is_server ? windows::version::server_2008r2     : windows::version::win7;
	if (IsWindowsVistaSP2OrGreater())       return is_server ? windows::version::server_2008_sp2   : windows::version::vista_sp2;
	if (IsWindowsVistaSP1OrGreater())       return is_server ? windows::version::server_2008_sp1   : windows::version::vista_sp1;
	if (IsWindowsVistaOrGreater())          return is_server ? windows::version::server_2008       : windows::version::vista;
	if (IsWindowsXPSP3OrGreater())          return is_server ? windows::version::xp								 : windows::version::xp;
	if (IsWindowsXPSP2OrGreater())		      return is_server ? windows::version::xp_sp1						 : windows::version::xp_sp1;
	if (IsWindowsXPSP1OrGreater())		      return is_server ? windows::version::xp_sp2						 : windows::version::xp_sp2;
	if (IsWindowsXPOrGreater())				      return is_server ? windows::version::xp_sp3						 : windows::version::xp_sp3;
	if (IsWindowsVersionOrGreater(5, 2, 0)) return is_server ? windows::version::server_2003       : windows::version::xp_pro_64bit;
	if (IsWindowsVersionOrGreater(5, 0, 0)) return is_server ? windows::version::win2000           : windows::version::win2000;

#else
	OSVERSIONINFOEX osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (GetVersionEx((OSVERSIONINFO*)&osvi))
	{
		if (osvi.dwMajorVersion == 6)
		{
			if (osvi.dwMinorVersion == 2)
			{
				if (osvi.wServicePackMajor == 1)
					return osvi.wProductType == VER_NT_WORKSTATION ? version::win8_1 : version::server_2012_sp1;
				else if (osvi.wServicePackMajor == 0)
					return osvi.wProductType == VER_NT_WORKSTATION ? version::win8 : version::server_2012;
			}

			else if (osvi.dwMinorVersion == 1)
			{
				if (osvi.wServicePackMajor == 0)
					return osvi.wProductType == VER_NT_WORKSTATION ? version::win7 : version::server_2008r2;
				else if (osvi.wServicePackMajor == 1)
					return osvi.wProductType == VER_NT_WORKSTATION ? version::win7_sp1 : version::server_2008r2_sp1;
			}
			else if (osvi.dwMinorVersion == 0)
			{
				if (osvi.wServicePackMajor == 2)
					return osvi.wProductType == VER_NT_WORKSTATION ? version::vista_sp2 : version::server_2008_sp2;
				else if (osvi.wServicePackMajor == 1)
					return osvi.wProductType == VER_NT_WORKSTATION ? version::vista_sp1 : version::server_2008_sp1;
				else if (osvi.wServicePackMajor == 0)
					return osvi.wProductType == VER_NT_WORKSTATION ? version::vista : version::server_2008;
			}
		}

		else if (osvi.dwMajorVersion == 5)
		{
			if (osvi.dwMinorVersion == 2)
			{
				SYSTEM_INFO si;
				GetSystemInfo(&si);
				if ((osvi.wProductType == VER_NT_WORKSTATION) && (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64))
					return version::xp_pro_64bit;
				else if (osvi.wSuiteMask & 0x00008000 /*VER_SUITE_WH_SERVER*/)
					return version::home_server;
				else
					return GetSystemMetrics(SM_SERVERR2) ? version::server_2003r2 : version::server_2003;
			}

			else if (osvi.dwMinorVersion == 1)
				return version::xp;
			else if (osvi.dwMinorVersion == 0)
				return version::win2000;
		}
	}
#endif

	return version::unknown;
}