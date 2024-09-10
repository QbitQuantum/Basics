void NetworkStatus::InitializeLoop()
{
	CoInitializeEx(0, COINIT_MULTITHREADED);
	HRESULT result = CoInitializeSecurity(0, -1, 0, 0, RPC_C_AUTHN_LEVEL_DEFAULT,
		RPC_C_IMP_LEVEL_IMPERSONATE, 0, EOAC_NONE, 0 );
	if (FAILED(result))
	{
		HandleHResultError("Failed to initialize COM security", result);
		return;
	}

	result = CoCreateInstance(CLSID_WbemAdministrativeLocator, 0,
		CLSCTX_INPROC_SERVER, IID_IWbemLocator,
		reinterpret_cast<void**>(&locator));
	if (FAILED(result))
	{
		HandleHResultError("Failed to initialize NetworkStatus locator", result);
		return;
	}

	result = locator->ConnectServer(L"root\\cimv2", 0, 0, 0,
		WBEM_FLAG_CONNECT_USE_MAX_WAIT, NULL, NULL, &service);
	if (FAILED(result))
	{
		HandleHResultError("Failed to initialize NetworkStatus service", result);
		return;
	}
}