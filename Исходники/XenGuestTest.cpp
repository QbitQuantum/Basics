void test_remote()
{
	HRESULT hr;
	COSERVERINFO csi = {0, L"10.204.2.52", 0, 0};
	MULTI_QI mqi[] = {&IID_IXenGuestServices, NULL, S_OK};

	::CoInitializeEx(NULL, COINIT_MULTITHREADED);

	hr = CoCreateInstanceEx(CLSID_XenGuestServices, NULL, CLSCTX_SERVER, &csi, 1, mqi);
}