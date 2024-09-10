void CUserAcessSetDlg::ClickAddbuildingMsflexgrid()
{
	long lRow,lCol;
	lRow = m_FlexGrid.get_RowSel();//获取点击的行号	
	lCol = m_FlexGrid.get_ColSel(); //获取点击的列号

	m_nCurRow=lRow;
	m_nCurCol=lCol;

	m_FlexGrid.put_Row(m_nCurRow);m_FlexGrid.put_Col(m_nCurCol);
	if(RGB(215,215,215)==m_FlexGrid.get_CellBackColor())
		return;

	CRect rect;
	m_FlexGrid.GetWindowRect(rect); //获取表格控件的窗口矩形
	ScreenToClient(rect); //转换为客户区矩形	
	CDC* pDC =GetDC();

	int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
	int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;
	//计算选中格的左上角的坐标(象素为单位)
	long y = m_FlexGrid.get_RowPos(lRow)/nTwipsPerDotY;
	long x = m_FlexGrid.get_ColPos(lCol)/nTwipsPerDotX;
	//计算选中格的尺寸(象素为单位)。加1是实际调试中，发现加1后效果更好
	long width = m_FlexGrid.get_ColWidth(lCol)/nTwipsPerDotX+1;
	long height = m_FlexGrid.get_RowHeight(lRow)/nTwipsPerDotY+1;
	//形成选中个所在的矩形区域
	CRect rcCell(x,y,x+width,y+height);
	//转换成相对对话框的坐标
	rcCell.OffsetRect(rect.left+1,rect.top+1);
	ReleaseDC(pDC);
	CString strValue = m_FlexGrid.get_TextMatrix(lRow,lCol);
	if(lCol==6||lCol==7||lCol==8)
	{
		
		m_userLeveSetBox.ResetContent();
		m_userLeveSetBox.AddString(_T("Read & write"));
		m_userLeveSetBox.AddString(_T("Read only"));
		m_userLeveSetBox.MoveWindow(&rcCell,1);
		m_userLeveSetBox.ShowWindow(SW_SHOW);
		m_userLeveSetBox.BringWindowToTop();
		m_userLeveSetBox.SetFocus();
	}
	if(lCol==9||lCol==11||lCol==12||lCol==10)
	{	
		m_userLeveSetBox.ResetContent();
		m_userLeveSetBox.AddString(_T("Enable"));
		m_userLeveSetBox.AddString(_T("Unenable"));
		m_userLeveSetBox.MoveWindow(&rcCell,1);
		m_userLeveSetBox.ShowWindow(SW_SHOW);
		m_userLeveSetBox.BringWindowToTop();
		m_userLeveSetBox.SetFocus();
	}
}