void SSLManager::loadSecurityLibrary()
{
	if (_hSecurityModule) return;

	OSVERSIONINFO VerInfo;
	std::wstring dllPath;

	// Find out which security DLL to use, depending on
	// whether we are on Win2k, NT or Win9x

	VerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (!GetVersionEx(&VerInfo))
		throw Poco::SystemException("Cannot determine OS version");

#if defined(_WIN32_WCE)
	dllPath = L"Secur32.dll";
#else
	if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT 
		&& VerInfo.dwMajorVersion == 4)
	{
		dllPath = L"Security.dll";
	}
	else if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ||
		VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT )
	{
		dllPath = L"Secur32.dll";
	}
	else
	{
		throw Poco::SystemException("Cannot determine which security DLL to use");
	}
#endif

	//
	//  Load Security DLL
	//

	_hSecurityModule = LoadLibraryW(dllPath.c_str());
	if(_hSecurityModule == 0)
	{
		throw Poco::SystemException("Failed to load security DLL");
	}

#if defined(_WIN32_WCE)
	INIT_SECURITY_INTERFACE pInitSecurityInterface = (INIT_SECURITY_INTERFACE)GetProcAddressW( _hSecurityModule, L"InitSecurityInterfaceW");
#else
	INIT_SECURITY_INTERFACE pInitSecurityInterface = (INIT_SECURITY_INTERFACE)GetProcAddress( _hSecurityModule, "InitSecurityInterfaceW");
#endif

	if (!pInitSecurityInterface)
	{
		FreeLibrary(_hSecurityModule);
		_hSecurityModule = 0;
		throw Poco::SystemException("Failed to initialize security DLL (no init function)");
	}

	PSecurityFunctionTable pSecurityFunc = pInitSecurityInterface();
	if (!pSecurityFunc)
	{
		FreeLibrary(_hSecurityModule);
		_hSecurityModule = 0;
		throw Poco::SystemException("Failed to initialize security DLL (no function table)");
	}

	CopyMemory(&_securityFunctions, pSecurityFunc, sizeof(_securityFunctions));
}