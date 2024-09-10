BOOL CSpiderAddPageDlg::WriteAuthorization()
{
	if (IsDlgButtonChecked (IDC_USELOGIN) == BST_CHECKED)
	{
		CString str;
		GetDlgItemText (IDC_USER, str);
		if (str == "")
		{
			MessageBox (LS (L_ENTERUSER), LS (L_INPERR), MB_ICONEXCLAMATION);
			CEdit *pE = (CEdit*) GetDlgItem (IDC_USER);
			pE->SetFocus ();
			pE->SetSel (0, -1);
			return FALSE;
		}

		m_wpd->GetWDPS ()->strUserName = str;

		GetDlgItemText (IDC_PASSWORD, str);
		m_wpd->GetWDPS ()->strPassword = str;
		m_wpd->setDirty();
	}

	return TRUE;

}