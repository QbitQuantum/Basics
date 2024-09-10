/////////////////////////////////////////////////////////////////////////////
// AppMainApp initialization
BOOL AppMainApp::InitATL()
{
	m_bATLInited = TRUE;
	HRESULT hRes = OleInitialize(NULL);
/*#if _WIN32_WINNT >= 0x0400
		HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
		HRESULT hRes = CoInitialize(NULL);
#endif*/
	if (FAILED(hRes))
	{
		m_bATLInited = FALSE;
		return FALSE;
	}
	return TRUE;
}