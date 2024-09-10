BOOL CPrg_Data::OnApply() 
{
	UINT nVal;

	nVal = GetDlgItemInt (IDC_AUTOSAVE, NULL, FALSE);

	
	if (nVal == 0)
	{
		
		CString str; str.Format (LS (L_ENTERGREATER), 0);
		MessageBox (str, LS (L_INPERR), MB_ICONEXCLAMATION);
		CEdit *pE = (CEdit*) GetDlgItem (IDC_AUTOSAVE);
		pE->SetSel (0, -1);
		pE->SetFocus ();
		return FALSE;
	}

	_App.AutosaveInterval (nVal * 60 * 1000);

	CString strOldVal = _App.DataFolder ();
	CString str;
	if (IsDlgButtonChecked (IDC_KEEP_2) == BST_CHECKED)
		GetDlgItemText (IDC_FOLDER, str);
	if (strOldVal != str)
	{
		_App.DataFolder (str);

		CRegKey key;
		if (ERROR_SUCCESS != key.Create (HKEY_CURRENT_USER, "Software\\FreeDownloadManager.ORG\\Free Upload Manager"))
			key.Open (HKEY_CURRENT_USER, "Software\\FreeDownloadManager.ORG\\Free Upload Manager");

		key.SetValue (fsGetAppDataFolder (), "force_data_folder");

		if (IDYES == MessageBox (LS (L_COPYDATAFILESNOW), NULL, MB_YESNO))
		{
			vmsCopyFiles (fsGetAppDataFolder (), _App.DataFolder (), "*.sav");
			extern bool _bNeedRecalcAppDataFolder;
			_bNeedRecalcAppDataFolder = true;
		}
		else
		{
			MessageBox (LS (L_RESTARTISREQ));
		}
	}
	
	return CPropertyPage::OnApply();
}