int CCugWorkSpaceApp::ExitInstance() 
{
	BCGCBProCleanUp();
	GdiplusShutdown(m_gdiplusToken);
	return CWinApp::ExitInstance();
}