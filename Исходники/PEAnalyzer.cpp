int WINAPI wWinMain(_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hPrevInstance,
					_In_ LPWSTR    lpCmdLine,
					_In_ int       nCmdShow)
{
	if (!IsWindows7SP1OrGreater()) {
		MessageBoxW(nullptr, L"You need at least Windows 10.", L"Version Not Supported", MB_OK | MB_ICONERROR);
		return -1;
	}
	DotComInitialize dot;
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	return MetroWindowRunLoop();
}