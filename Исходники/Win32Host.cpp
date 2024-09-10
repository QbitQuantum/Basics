void Win32Host::UnInitialize()
{
	// Shut down the CEF
	//CefShutdown();
	// Shut down COM.
	OleUninitialize();
	MCruxWin32Window::unInitWindowClass(GetModuleHandle(NULL));
}