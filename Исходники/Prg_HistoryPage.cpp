BOOL CPrg_HistoryPage::OnApply() 
{
	if (IsDlgButtonChecked (IDC_USEHIST) == BST_UNCHECKED)
	{
		_App.History_Use (FALSE);
	}
	else
	{
		int cMaxDays = INT_MAX;
		if (IsDlgButtonChecked (IDC_DELRECTHATEXISTS) == BST_CHECKED)
		{
			cMaxDays = GetDlgItemInt (IDC_DAYS);
			if (cMaxDays == 0)
			{
				CString str;
				str.Format (LS (L_ENTERGREATER), 0);
				MessageBox (str, LS (L_INPERR), MB_ICONEXCLAMATION);
				CEdit *pE = (CEdit*) GetDlgItem (IDC_DAYS);
				pE->SetSel (0, -1);
				pE->SetFocus ();
				return FALSE;
			}
		}

		int cMaxRecs = INT_MAX;
		if (IsDlgButtonChecked (IDC_MAXNUMBER) == BST_CHECKED)
		{
			cMaxRecs = GetDlgItemInt (IDC_MAXNUMBERVAL);
			if (cMaxRecs == 0)
			{
				CString str;
				str.Format (LS (L_ENTERGREATER), 0);
				MessageBox (str, LS (L_INPERR), MB_ICONEXCLAMATION);
				CEdit *pE = (CEdit*) GetDlgItem (IDC_MAXNUMBERVAL);
				pE->SetSel (0, -1);
				pE->SetFocus ();
				return FALSE;
			}
		}

		_App.History_FoldersOnly (
			IsDlgButtonChecked (IDC_FOLDERSONLY) == BST_CHECKED);

		_App.History_KeepDays (cMaxDays);
		_App.History_MaxRecords (cMaxRecs);
		_App.History_Use (TRUE);
	}

	_HsMgr.ReadSettings ();
	
	return CPropertyPage::OnApply();
}