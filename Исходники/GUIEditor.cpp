//---------------------------------------------------------------------
// Function:	EditDocument
// Description:	Edit an GUIEditor Document retrieving initial data 
//					from a archive
// Parameters:	ar = archive to load into document
// Returns:		DWORD = possible error or 0 for no error
//---------------------------------------------------------------------
DWORD CGUIEditor::EditDocument()
{
	if (!m_bCreated)
	{
		SetupTabBar();
		m_bCreated = true;
	}
	if (!m_bDocOpen)
	{
		StdString res;
		ReadINIKey(_T("LastUsedResolution"), res, _T("GUIEditor"), _T("800x600"));
		StdString x, y;
		res.GetToken(_T("x"), x);
		res.GetToken(_T("x"), y);
		UINT iX, iY;
		iX = (UINT)atoi(x.c_str());
		iY = (UINT)atoi(y.c_str());
		CreateDocView(iX, iY);
	}
	else
	{
		MessageBox(NULL, _T("Can't have more than one GUI open at a time"), _T("Sorry, mac"), MB_OK);
	}
	return NO_ERROR;
}