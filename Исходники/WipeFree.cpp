void CWipeFree::OnDmWipe() 
{
	LVITEM				lvitem;
	int					nSel;
	int					i;
	YG_PARTITION_INFO	*pTargetParInfo = NULL;
	CWipeProc			WipeProcDlg;
	BOOL				bSel = FALSE;
	CString				cstr,csCaption;
	TCHAR				szCurDir[MAX_PATH];
	TCHAR				szDir[32];

	UpdateData(TRUE);
	g_bBeepOff = m_BeepOff.GetCheck();

	nSel = m_SelMothed.GetCurSel ();
	g_nWipeMothed = nSel;

	csCaption.LoadString (IDS_DM_ERROR);

	lvitem.mask = LVIF_IMAGE;
	lvitem.iSubItem = 0;
	
	for(i = 0; i < m_WipeParList.GetItemCount (); i++) 
	{
		lvitem.iItem = i;
		m_WipeParList.GetItem(&lvitem);
		if(lvitem.iImage == IMG_LIST_SELECT) 
		{
			pTargetParInfo		= (YG_PARTITION_INFO*)m_WipeParList.GetItemData (i);
			g_pTargetParInfo	= pTargetParInfo;
			bSel				= TRUE;
			break;
		}
	}
	if(bSel)
	{
		if(g_pTargetParInfo->DriveLetter == _T('*'))
		{
			cstr.LoadString (IDS_Q_FORMAT_PARTITION);
			csCaption.LoadString (IDS_DM_INFO);
			MessageBox(cstr,csCaption,MB_OK);
			return ;
		}
		ZeroMemory(szDir, 32  * sizeof(TCHAR));
		_tcscpy(szDir,_T("C:\\"));
		szDir[0] = g_pTargetParInfo->DriveLetter;
		GetCurrentDirectory(MAX_PATH,szCurDir);
		if(!SetCurrentDirectory(szDir))
		{
			cstr.LoadString (IDS_Q_FORMAT_PARTITION);
			csCaption.LoadString (IDS_DM_INFO);
			MessageBox(cstr,csCaption,MB_OK);
			return ;
		}
		SetCurrentDirectory(szCurDir);
		cstr.Format (IDS_CONFIRM_WIPE_FREE,g_pTargetParInfo->DriveLetter);
		csCaption.LoadString (IDS_DM_CONFIRM_CAPTITION);
		if(IDYES == MessageBox (cstr,csCaption,MB_YESNO))
		{
			WipeProcDlg.m_DriveLetter = g_pTargetParInfo->DriveLetter;
			if (!g_bBeepOff) Beep(1000,100);
			WipeProcDlg.DoModal ();
		}

	}
}