int CDataLoggerApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	GdiplusShutdown(m_pGdiToken);
	return CWinApp::ExitInstance();
}