//将已经按照姓名汇总的数据分别输出到excel文件中
void CGhQuery::OnBnClickedClassifyExcel()
{
	// 添加文件保存目录

    CString str,strPath;
	
//    ZeroMemory(szPath, sizeof(szPath));   

    BROWSEINFO bi;   
    bi.hwndOwner = m_hWnd;   
    bi.pidlRoot = NULL;   
	bi.pszDisplayName = str.GetBuffer(MAX_PATH);   
    bi.lpszTitle = "请选择汇总信息存放目录：";   
    bi.ulFlags = 0;   
    bi.lpfn = NULL;   
    bi.lParam = 0;   
    bi.iImage = 0;   
    //弹出选择目录对话框
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);   
	str.ReleaseBuffer();

	SHGetPathFromIDList(lp,strPath.GetBuffer(MAX_PATH)) ;
    strPath.ReleaseBuffer();
    
	if(strPath.GetLength() <3){
		AfxMessageBox("选择的目录无效,请重新选择可读写的目录....");
		return;
	}


	UpdateData();

	CFormGhList *pf=(CFormGhList*)theApp.pParentGrid.pGrid;
	int iRows=pf->m_grid.GetRowCount();
	int iCols=pf->m_grid.GetColumnCount();
	if( iRows < 3) {
		AfxMessageBox("没有数据需要进行分类汇总输出,请先进行数据分类汇总....");
		return;
	}
	int iType=m_Type.GetCurSel();
	CString strJournalType;
	if( iType == CB_ERR || iType == 1 )strJournalType="报刊合计";
	else m_Type.GetLBText(iType,strJournalType);

	CString strPath2;
	strPath2.Format("(%s)%s-%s",strJournalType,m_strStart,m_strEnd);
	if( strPath.Right(1) == '\\' )  //路径选择为根目录时,目录后会自动附加'\\'字符,如果是正常的目录,则没有附加的'\\',所以要进行判断
		strPath=strPath+strPath2;
	else 
		strPath=strPath+"\\"+strPath2;

	//判断目录是否存在    
	WIN32_FIND_DATA fd;  
    HANDLE hFind = FindFirstFile(strPath, &fd);  
   // BOOL bFilter = (FALSE == dwFilter) ? TRUE : fd.dwFileAttributes & dwFilter;  
   // BOOL RetValue = ((hFind != INVALID_HANDLE_VALUE) && bFilter) ? TRUE : FALSE;  

    FindClose(hFind);  
	if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			AfxMessageBox("当前目前下已存在要导出的文件目录,如需导出,请重新选择目录...");
			return;
	}
	


	if( ! CreateDirectory(strPath,NULL) ){
		AfxMessageBox("Create directory is error !!");
		return;
	}
	strPath+="\\";
	const int COL_FACTORY=1,COL_NAME=2,COL_PRICE=3,COL_SQ=0;

	_Application app2;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;
	 COleVariant vOpt(DISP_E_PARAMNOTFOUND,VT_ERROR);
const int  IDC_PROGRESS_EXCEL=WM_USER+10003;
	CProgressEx pp;
	CRect r1(0,0,400,25);
	pp.Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,AfxGetMainWnd()->GetForegroundWindow(),IDC_PROGRESS_EXCEL);
	pp.UpdateWindow();
	pp.ShowWindow(SW_SHOW);
	pp.CenterWindow();
	pp.Invalidate();
	pp.SetRange32(0,iRows );
	pp.strView="正在准备导出...请稍等!!";

	app2.CreateDispatch("excel.application");
	if(!app2){
		AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
		return;
	}
	CString strFileName;
	strFileName.Format("%sspec.xls",LoginInformation.path);
	books2=app2.GetWorkbooks();


	Range vRange;
	SQ_EXCEL9::Font font;
	long x,y;
	CString str1,str2;
	
	app2.SetVisible(false);
//	pp.strView="";
	books2=app2.GetWorkbooks(); //OPEN excel template
	book2=books2.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	sheets2=book2.GetWorksheets();
	sheet2=sheets2.GetItem(COleVariant((short)1));


	CString szFlgFactory,szTmp;
	CString szOutFile,szCell;
	int xlsRow(3),clrRow(0);	//clrRow记录文件最后一行行号
	for(int i=1; i< iRows ;i++)
	{
		szFlgFactory=pf->m_grid.GetItemText(i,COL_FACTORY);

		if( xlsRow ==3 ){			
			szCell="a1";
			vRange=sheet2.GetRange(_variant_t(szCell),_variant_t(szCell) );
			vRange.SetValue(_variant_t(szFlgFactory));
			szOutFile.Format("%s%s(%s-%s).xls",strPath,szFlgFactory,m_strStart,m_strEnd);
			if(  clrRow ){
				szCell.Format("A3:%c%d",'A'+COL_PRICE,clrRow+1);
				vRange=sheet2.GetRange(_variant_t(szCell),_variant_t(szCell) );
				szCell="";
				vRange.SetValue(_variant_t(szCell));
				clrRow=0;
			}
		}

		if( i !=1 && xlsRow!= 3 ){
	
			szTmp=pf->m_grid.GetItemText(i-1,COL_FACTORY);
			if( szTmp.Compare(szFlgFactory) !=0 ){
	
				szCell.Format("%c%d",'A'+COL_PRICE,xlsRow);
				vRange=sheet2.GetRange(_variant_t(szCell),_variant_t(szCell) );
				szCell.Format("=sum(D3:D%d)",xlsRow-1);
				vRange.SetValue(_variant_t(szCell));
			
				book2.SaveAs(_variant_t(szOutFile),vOpt,vOpt,vOpt,vOpt,vOpt,0L,vOpt,vOpt,vOpt,vOpt);
			
				xlsRow=3;
				i--;
				continue;
			}

		}
		for(int iCol=0; iCol< iCols ; iCol++){	//输出到excel表格
			szCell.Format("%c%d",'A'+iCol,xlsRow);
			vRange=sheet2.GetRange(_variant_t(szCell),_variant_t(szCell) );
			if( iCol == 0 ) szCell.Format("%d",xlsRow-2);   //xlsRow 起始行为3，第一列为序号列，
			else 	
				szCell=pf->m_grid.GetItemText(i,iCol);
			vRange.SetValue(_variant_t(szCell));
		}
		xlsRow++;
		clrRow=xlsRow;
	
		pp.strView.Format("%2.0f%%",double(i)/iRows*100);
		pp.SetPos(i);

	}

	pp.SendMessage(WM_CLOSE);

	sheet2.ReleaseDispatch();

	sheets2.ReleaseDispatch();

	book2.SetSaved(true);	//设置已存储标志，在quit是不提示更改保存
	book2.Close(_variant_t(false ),vOpt,vOpt);

	books2.Close();
	book2.ReleaseDispatch();
	books2.ReleaseDispatch();
	app2.Quit();
	app2.ReleaseDispatch();	
	
}