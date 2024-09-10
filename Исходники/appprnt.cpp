BOOL CWinApp::CreatePrinterDC(CDC& dc)
{
	HDC hDC = AfxCreateDC(m_hDevNames, m_hDevMode);
	if (hDC != NULL)
	{
		dc.DeleteDC();
		VERIFY(dc.Attach(hDC));
		return TRUE;
	}
	return FALSE;
}