BOOL CWPDS_GeneralPage::WriteAuthorization()
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

		m_wpds->strUserName = str;

		GetDlgItemText (IDC_PASSWORD, str);
		m_wpds->strPassword = str;
	}
	else
	{
		m_wpds->strUserName = "";
		m_wpds->strPassword = "";
	}

	if (m_wpds->m_ppoOwner)
		m_wpds->m_ppoOwner->setDirty();

	return TRUE;
}