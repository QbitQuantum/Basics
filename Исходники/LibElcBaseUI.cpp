BOOL CLibElcBaseUIApp::InitInstance()
{
	CWinApp::InitInstance();

	m_hResource = LoadResourceLibrary(_T("LibElcBaseUIRes.dll"));
	if (m_hResource) {
		AfxSetResourceHandle(m_hResource);
	}

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	CString strSkinPath;
	GetL10NDirectory(strSkinPath);
	strSkinPath += _T("Skins\\SkinUI.xml");

	if (!theSkin.LoadFile(strSkinPath)) {
		//ElcMessageBox(IDS_ERROR_LOAD_SKIN, MB_OK|MB_ICONERROR);
		//return FALSE;
	}

	return TRUE;
}