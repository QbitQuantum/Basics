void sunapp_register_classes() {
	HRESULT hr;
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FAILED(hr))
		alert("CoInitialize failed");

	IInternetSession* iis;
	hr = CoInternetGetSession(0, &iis, 0);
	if (FAILED(hr))
		alert("CoInternetGetSession failed");
	else {
		iis->RegisterNameSpace(&factory, CLSID_SuneidoAPP, L"suneido", 0, 0, 0);
		iis->Release();
	}
}