bool CDialogStatus::InitStatusList()
{
	CListCtrl *pStatusList = (CListCtrl*)GetDlgItem(IDC_LIST_STATUS);
	if (NULL != pStatusList)
	{
		RECT ret = {0};
		GetClientRect(&ret);
		pStatusList->MoveWindow(&ret);

		pStatusList->ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS);
		pStatusList->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

		for (int nIndex(0); sizeof(StatusListHeade)/sizeof(StatusListHeade[0]) > nIndex; ++nIndex)
		{
			pStatusList->InsertColumn(nIndex, StatusListHeade[nIndex].pString, LVCFMT_LEFT, StatusListHeade[nIndex].nWidth);
		}
	}

	return true;
}