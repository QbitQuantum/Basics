int CLayeredApp::ExitInstance()
{
    GdiplusShutdown(m_GdiplusToken);

    return CWinApp::ExitInstance();
}