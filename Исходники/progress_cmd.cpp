	ProgressTaskBar(__RPC__in HWND hwnd, ULONGLONG Total)
		: hwnd(hwnd)
		, Total(Total)
	{
		if (FAILED(CoInitialize(nullptr)))
			ATL::AtlThrowLastWin32();
		if (FAILED(TaskbarList.CoCreateInstance(CLSID_TaskbarList)))
			ATL::AtlThrowLastWin32();
	}