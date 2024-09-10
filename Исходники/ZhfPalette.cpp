void CZhfPalette::OnSize(UINT nType, int cx, int cy)
{
	CAdUiPalette::OnSize(nType, cx, cy);
	// TODO: 在此添加消息处理程序代码
	if (cx<m_iCtrlWidth+m_iMarginX||cy<m_iCtrlHeight+m_iMarginY)
	{
		return ;
	}
	int iCtrlNum = m_pArrayPreviewCtrl.GetCount() ;
	int iCol = cx/(m_iCtrlWidth+m_iMarginX) ;
	int iRow = iCtrlNum/iCol + (iCtrlNum%iCol==0?0:1);

	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	si.nMax = iRow-1 ;
	si.nPage = cy/(m_iCtrlHeight+m_iMarginY) ;
	SetScrollInfo(SB_VERT,&si,TRUE);
	ScrollWindow(0,0);

	m_iOldPosY = 0;

	Invalidate(TRUE);

	if (m_pArrayPreviewCtrl.GetCount()>0&&cx>(m_iCtrlWidth+m_iMarginX))
	{
		TRACE(_T("\ncx:%d, cy:%d"),cx, cy) ;
		ResizeCtrl(cx, cy) ;
	}
}