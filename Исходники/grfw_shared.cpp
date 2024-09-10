	std::wstring Globals::LaunchPath()
	{ 
		if (!m_bLPGenerated)
		{
			auto drive = new wchar_t[260];
			auto name = &drive[4];
			GetModuleFileName(GetModuleHandle(nullptr), name, 256);
			auto temp = static_cast<LPCWSTR>(name);
			_wsplitpath_s(temp, drive, 3, name, 256, nullptr, 0, nullptr, 0);
			m_wsLaunchPath = lstrcatW(drive, static_cast<LPCWSTR>(name));
			SetCurrentDirectory(m_wsLaunchPath.data());
			m_bLPGenerated = true;
		}
		return m_wsLaunchPath;
	}