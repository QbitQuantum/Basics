HRESULT AppUtils::LaunchApplication(LPCWSTR packageFullName, PDWORD pdwProcessId)
{
	CComPtr<IApplicationActivationManager> spAppActivationManager;
	HRESULT result = E_INVALIDARG;

	/* Initialize IApplicationActivationManager */
	result = CoCreateInstance(CLSID_ApplicationActivationManager,
		NULL,
		CLSCTX_LOCAL_SERVER,
		IID_IApplicationActivationManager,
		(LPVOID*)&spAppActivationManager);

	if (!SUCCEEDED(result)) return result;

	/* This call ensures that the app is launched as the foreground window */
	result = CoAllowSetForegroundWindow(spAppActivationManager, NULL);

	/* Launch the app */
	if (!SUCCEEDED(result)) return result;

	result = spAppActivationManager->ActivateApplication(packageFullName, NULL, AO_NONE, pdwProcessId);

	return result;
}