//位置消息
VOID CControlWnd::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//移动控件
	HDWP hDwp=BeginDeferWindowPos(32);
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOSIZE;

	//调整控件
	DeferWindowPos(hDwp,m_btMaxScore,NULL,cx-28,4,0,0,uFlags);
	DeferWindowPos(hDwp,m_btLessScore,NULL,cx-28,26,0,0,uFlags);

	//结束移动
	EndDeferWindowPos(hDwp);

	return;
}