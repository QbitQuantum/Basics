void CSelectFilesOnCDDlg::SetListHeader()
	{
	LV_COLUMN lvc;
	int i;
	char *colums[] = {"File","Size"};
	RECT rc;
	CListCtrl	*pList;

	pList = (CListCtrl	*)(GetDlgItem(IDC_LIST));

	pList->GetClientRect(&rc);


	memset(&lvc,0,sizeof(lvc));
	lvc.mask=LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
	lvc.fmt=LVCFMT_LEFT;
	lvc.cx=rc.right/2;
	lvc.cchTextMax=128;
	for(i=0;i<sizeof(colums)/sizeof(char *);++i)
		{
		lvc.iSubItem=i;
		lvc.pszText=colums[i];
		pList->InsertColumn(i,&lvc);
		}
			
	}	