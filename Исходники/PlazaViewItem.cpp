//位置消息
void CPlazaViewItem::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	//状态判断
	if (m_bInitDialog==false) return;
	if ((cx==0)||(cy==0)) return;

	//变量定义
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;

	//移动控件
	HDWP hDwp=BeginDeferWindowPos(32);
	DeferWindowPos(hDwp,m_pHtmlBrower->GetSafeHwnd(),NULL,m_ImageInfoWeb.nLBorder,m_ImageInfoWeb.nTBorder,
		cx-m_ImageInfoWeb.nLBorder-m_ImageInfoWeb.nRBorder,cy-m_ImageInfoWeb.nTBorder-m_ImageInfoWeb.nBBorder,uFlags);

	//导航按钮
	CRect rcButton;
	m_WEB_BEFORE.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp,m_WEB_BEFORE,NULL,10,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_WEB_NEXT,NULL,10+rcButton.Width(),3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_WEB_BRUSH,NULL,10+rcButton.Width()*2,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_WEB_STOP,NULL,10+rcButton.Width()*3,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_WEB_HOME,NULL,10+rcButton.Width()*4,3,0,0,uFlags|SWP_NOSIZE);

	EndDeferWindowPos(hDwp);

	return;
}