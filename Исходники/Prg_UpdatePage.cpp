BOOL CPrg_UpdatePage::OnApply() 
{
	CString str;

	GetDlgItemText (IDC_UPDATEURL, str);

	
	if (str [str.GetLength () - 1] != '\\' && str [str.GetLength () - 1] != '/')
		str += '/';

	fsURL url;
	if (url.Crack (str) != IR_SUCCESS || *url.GetHostName () == 0)
	{
		MessageBox (LS (L_CHECKURL), LS (L_INPERR), MB_ICONEXCLAMATION);
		CEdit *pE = (CEdit*) GetDlgItem (IDC_UPDATEURL);
		pE->SetSel (0, -1);
		pE->SetFocus ();
		return FALSE;
	}

	_UpdateMgr.m_strUpdateUrl = _UpdateMgr.m_strDlFullInstallPath = _UpdateMgr.m_strDlUpgradesPath = str;

	if (IsDlgButtonChecked (IDC_AUTOUPDATES_INSTALL) == BST_CHECKED)
		_UpdateMgr.m_enAUT = AUT_DLANDINST;
	else if (IsDlgButtonChecked (IDC_AUTOUPDATES_NOTIFYONLY) == BST_CHECKED)
		_UpdateMgr.m_enAUT = AUT_NOTIFYONLY;
	else
		_UpdateMgr.m_enAUT = AUT_TURNOFF;
	
	return CPropertyPage::OnApply();
}