BOOL CPuzzleGameApp::ExitInstance()
{
	GdiplusShutdown(m_gdiplusToken);
	return CWinApp::ExitInstance();
}