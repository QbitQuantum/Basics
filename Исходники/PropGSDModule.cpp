//----------------------------- FUNCTION -------------------------------------*
void PropGSDModule::InitListCrtls()
{
    CRect   rect;
    CString sTitle;
	int iWidth;
	int iThird;
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_AVAILABLE_EXT_USER_PARAM);
	if (pList)	{
		pList->GetClientRect(&rect);
		iWidth = rect.Width();
		iThird = iWidth / 3;
		sTitle.LoadString(IDS_EXTUSERPARAM_DESCRIPTION);
		pList->InsertColumn(0, sTitle, LVCFMT_LEFT, iWidth, 0 );	// Create 1st Column
	//	sTitle.LoadString(IDS_MODULE_CONFIGBYTES);
	//	pListAvai->InsertColumn(1, sTitle, LVCFMT_LEFT, iThird, 0 );	// Create 2nd Column
	}

	pList = (CListCtrl*)GetDlgItem(IDC_LIST_USED_EXT_USER_PARAMS);
	if (pList)	{
		pList->GetClientRect(&rect);
		iWidth = rect.Width();
		iThird = iWidth/3;
		sTitle.LoadString(IDS_EXTUSERPARAM_DESCRIPTION);
		pList->InsertColumn(0, sTitle, LVCFMT_LEFT, iWidth, 0 );	// Create 1st Column
	//	sTitle.LoadString(IDS_MODULE_CONFIGBYTES);
	//	pListUsed->InsertColumn(1, sTitle, LVCFMT_LEFT, iThird, 0 );	// Create 2nd Column
	}

	pList = (CListCtrl*)GetDlgItem(IDC_LIST_AVAIL_MOD_EXTPRM);
	if (pList)	{
		pList->GetClientRect(&rect);
		iWidth = rect.Width();
		iThird = iWidth/3;
		sTitle.LoadString(IDS_EXTUSERPARAM_DESCRIPTION);
		pList->InsertColumn(0, sTitle, LVCFMT_LEFT, iWidth, 0 );	// Create 1st Column
	}

	pList = (CListCtrl*)GetDlgItem(IDC_LIST_USED_MOD_EXTPRM);
	if (pList)	{
		pList->GetClientRect(&rect);
		iWidth = rect.Width();
		iThird = iWidth/3;
		sTitle.LoadString(IDS_EXTUSERPARAM_DESCRIPTION);
		pList->InsertColumn(0, sTitle, LVCFMT_LEFT, iWidth, 0 );	// Create 1st Column
	}
}