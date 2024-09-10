void CXTPSyntaxEditPropertiesPageColor::OnDblClickSchema()
{
	int iIndex = m_lboxName.GetCurSel();
	if (iIndex == LB_ERR)
		return;

	XTP_EDIT_SCHEMAFILEINFO* pSchemaInfo = (XTP_EDIT_SCHEMAFILEINFO*)m_lboxName.GetItemData(iIndex);
	if (pSchemaInfo == NULL)
		return;

	if (!FILEEXISTS_S(pSchemaInfo->csValue))
		return;

	TCHAR szDrive[_MAX_DRIVE], szDir[_MAX_DIR], szFileName[_MAX_FNAME], szEx[_MAX_EXT];
	SPLITPATH_S(pSchemaInfo->csValue, szDrive, szDir, szFileName, szEx);

	CString csBuffer;
	XTPResourceManager()->LoadString(
		&csBuffer, XTP_IDS_EDIT_OPENSCHEMAMSG);

	CString csMessage;
	csMessage.Format(csBuffer, szFileName, szEx);
	if (AfxMessageBox(csMessage, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		// close the options dialog.
		CPropertySheet* pWndParent = DYNAMIC_DOWNCAST(CPropertySheet, GetParent());
		if (pWndParent)
			pWndParent->EndDialog(IDCANCEL);

		// open the document.
		CWinApp* pWinApp = AfxGetApp();
		if (pWinApp)
			pWinApp->OpenDocumentFile(pSchemaInfo->csValue);
	}
}