int CFloatApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	GdiplusShutdown(m_gdiplusToken);
	return CWinApp::ExitInstance();
}