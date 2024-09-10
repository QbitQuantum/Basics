CRect CScanDlg::CalcGridCellRect(int iRow, int iCol )
{
	CRect rect;
	m_flexGrid.GetWindowRect(rect); //获取表格控件的窗口矩形
	ScreenToClient(rect); //转换为客户区矩形	
	CDC* pDC = GetDC();

	int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
	int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;
	//计算选中格的左上角的坐标(象素为单位)
	long y = m_flexGrid.get_RowPos(iRow)/nTwipsPerDotY;
	long x = m_flexGrid.get_ColPos(iCol)/nTwipsPerDotX;
	//计算选中格的尺寸(象素为单位)。加1是实际调试中，发现加1后效果更好
	long width = m_flexGrid.get_ColWidth(iCol)/nTwipsPerDotX+1;
	long height = m_flexGrid.get_RowHeight(iRow)/nTwipsPerDotY+1;
	//形成选中个所在的矩形区域
	CRect rcCell(x,y,x+width,y+height);
	//转换成相对对话框的坐标
	rcCell.OffsetRect(rect.left+2,rect.top+2);	
	rcCell.InflateRect(-1,-1,-1,-1);
	//CString strValue = m_flexGrid.get_TextMatrix(iRow,iCol);

	//pDC->Draw3dRect(rcCell, RGB(255,0,0), RGB(192,192,192));
	//pDC->DrawText(_T("Fix"), &rcCell, DT_CENTER);

	return rcCell;
	ReleaseDC(pDC);

}