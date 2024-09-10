void OpenFileDlg::LoadWfdiscRecords(LPSTR lpFileName)
	{
	int nRecord=0;
	CListCtrl	m_list;
	char cChan[32],cSpS[32],cSta[32],cTimeBeg[32],cTimeEnd[32];
	LV_ITEM lvi;
	static char line[WFDISC_SIZE+2];
	static wfdisc wfd;
	struct wfdisc *pwfdisc;
	pwfdisc=&wfd;

	m_list.Attach(GetDlgItem(IDC_LIST)->m_hWnd);

	m_list.DeleteAllItems();


	int result;
	struct _stat buffer;
	result = _stat(lpFileName, &buffer);
	if( result == 0 )
		{
		int file_type=_S_IFREG;
		int dir_type=_S_IFDIR ;
		
		if( (buffer.st_mode & _S_IFMT) == _S_IFMT)
			{
			m_list.Detach();
			return;
			}
		}
	else
		{
		m_list.Detach();
		return;
		}




	FILE *fp=fopen(lpFileName,"rt");

	if(fp==NULL)
		{
		m_list.Detach();
		return;
		}

	_fpreset();
	while(1)
		{
		if (fgets(line, WFDISC_SIZE+1, fp) == NULL) break;
		if (lstrlen(line) == WFDISC_SIZE) 
			{
//        sscanf(line, WFDISC_SCS, WFDISC_RVL(pwfdisc));

			ScanWfdLine(pwfdisc, line);
            WFDISC_TRM(pwfdisc);

			lstrcpy(cSta,	pwfdisc->sta);
			lstrcpy(cChan,	pwfdisc->chan);
			sprintf(cSpS,"%.3f", pwfdisc->smprate);
			sprintf(cTimeBeg,"%s",dttostr(pwfdisc->time, 1));
			sprintf(cTimeEnd,"%s",dttostr(pwfdisc->endtime, 1));


			memset(&lvi,0,sizeof(lvi));
			lvi.iItem=nRecord;
			lvi.iSubItem=0;
			lvi.mask=LVIF_TEXT;
			lvi.iImage=0;
			lvi.cchTextMax=sizeof(cSta);
			lvi.pszText=cSta;

			m_list.InsertItem(&lvi);
			m_list.SetItemText(nRecord,1,cChan);
			m_list.SetItemText(nRecord,2,cSpS);
			m_list.SetItemText(nRecord,3,cTimeBeg);
			m_list.SetItemText(nRecord,4,cTimeEnd);
			++nRecord;
			}
		}
	fclose(fp);
	m_list.Detach();
	}