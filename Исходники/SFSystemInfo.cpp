bool SFSystemInfo::InitializeOSInfo()
{
	// 2014.07.02 최흥배 GetVersionEx를 MS에서 비추천 API로 지정되어서 새 API로 OS의 간단한 정보만 얻었습니다.
	// MSDN의 OS 버전 번호 http://msdn.microsoft.com/en-us/library/ms724832(v=vs.85).aspx

	if (IsWindowsServer())
	{
		m_OSInfo.isServer = true;
	}

	if (IsWindows8Point1OrGreater())
	{
		if (m_OSInfo.isServer)
			m_OSInfo.szOperatingSystem = "Windows Server 2012 R2 or Grater";
		else
			m_OSInfo.szOperatingSystem = "Windows 8.1 or Grater";

		m_OSInfo.majorVer = 6;
		m_OSInfo.minorVer = 3;
	}
	else if (IsWindows8OrGreater())
	{
		if (m_OSInfo.isServer)
			m_OSInfo.szOperatingSystem = "Windows Server 2012";
		else
			m_OSInfo.szOperatingSystem = "Windows 8";

		m_OSInfo.majorVer = 6;
		m_OSInfo.minorVer = 2;
	}
	else if (IsWindows7OrGreater())
	{
		if (m_OSInfo.isServer)
			m_OSInfo.szOperatingSystem = "Windows Server 2008 R2";
		else
			m_OSInfo.szOperatingSystem = "Windows 7";

		m_OSInfo.majorVer = 6;
		m_OSInfo.minorVer = 1;
	}
	else if (IsWindowsVistaOrGreater())
	{
		if (m_OSInfo.isServer)
			m_OSInfo.szOperatingSystem = "Windows Server 2008";
		else
			m_OSInfo.szOperatingSystem = "Windows Vista";

		m_OSInfo.majorVer = 6;
		m_OSInfo.minorVer = 0;
	}
	else if (IsWindowsXPOrGreater())
	{
		if (m_OSInfo.isServer)
			m_OSInfo.szOperatingSystem = "Windows Server 2003";
		else
			m_OSInfo.szOperatingSystem = "Windows XP";

		m_OSInfo.majorVer = 5;
		m_OSInfo.minorVer = 1;
	}

	return true; 
}