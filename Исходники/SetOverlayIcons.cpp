BOOL CSetOverlayIcons::OnInitDialog()
{
	ISettingsPropPage::OnInitDialog();

	m_cIconList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_INFOTIP | LVS_EX_SUBITEMIMAGES);
	// get the path to our icon sets
	TCHAR buf[MAX_PATH] = {0};
	SHGetSpecialFolderPath(m_hWnd, buf, CSIDL_PROGRAM_FILES_COMMON, true);
	m_sIconPath = buf;
	m_sIconPath += _T("\\TortoiseOverlays\\Icons");
	// list all the icon sets
	CDirFileEnum filefinder(m_sIconPath);
	bool isDir = false;
	CString item;
	while (filefinder.NextFile(item, &isDir))
	{
		if (!isDir)
			continue;
		m_cIconSet.AddString(CPathUtils::GetFileNameFromPath(item));
	}
	CheckRadioButton(IDC_LISTRADIO, IDC_SYMBOLRADIO, IDC_LISTRADIO);
	CString sModifiedIcon = m_regModified;
	if (sModifiedIcon.IsEmpty())
	{
		// no custom icon set, use the default
		sModifiedIcon = m_sIconPath + _T("\\XPStyle\\ModifiedIcon.ico");
	}
	if (sModifiedIcon.Left(m_sIconPath.GetLength()).CompareNoCase(m_sIconPath)!=0)
	{
		// an icon set outside our own installation? We don't support that,
		// so fall back to the default!
		sModifiedIcon = m_sIconPath + _T("\\XPStyle\\ModifiedIcon.ico");
	}
	// the name of the icon set is the folder of the icon location
	m_sOriginalIconSet = sModifiedIcon.Mid(m_sIconPath.GetLength()+1);
	m_sOriginalIconSet = m_sOriginalIconSet.Left(m_sOriginalIconSet.ReverseFind('\\'));
	// now we have the name of the icon set. Set the combobox to show
	// that as selected
	CString ComboItem;
	for (int i=0; i<m_cIconSet.GetCount(); ++i)
	{
		m_cIconSet.GetLBText(i, ComboItem);
		if (ComboItem.CompareNoCase(m_sOriginalIconSet)==0)
			m_cIconSet.SetCurSel(i);
	}

	WORD langID = (WORD)(DWORD)CRegStdDWORD(_T("Software\\TortoiseGit\\LanguageID"), GetUserDefaultLangID());
	TCHAR statustext[MAX_STATUS_STRING_LENGTH] = { 0 };
	GitStatus::GetStatusString(AfxGetResourceHandle(), git_wc_status_normal, statustext, _countof(statustext), langID);
	m_sNormal = statustext;
	GitStatus::GetStatusString(AfxGetResourceHandle(), git_wc_status_modified, statustext, _countof(statustext), langID);
	m_sModified = statustext;
	GitStatus::GetStatusString(AfxGetResourceHandle(), git_wc_status_conflicted, statustext, _countof(statustext), langID);
	m_sConflicted = statustext;
	GitStatus::GetStatusString(AfxGetResourceHandle(), git_wc_status_deleted, statustext, _countof(statustext), langID);
	m_sDeleted = statustext;
	GitStatus::GetStatusString(AfxGetResourceHandle(), git_wc_status_added, statustext, _countof(statustext), langID);
	m_sAdded = statustext;
	GitStatus::GetStatusString(AfxGetResourceHandle(), git_wc_status_ignored, statustext, _countof(statustext), langID);
	m_sIgnored = statustext;
	GitStatus::GetStatusString(AfxGetResourceHandle(), git_wc_status_unversioned, statustext, _countof(statustext), langID);
	m_sUnversioned = statustext;

	m_sReadOnly.LoadString(IDS_SETTINGS_READONLYNAME);
	m_sLocked.LoadString(IDS_SETTINGS_LOCKEDNAME);

	SetWindowTheme(m_hWnd, L"Explorer", NULL);

	ShowIconSet(true);

	return TRUE;
}