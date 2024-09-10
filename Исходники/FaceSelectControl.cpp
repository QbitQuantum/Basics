//滚动消息
BOOL CFaceItemSelectWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint Point)
{
	__super::OnMouseWheel(nFlags,zDelta,Point);

	//设置变量
	INT nLastPos=m_nCurrentPos;
	m_nCurrentPos=__max(0,__min(m_nCurrentPos-zDelta/WHELL_PELS,m_nMaxPels-m_nPagePels));

	//设置滚动
	SetScrollPos(SB_VERT,m_nCurrentPos);
	ScrollWindow(0,nLastPos-m_nCurrentPos,NULL,NULL);

	return TRUE;
}