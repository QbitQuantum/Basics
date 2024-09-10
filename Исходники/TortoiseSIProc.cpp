CTortoiseSIProcApp::CTortoiseSIProcApp()
{
	CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) _T(": CTortoiseSIProcApp()\n"));

	// Remove the current directory from the default DLL search order.
	// Search in System32, System, Windows and the PATH.
	SetDllDirectory(L"");

	// Use HTML help for this application
	EnableHtmlHelp();

	m_bLoadUserToolbars = FALSE;
	m_bSaveState = FALSE;
	m_bRetSuccess = false;
	m_gdiplusToken = NULL;

	// Programs compiled with 64-bit VS 2013 C++ compiler crash with "0xC000001D: Illegal Instruction" on
	// Windows 7 x64 SP1 if support for the AVX2 is not available on the CPU.  This is the work-around.
#if defined (_WIN64) && _MSC_VER >= 1800
	_set_FMA3_enable(0);
#endif
}