BOOL CFavUrlMenuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetFont(&m_font);
	if (m_bAddFav)
	{
		ITEM item;
		item.type = ITEM_TYPE_BTN_ADD;
		item.strName = "添加到收藏夹";
		item.strPath = m_strParentPath;
		m_arrItems.Add(item);
		item.type = ITEM_TYPE_SEPARATOR;
		m_arrItems.Add(item);
		GetUrls(m_strParentPath, m_arrItems);
	}else 
	{
		ITEM item;
		item.type = ITEM_TYPE_BTN_OPEN;
		item.strName = "打开";
		item.strPath = m_strParentPath;
		m_arrItems.Add(item);

		item.type = ITEM_TYPE_BTN_REMOE;
		item.strName = "删除";
		item.strPath = m_strParentPath;
		m_arrItems.Add(item);
	}
	// 获取最长字符串所占宽度
	CClientDC dc(this);
	int nTextWidthMax = 0;
	CSize size;
	dc.SelectObject(&m_font);
	for (INT_PTR i=0; i<m_arrItems.GetSize(); i++)
	{
		CString strText = m_arrItems.GetAt(i).strName;
		size = dc.GetTextExtent(strText);
		if (size.cx > nTextWidthMax)
			nTextWidthMax = size.cx;
	}
	nTextWidthMax = nTextWidthMax < 90 ? nTextWidthMax+100: nTextWidthMax+30;
	size.cx = nTextWidthMax;

	m_rctFirsItem = CRect(CPoint(m_nBorderWidth, m_nBorderWidth), CSize(size.cx+m_nSpacingHeigth*2, size.cy+m_nSpacingHeigth));
	m_rctFirsItem.top += 6;
	m_rctFirsItem.bottom +=10;

	CRect rctWnd(0, 0, 0, 0);
	rctWnd.right = m_nBorderWidth*2 + m_rctFirsItem.Width();
	rctWnd.bottom= m_nBorderWidth*2 + m_rctFirsItem.Height()*m_arrItems.GetSize() ;
	if (m_nBorderWidth % 2)
	{
		rctWnd.right += 2;
		rctWnd.bottom += 2;
	}
 	dc.BeginPath();
 	dc.RoundRect(rctWnd, CPoint(m_nBorderWidth, m_nBorderWidth));
 	dc.EndPath();
  	HRGN hRgn = PathToRegion(dc.m_hDC);
 	SetWindowRgn(hRgn, FALSE);
	GetRgnBox(hRgn, &rctWnd);
	SetWindowPos(NULL, 0, 0, rctWnd.Width(), rctWnd.Height(), SWP_NOMOVE);
 	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}