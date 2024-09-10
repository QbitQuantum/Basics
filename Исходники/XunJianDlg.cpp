void CXunJianDlg::OnOK() 
{
	try{
	pList= (CListBox *)GetDlgItem(IDC_HOSTLIST);
	/*if( pList->GetTextLen(0)>15 || pList->GetTextLen(0)<7 )
	{
		MessageBox("主机列表文件未加载，请重新选择！");
		return;
	}*/

	_GUID clsid;
	IUnknown *pUnk;
	IDispatch *pDisp;
	LPDISPATCH lpDisp;

	_Application app;
	Workbooks xj_books;
	_Workbook xj_book;
	Worksheets xj_sheets;
	_Worksheet xj_sheet;
	Range range;
	Range unionRange;
	Range cols;

	Font font;
//	COleVariant background;

	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	::CLSIDFromProgID(L"Excel.Application",&clsid); // from registry
	if(GetActiveObject(clsid, NULL,&pUnk) == S_OK)
	{
		VERIFY(pUnk->QueryInterface(IID_IDispatch,(void**) &pDisp) == S_OK);
		app.AttachDispatch(pDisp);
		pUnk->Release();
	} 
	else
	{  
		if(!app.CreateDispatch("Excel.Application"))
		{
			MessageBox("Excel program not found");     
			app.Quit();     
			return;
		}
	}

	xj_books=app.GetWorkbooks();
	xj_book=   xj_books.Add(covOptional);
	xj_sheets= xj_book.GetSheets();
	xj_sheet=  xj_sheets.GetItem(COleVariant((short)1));

	int i;
	Range item;
	range=xj_sheet.GetRange(COleVariant("A1"),COleVariant("F1"));
	for(i= 0; i < 6; i++)
	{
		item.AttachDispatch(range.GetItem(COleVariant((long)1),COleVariant((long)i+1)).pdispVal);
		item.SetValue2(COleVariant(PROJ[i]));
	}  //描绘第一行目录

	//range=xj_sheet.GetRange(COleVariant("A1"),COleVariant("F1"));
	lpDisp=range.GetInterior();
	Interior   cellinterior;
	cellinterior.AttachDispatch(lpDisp);
	cellinterior.SetColor(COleVariant((long)0xc0c0c0));  //设置背景色为灰色
	cellinterior.ReleaseDispatch();
	//range=xj_sheet.GetRange(COleVariant("A1"),COleVariant("F1"));
	range.SetHorizontalAlignment(COleVariant((long)-4108)); //全部居中
	Borders bord;
	bord=range.GetBorders();
	bord.SetLineStyle(COleVariant((short)1));  //设置边框
	//range=xj_sheet.GetRange(COleVariant("A1"),COleVariant("F1"));
	cols=range.GetEntireColumn();
	cols.AutoFit();  //自动调整

/**************************表格初始绘画完成************************************/

	long usedRowNum; //行计数
	CString handleFile;
	CString hostFileName,hostip;
	bool error = false;
	CString infos,info;
	ExcelFile excelFile;
	ReadTxt xj_txt;
	xj_HostCount=pList->GetCount();
	for(int n_host=0;n_host<xj_HostCount;n_host++)  //主循环，一个文件一次循环。
	{		
		pList->GetText(n_host,hostFileName);
		hostip = hostFileName;
		handleFile = hostFileName + _T(" 正在处理...");
		pList->DeleteString(n_host);
		pList->InsertString(n_host,handleFile);
		pList->SetCurSel(n_host);
		pList->UpdateWindow();

		hostFileName = xj_FilePath + hostFileName;
		hostFileName += _T(".txt");
		CStdioFile hostFile;
		if(!hostFile.Open(hostFileName,CFile::modeRead,0))
		{  //记录不存在文件名
			handleFile.Replace("正在处理...","失败！");
			error = true;
			pList->DeleteString(n_host);
			pList->InsertString(n_host,handleFile);
			pList->UpdateWindow();
			continue;
		}
		usedRowNum = excelFile.GetRowCount(xj_sheet);
		range.AttachDispatch(xj_sheet.GetCells());

		//info.Format( _T("%d"), n_host+1);
		info = xj_txt.ReadHostName(&hostFile,COMMAND[0],COMMAND[1]);  //获取节点名称
		range.SetItem(COleVariant(usedRowNum+1),COleVariant(long(1)),COleVariant(info));

		int portCount = 0;   //端口数目，不包括7/1
		CString nSend, nRecv;
		float n_Send,n_Recv;

		while(hostFile.ReadString(info))
			if(info.Find( COMMAND[4]) > -1) break;
		while( hostFile.ReadString(info) && info.Find( "[local]" ) == -1 )  //端口号和流量
		{
			if( info.Find( "/" ) == -1 || info.Find( "7/1" ) > -1 ) continue;

			info.Replace( "ethernet","");
			info = _T("'") + info;
			infos = info;

			while( hostFile.ReadString(info) )
				if( info.Find( "send bit rate" ) > -1 ) break;
			nSend = info.Mid( 60 );
			hostFile.ReadString(info);
			nRecv = info.Mid( 60 );
			nSend.Trim();
			nRecv.Trim();
			n_Send = (float)atof(nSend);
			n_Recv = (float)atof(nRecv);

			if( n_Send < 1000 && n_Recv < 1000 ) continue;
			portCount++;
			range.SetItem(COleVariant(usedRowNum+portCount),COleVariant(long(2)),COleVariant(infos.Trim()));
			range.SetItem(COleVariant(usedRowNum+portCount),COleVariant(long(4)),COleVariant((n_Send>n_Recv)?nSend:nRecv));
		}

		hostFile.SeekToBegin();
		infos = xj_txt.ReadLine(&hostFile,"ubscriber Address");  //历史在线最大用户数
		if( infos == _T("") ) info = _T("0");
		else
		{
			int token = 0;
			for(i = 0; i < 5 ; i++) info = infos.Tokenize(" ",token);
		}
		range.SetItem(COleVariant(usedRowNum+1),COleVariant(long(6)),COleVariant(info.Trim()));  

		hostFile.Close();

		if(portCount > 1)
		{
			unionRange.AttachDispatch(range.GetItem(COleVariant(usedRowNum+1),COleVariant((long)1)).pdispVal);
			unionRange.AttachDispatch(unionRange.GetResize(COleVariant((long)portCount),COleVariant((long)1)));
			unionRange.Merge(COleVariant((long)0));  //节点名称单元格合并

			unionRange.AttachDispatch(range.GetItem(COleVariant(usedRowNum+1),COleVariant((long)6)).pdispVal);
			unionRange.AttachDispatch(unionRange.GetResize(COleVariant((long)portCount),COleVariant((long)1)));
			unionRange.Merge(COleVariant((long)0)); 			
			//历史最大用户数合并
		}

		unionRange.AttachDispatch(range.GetItem(COleVariant(usedRowNum+1),COleVariant((long)1)).pdispVal);
		unionRange.AttachDispatch(unionRange.GetResize(COleVariant((long)portCount),COleVariant((long)6)));
		unionRange.SetRowHeight(COleVariant(13.5));
		bord = unionRange.GetBorders();
		bord.SetLineStyle(COleVariant((short)1));  //设置边框



		handleFile.Replace("正在处理...","已完成");
		pList->DeleteString(n_host);
		pList->InsertString(n_host,handleFile);
		pList->UpdateWindow();
	}

	CTime time;
	time = time.GetCurrentTime();
	infos = time.Format("%Y%m%d%H%M%S");  //time.Format();
	info = _T("巡检报表") + infos + _T(".xlsx");
	info = xj_FilePath + info;
	info.Replace("\\\\","\\");

	xj_book.SaveAs(COleVariant(info),covOptional,covOptional,covOptional,covOptional,covOptional,0,covOptional,covOptional,covOptional,covOptional,covOptional);
	
	if(error == true )
	{
		MessageBox("巡检报表已完成，已保存到\r\n" + info + "\r\n有文件打开错误，点击\"确定\"返回查看","有文件打开错误！",MB_OK|MB_ICONWARNING);
		app.Quit();
	}
	else 
	{
		if(MessageBox("巡检报表已完成，已保存到\r\n" + info + "\r\n点击\"确定\"打开文件查看","生成报表完成",MB_OKCANCEL) == IDOK)
		{
			app.SetVisible(TRUE);
			app.SetUserControl(TRUE);
		}
		else app.Quit();
	}
}
catch (CFileException* e)
    {
        e->ReportError();
        e->Delete();
    }
	//CDialog::OnOK();
}