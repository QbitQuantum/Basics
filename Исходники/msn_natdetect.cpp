static bool IsIcfEnabled(void)
{
	HRESULT hr;
	VARIANT_BOOL fwEnabled = VARIANT_FALSE;

	INetFwProfile* fwProfile = NULL;
	INetFwMgr* fwMgr = NULL;
	INetFwPolicy* fwPolicy = NULL;
	INetFwAuthorizedApplication* fwApp = NULL;
	INetFwAuthorizedApplications* fwApps = NULL;
	BSTR fwBstrProcessImageFileName = NULL;
	wchar_t *wszFileName = NULL;

	hr = CoInitialize(NULL);
	if (FAILED(hr)) return false;

	// Create an instance of the firewall settings manager.
	hr = CoCreateInstance(CLSID_NetFwMgr, NULL, CLSCTX_INPROC_SERVER,
			IID_INetFwMgr, (void**)&fwMgr );
	if (FAILED(hr)) goto error;

	// Retrieve the local firewall policy.
	hr = fwMgr->get_LocalPolicy(&fwPolicy);
	if (FAILED(hr)) goto error;

	// Retrieve the firewall profile currently in effect.
	hr = fwPolicy->get_CurrentProfile(&fwProfile);
	if (FAILED(hr)) goto error;

	// Get the current state of the firewall.
	hr = fwProfile->get_FirewallEnabled(&fwEnabled);
	if (FAILED(hr)) goto error;

	if (fwEnabled == VARIANT_FALSE) goto error;

	// Retrieve the authorized application collection.
	hr = fwProfile->get_AuthorizedApplications(&fwApps);
	if (FAILED(hr)) goto error;

	TCHAR szFileName[MAX_PATH];
	GetModuleFileName(NULL, szFileName, SIZEOF(szFileName));

	wszFileName = mir_t2u(szFileName);

	// Allocate a BSTR for the process image file name.
	fwBstrProcessImageFileName = SysAllocString(wszFileName);
	if (FAILED(hr)) goto error;

	// Attempt to retrieve the authorized application.
	hr = fwApps->Item(fwBstrProcessImageFileName, &fwApp);
	if (SUCCEEDED(hr))
	{
		// Find out if the authorized application is enabled.
		fwApp->get_Enabled(&fwEnabled);
		fwEnabled = ~fwEnabled;
	}

error:
	// Free the BSTR.
	SysFreeString(fwBstrProcessImageFileName);
	mir_free(wszFileName);

	// Release the authorized application instance.
	if (fwApp != NULL) fwApp->Release();

	// Release the authorized application collection.
	if (fwApps != NULL) fwApps->Release();

	// Release the firewall profile.
	if (fwProfile != NULL) fwProfile->Release();

	// Release the local firewall policy.
	if (fwPolicy != NULL) fwPolicy->Release();

	// Release the firewall settings manager.
	if (fwMgr != NULL) fwMgr->Release();

	CoUninitialize();

	return fwEnabled != VARIANT_FALSE;
}