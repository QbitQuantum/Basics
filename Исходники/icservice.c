HRESULT init_icservice() {
	HRESULT hr = -1;

	CoInitialize(NULL);
	CoInitializeSecurity(NULL, -1, NULL, NULL,
		RPC_C_AUTHN_LEVEL_PKT,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL, EOAC_NONE, NULL);
	hr = CoCreateInstance(
		&(CLSID_NetSharingManager),
		NULL,
		CLSCTX_ALL,
		&(IID_INetSharingManager),
		(void**)&sharing_manager);

	return hr;
}