/*static*/ std::string SuperCardProWin32::GetDevicePath ()
{
	std::string path;

	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_PORTS, nullptr, nullptr, DIGCF_PRESENT);
	if (hDevInfo != INVALID_HANDLE_VALUE)
	{
		for (int i = 0; ; ++i)
		{
			char szInstanceId[256];
			SP_DEVINFO_DATA DevInfoData = { sizeof(DevInfoData) };

			if (SetupDiEnumDeviceInfo(hDevInfo, i, &DevInfoData) &&
				SetupDiGetDeviceInstanceId(hDevInfo, &DevInfoData, szInstanceId, sizeof(szInstanceId), nullptr))
			{
				if (!strstr(szInstanceId, "SCP-JIM"))
					continue;

				HKEY hkey = SetupDiOpenDevRegKey(hDevInfo, &DevInfoData, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
				if (hkey != INVALID_HANDLE_VALUE)
				{
					char szPort[256];
					DWORD dwType = REG_SZ, dwSize = sizeof(szPort) / 2;
					if (SUCCEEDED(RegQueryValueEx(hkey, "PortName", nullptr, &dwType, (PBYTE)szPort, &dwSize)))
						path = std::string(R"(\\.\)") + szPort;
					RegCloseKey(hkey);
					break;
				}
			}
			else if (GetLastError() == ERROR_NO_MORE_ITEMS)
				break;
		}

		SetupDiDestroyDeviceInfoList(hDevInfo);
	}
	return path;
}

/*static*/ std::unique_ptr<SuperCardPro> SuperCardProWin32::Open ()
{
	std::string path = GetDevicePath();
	if (!path.empty())
	{
		HANDLE h = CreateFile(path.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
		if (h != INVALID_HANDLE_VALUE)
		{
			DCB dcb = { sizeof(dcb) };
			if (BuildCommDCB("baud=9600 parity=N data=8 stop=1", &dcb) && SetCommState(h, &dcb))
				return std::unique_ptr<SuperCardPro>(new SuperCardProWin32(h));
		}
	}
	return std::unique_ptr<SuperCardPro>();
}

SuperCardProWin32::SuperCardProWin32 (HANDLE hdev)
	: m_hdev(hdev), m_dwError(ERROR_SUCCESS)
{
}

SuperCardProWin32::~SuperCardProWin32 ()
{
	CloseHandle(m_hdev);
}

bool SuperCardProWin32::Read (void *p, int len, int *bytes_read)
{
	DWORD dwBytesRead = 0;
	if (!ReadFile(m_hdev, p, static_cast<DWORD>(len), &dwBytesRead, nullptr))
	{
		m_dwError = GetLastError();
		return false;
	}

	*bytes_read = static_cast<int>(dwBytesRead);
	return true;
}