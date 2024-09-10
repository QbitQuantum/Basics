void CCreateTPDownloadDlg::OnOk()
{
	if (IR_SUCCESS != Crack(m_strUrl))
		return WrongURL ();

	GetDlgItemText (IDC_SAVEAS, m_strFileName);

	int nDldType = m_wndDldType.GetCurSel ();

	if (nDldType == 1)	
	{
		char sz [MY_MAX_PATH];
		GetTempPath (sizeof (sz), sz);
		m_strOutFolder = sz;
	}
	else
	{
		if (FALSE == _CheckFolderName (this, IDC_OUTFOLDER))
			return;
		GetDlgItemText (IDC_OUTFOLDER, m_strOutFolder);
	
		if (IsDlgButtonChecked (IDC_FILEAUTO) == BST_UNCHECKED)
		{
			if (m_strFileName == "")
			{
				MessageBox (LS (L_EMPTY), LS (L_INPERR), MB_ICONEXCLAMATION);
				GetDlgItem (IDC_SAVEAS)->SetFocus ();
				return;
			}
			if (FALSE == _CheckFileName (this, IDC_SAVEAS))
				return;
			_App.NewDL_GenerateNameAutomatically (FALSE);
		}
		else
			_App.NewDL_GenerateNameAutomatically (TRUE);
	}

	fsPathToGoodPath ((LPSTR)(LPCSTR)m_strOutFolder);
	fsPathToGoodPath ((LPSTR)(LPCSTR)m_strFileName);

	if (m_strOutFolder.GetLength () == 0)
	{
		MessageBox (LS (L_ENTERFLRNAME), LS (L_INPERR), MB_ICONEXCLAMATION);
		GetDlgItem (IDC_OUTFOLDER)->SetFocus ();
		return;
	}

	if (nDldType != 1)
		_LastFolders.AddRecord (m_strOutFolder);
	_LastUrlFiles.AddRecord (m_strUrl);

	if (m_strOutFolder [m_strOutFolder.GetLength () - 1] != '\\' && 
		m_strOutFolder [m_strOutFolder.GetLength () - 1] != '/')
		m_strOutFolder += '\\';

	if (_App.NewGrp_SelectWay () == NGSW_USE_ALWAYS_SAME_GROUP_WITH_OUTFOLDER_AUTO_UPDATE)
	{
		vmsDownloadsGroupSmartPtr pGrp = _DldsGrps.FindGroup (_App.NewDL_GroupId ());
		if (pGrp != NULL) {
			pGrp->strOutFolder = m_strOutFolder;
			pGrp->setDirty();
		}
	}
	
	if (_App.CheckIfDownloadWithSameUrlExists ())
	{
		int ret = _CheckDownloadAlrExists (m_dld);
		if (ret)
		{
			if (ret == 1)
				EndDialog (ID_DLNOTADDED);
			return;
		}
	}

	m_dld->pGroup = m_wndGroups.GetSelectedGroup ();

	GetDlgItemText (IDC_COMMENT, m_dld->strComment);

	BOOL bUseZipPreview = _App.NewDL_UseZIPPreview ();
	_App.UseZipPreview (bUseZipPreview);

	if (nDldType == 1)
	{
		m_dld->dwFlags |= DLD_DELETEWHENDONE | DLD_DELETEFILEATRESTART;
	}
	else if (nDldType == 2)
		m_dld->dwFlags |= DPF_STARTWHENDONE;

	m_wndGroups.RememberSelectedGroup ();

	m_nStreamingSpeed = GetDlgItemInt (IDC_STRSPEED);

	if (m_bThread)
	{
		m_bNeedExit = TRUE;
		while (m_bThread);
	}

	_App.OnDlHasBeenCreatedByUser ();

	m_bPlaceAtTop = IsDlgButtonChecked (IDC_PLACEATTOP) == BST_CHECKED;

	CDialog::OnOK();
}