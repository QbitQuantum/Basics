void CZogvmDlg::DisplayerList()
{
	m_list.DeleteAllItems();
	WinfileviewList.clear();

	if(0==ListTotal)
	{
		GetDlgItem(IDC_STATIC_INFO)->SetWindowText("共0条 1/1页");
		InvalidateRect(printf_Rect, TRUE);
		return ;
	}

	unsigned long int si,ei;

	si=ListNow+1;
	if((ListNow+PAGE_MAX_NUM) < ListTotal)
		ei=ListNow+PAGE_MAX_NUM ;
	else
		ei=ListTotal;

	switch(ModeFlag)
	{
	case MODE_DOUBLE:
		SQLDB.File_ReadDouble(WinfileviewList,si-1,ei-(si-1));
		break;
	case MODE_FIND:
		if(m_sreach.IsEmpty())
			SQLDB.File_Read(SQLstr,WinfileviewList,si-1,ei-(si-1));
		else
			SQLDB.File_ReadForSearch(SQLstr,m_sreach.GetBuffer(0),WinfileviewList,si-1,ei-(si-1));
		break;
	case MODE_TRASH:
		SQLDB.File_ReadTrash(WinfileviewList,si-1,ei-(si-1));
		break;
	default:return ;

	}

	if(WinfileviewList.size()<=0)
		return ;

	list<struct FILE_VIEW_ST>::iterator beglist;
	char str[128];
	int i=0;
	SYSTEMTIME   systime;
	FILETIME  temptime;
	ULARGE_INTEGER  uli; 

	for(beglist=WinfileviewList.begin();beglist!=WinfileviewList.end();beglist++)
	{
		//带复选框 LVS_EX_CHECKBOXES
		if(MAINTYPE_OTHER == beglist->file_data.maintype )
		{
			m_list.InsertItem( i,beglist->hdd_data.serno,5);
		}
		else if( MAINTYPE_SUB == beglist->file_data.maintype)
		{
			m_list.InsertItem( i,beglist->hdd_data.serno,4);
		}
		else  if(MAINTYPE_VIDEO == beglist->file_data.maintype )
		{
			m_list.InsertItem( i,beglist->hdd_data.serno,2);
		}
		else  if(MAINTYPE_MUSIC == beglist->file_data.maintype )
		{
			m_list.InsertItem( i,beglist->hdd_data.serno,3);
		}
		m_list.SetItemText(i,1,beglist->hdd_data.mark);
		m_list.SetItemText(i,2,beglist->hdd_data.area);

		sprintf(str,"%I64u",beglist->file_data.file_nid);
		m_list.SetItemText(i,3,str);
		m_list.SetItemText(i,4,beglist->file_data.path);
		m_list.SetItemText(i,5,beglist->file_data.name);

		m_list.SetItemText(i,6,	MainType2Str(beglist->file_data.maintype));

		m_list.SetItemText(i,7,beglist->file_data.type);

		if(beglist->file_data.CreationTime)
		{
			uli.QuadPart=beglist->file_data.CreationTime;
			temptime.dwLowDateTime=uli.LowPart;
			temptime.dwHighDateTime=uli.HighPart;
			FileTimeToSystemTime(&temptime,&systime);

			sprintf(str,"%04d-%02d-%02d %02d:%02d:%02d", 
				systime.wYear,systime.wMonth,systime.wDay,
				systime.wHour,systime.wMinute,systime.wSecond);

			m_list.SetItemText(i,8,str);
		}

		if(beglist->file_data.LastWriteTime)
		{
			uli.QuadPart=beglist->file_data.LastWriteTime;
			temptime.dwLowDateTime=uli.LowPart;
			temptime.dwHighDateTime=uli.HighPart;
			FileTimeToSystemTime(&temptime,&systime);

			sprintf(str,"%04d-%02d-%02d %02d:%02d:%02d", 
				systime.wYear,systime.wMonth,systime.wDay,
				systime.wHour,systime.wMinute,systime.wSecond);
			m_list.SetItemText(i,9,str);
		}

		//sprintf(str,"%I64u",);
		DisplaySize(beglist->file_data.filesize,str);
		m_list.SetItemText(i,10,str);

		if(beglist->file_data.resolutionW && beglist->file_data.resolutionH)
		{
			sprintf(str,"%d*%d",beglist->file_data.resolutionW,beglist->file_data.resolutionH);
			m_list.SetItemText(i,11,str);
		}
		else
			m_list.SetItemText(i,11,"");

		if(beglist->file_data.filetime)
		{
			sprintf(str,"%d:%02d:%02d", 
				beglist->file_data.filetime / 3600,
				(beglist->file_data.filetime  % 3600) / 60,
				beglist->file_data.filetime % 60);
			m_list.SetItemText(i,12,str);
		}
		else
			m_list.SetItemText(i,12,"");

		if(beglist->hdd_data.insertflag)
		{
			m_list.SetItemText(i,13,"接入");
			m_list.SetItem(i, 13, LVIF_IMAGE, NULL, 0, 0, 0, 0);
		}
		else
		{
			m_list.SetItemText(i,13,"脱机");
			m_list.SetItem(i, 13, LVIF_IMAGE, NULL, 1, 0, 0, 0);
		}

		/*
		//名称
		LV_ITEM lvitem;
		memset ((char *) &lvitem, 0, sizeof (LV_ITEM));
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE  | LVIF_STATE;
		lvitem.iItem = i;
		lvitem.iSubItem = 12;
		lvitem.stateMask = 0;
		lvitem.iImage =1;          //显示不同的图标时，可以把一个int 变量赋给这个属性值
		lvitem.pszText = "a";
		m_list.SetItem (&lvitem);

		m_list.SetItem(i, 12, LVIF_IMAGE, NULL, 0, 0, 0, 0);
*/

		m_list.SetItemText(i,14,beglist->file_data.zidian_3d);
		m_list.SetItemText(i,15,beglist->file_data.zidian_huazhi);
		m_list.SetItemText(i,16,beglist->file_data.zidian_fenbianlv);
		m_list.SetItemText(i,17,beglist->file_data.zidian_yazhi);
		m_list.SetItemText(i,18,beglist->file_data.zidian_year);

		m_list.SetItemText(i,19,beglist->file_data.md5);
		if(MODE_DOUBLE == ModeFlag)
		{
			sprintf(str,"%I64u",beglist->file_data.double_nid);
			m_list.SetItemText(i,20,str);
		}
		else
			m_list.SetItemText(i,20,"0");

		i++;
	}

	if(ListTotal%PAGE_MAX_NUM)
	{
		sprintf(str,"共%d条 %d/%d页 每页%d条",
			ListTotal,
			ListNow/PAGE_MAX_NUM+1,ListTotal/PAGE_MAX_NUM+1,PAGE_MAX_NUM);
	}
	else
	{
		sprintf(str,"共%d条 %d/%d页 每页%d条",
			ListTotal,
			ListNow/PAGE_MAX_NUM+1,ListTotal/PAGE_MAX_NUM,PAGE_MAX_NUM);
	}
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText(str);
	InvalidateRect(printf_Rect, TRUE);

	m_c_delete_trash=FALSE;
	UpdateData(FALSE);
}