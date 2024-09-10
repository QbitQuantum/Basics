HRESULT CAddFunctionDlg::SetTemplatePieces()
{
	HRESULT hr = NOERROR;
	CTemplateManagement *pTM = NULL;
	BOOL fDelete = false;
	try
	{
		// Wenn Notification, dann alle Funktionselemente aus diesem Item holen
		if (1 == m_chckNotification.GetCheck()) 
		{	// Istein Text im EditCtrl ?
			CString str;
			m_cbxNotification.GetWindowText(str);
			if (str.IsEmpty()) _com_issue_error(E_INVALIDARG);
			// Wenn je, liefere den Index
			int iFind = m_cbxNotification.FindString(-1, str);
			if (CB_ERR == iFind) _com_issue_error(E_FAIL);
			// Den Templtemenager geben lassen
			DWORD dw = m_cbxNotification.GetItemData(iFind);
			if (CB_ERR == dw) _com_issue_error(E_FAIL);
			pTM = (CTemplateManagement *)dw;
		} 
		else 
		{
			fDelete = true;
			THROW_FAILED_HRESULT(MakeTemplate(&pTM));
		}

		char str	[MAXSTRLENGTH]; *str = '\0';
		char strType[MAXSTRLENGTH];	*strType = '\0';
		char strPar [MAXSTRLENGTH];	*strPar = '\0';
		char strName[MAXSTRLENGTH];	*strName = '\0';
		char strComment[MAXSTRLENGTH]; *strComment = '\0';

		THROW_FAILED_HRESULT(pTM -> GetComment(strComment, MAXSTRLENGTH));
		THROW_FAILED_HRESULT(pTM -> GetDeclaration(str, MAXSTRLENGTH));
		THROW_FAILED_HRESULT(pTM -> GetParams(strPar, MAXSTRLENGTH));
		THROW_FAILED_HRESULT(pTM -> GetName(strName, MAXSTRLENGTH));
		THROW_FAILED_HRESULT(pTM -> GetType(strType, MAXSTRLENGTH));

		m_strTyp = strType;		
		m_strParams = strPar;
		m_strDeclaration = str;
		m_strName = strName;
		m_strComment = strComment;
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	if (fDelete) DELETE_OBJ(pTM);
	return hr;
}