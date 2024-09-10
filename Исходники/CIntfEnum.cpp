int CIntfEnum::CreateEnumNotifWnd(HINSTANCE hInstance)
{
	if(hInstance)
	{
		WNDCLASSW WndClass;
		WndClass.style = 0;
		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hIcon = 0;
		WndClass.hCursor = 0;
		WndClass.hbrBackground = 0;
		WndClass.lpszMenuName = 0;
		WndClass.lpfnWndProc = CIntfEnum::EnumNotifWndProcStatic;
		WndClass.hInstance = hInstance;
		WndClass.lpszClassName = L"CIntfEnumNotifWnd";
		g_pEnumerator = this;
		RegisterClassW(&WndClass);
		m_hEnumNotifWnd = CreateWindowExW(0x80, L"CIntfEnumNotifWnd", L"CIntfEnumNotifWnd", 0x80000000u, 0, 0, 0, 0, 0, 0, hInstance, (LPVOID)this);
		if(m_hEnumNotifWnd)
		{
			ShowWindow(m_hEnumNotifWnd, 0);
		}
	}
	m_hSetupApiLibrary = LoadLibraryW(L"SetupApi.dll");
	if(m_hSetupApiLibrary)
	{
#define RESOLVE_SETUPAPI_FUNC(def) do{if(!(m_pfn##def = (Def_##def*)GetProcAddress(m_hSetupApiLibrary, #def)))return 0;}while(0)
		RESOLVE_SETUPAPI_FUNC(CM_Get_Parent);
		RESOLVE_SETUPAPI_FUNC(CM_Get_Depth);
		RESOLVE_SETUPAPI_FUNC(CM_Get_Device_IDA);
		RESOLVE_SETUPAPI_FUNC(CM_Locate_DevNodeA);
		RESOLVE_SETUPAPI_FUNC(CMP_WaitNoPendingInstallEvents);
		RESOLVE_SETUPAPI_FUNC(SetupDiGetClassDevsW);
		RESOLVE_SETUPAPI_FUNC(SetupDiGetDeviceInterfaceDetailW);
		RESOLVE_SETUPAPI_FUNC(SetupDiGetDeviceRegistryPropertyW);
		RESOLVE_SETUPAPI_FUNC(SetupDiEnumDeviceInterfaces);
		RESOLVE_SETUPAPI_FUNC(SetupDiDestroyDeviceInfoList);
		RESOLVE_SETUPAPI_FUNC(SetupDiEnumDeviceInfo);
		RESOLVE_SETUPAPI_FUNC(SetupDiOpenDeviceInterfaceRegKey);
		return 1;
	#undef RESOLVE_SETUPAPI_FUNC
	}
	return 0;
}