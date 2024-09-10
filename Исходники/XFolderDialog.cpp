//=============================================================================
void CXFolderDialog::OnCbnKillfocusMruCombo()
//=============================================================================
{
	CString strFolder = _T("");
	m_cmbRecentFolders.GetWindowText(strFolder);
	
	if (!strFolder.IsEmpty() && (_taccess(strFolder, 00) == 0))
	{
		CWnd *pWnd = GetParent();
		if (pWnd && ::IsWindow(pWnd->m_hWnd))
		{
			// change to new folder, leave file name control unchanged
			TCHAR szText[MAX_PATH*2];
			szText[0] = _T('\0');
			pWnd->GetDlgItem(m_nIdFileNameCombo)->SendMessage(WM_GETTEXT,
				sizeof(szText)/sizeof(TCHAR)-2, (LPARAM)szText);
			pWnd->SendMessage(CDM_SETCONTROLTEXT, m_nIdFileNameCombo,
				(LPARAM)(LPCTSTR)strFolder);
			pWnd->SendMessage(WM_COMMAND, MAKEWPARAM(IDOK, BN_CLICKED),
				(LPARAM)GetDlgItem(IDOK)->GetSafeHwnd());
			pWnd->SendMessage(CDM_SETCONTROLTEXT, m_nIdFileNameCombo,
				(LPARAM)szText);
			
			m_strPath = strFolder;
		}
	}
}