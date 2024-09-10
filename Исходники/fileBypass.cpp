	filePathLinkA(const string& path) :m_ntType("\\??\\")
	{
		if (path.length() > 4 && path.substr(0, 4) == "\\??\\")
		{
			m_ntType.append(path.substr(4));
		}
		else
		{
			m_ntType.append(path);
		}
		static DWORD tick = 0;
		char tmpBuffer[100];
		StringCbPrintfA(tmpBuffer, 100, "%x%x%x%x", GetCurrentThreadId(), GetTickCount(), rand(), ++tick);
		m_pathDefine = string(FS_BYPASS_DEFINE_PREFIX_A) + tmpBuffer;
		if (DefineDosDeviceA(DDD_RAW_TARGET_PATH, m_pathDefine.c_str(), m_ntType.c_str()))
		{
			m_pathLink = string("\\\\.\\") + FS_BYPASS_DEFINE_PREFIX_A + tmpBuffer;
			m_transformed = true;
		}
		else
		{
			m_pathLink = path;
			m_transformed = false;
		}
	}