void ApplyGraphicLabelsDlg::ClickAddbuildingMsflexgrid()
{
	
	long lRow,lCol;
	lRow = m_FlexGrid.get_RowSel();//获取点击的行号	
	lCol = m_FlexGrid.get_ColSel(); //获取点击的列号

	m_nCurRow=lRow;
	m_nCurCol=lCol;
	/*
	m_strBuilding_Name2=m_AddBuiding_FlexGrid.get_TextMatrix(lRow,AB_NAME);
	m_strBuildingName=m_AddBuiding_FlexGrid.get_TextMatrix(lRow,AB_NAME);
	m_strConnetion=m_AddBuiding_FlexGrid.get_TextMatrix(lRow,AB_CONNECTION);
	m_strProtocol=m_AddBuiding_FlexGrid.get_TextMatrix(lRow,AB_PROTOCOL);
	m_strIpAddress=m_AddBuiding_FlexGrid.get_TextMatrix(lRow,AB_IPADDRESS);
	m_strIpPort=m_AddBuiding_FlexGrid.get_TextMatrix(lRow,AB_IPPORT);
	m_strComPort=m_AddBuiding_FlexGrid.get_TextMatrix(lRow,AB_COMPORT);
	m_strBaudrat=m_AddBuiding_FlexGrid.get_TextMatrix(lRow,AB_BAUDRAT);
	*/



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

	if(0==lRow)
		return;

	if(0==lCol)
	{
		//ID_BUILDINGSEL_SELECT
		CMenu menu;
		menu.LoadMenu(IDR_APPLYGRAPHICLABELS);
		CMenu *pmenu=menu.GetSubMenu(0);
		CPoint point;
		GetCursorPos(&point);
		pmenu->TrackPopupMenu(TPM_LEFTBUTTON | TPM_LEFTALIGN ,point.x,point.y,this);	

	}
}