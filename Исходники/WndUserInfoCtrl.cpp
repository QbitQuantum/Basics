//调整控件
VOID CWndUserInfoCtrl::RectifyControl(INT nWidth, INT nHeight)
{
	//设置区域
	m_rcUnderWrite.SetRect(127,52,nWidth-13,72);

	//变量定义
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER|SWP_NOSIZE;

	//按钮大小
	CRect rcButton;
	m_btUserInfo1.GetWindowRect(&rcButton);

	//间隔定义
	UINT nSpace=14;
	UINT nStartPos=18;

	//调整按钮
	DeferWindowPos(hDwp,m_btUserInfoSet,NULL,69,15,0,0,uFlags);
	DeferWindowPos(hDwp,m_btUserInfo1,NULL,nStartPos,nHeight-rcButton.Height()-9,0,0,uFlags);
	DeferWindowPos(hDwp,m_btUserInfo2,NULL,nStartPos+rcButton.Width()+nSpace,nHeight-rcButton.Height()-9,0,0,uFlags);
	DeferWindowPos(hDwp,m_btUserInfo3,NULL,nStartPos+(rcButton.Width()+nSpace)*2,nHeight-rcButton.Height()-9,0,0,uFlags);

	//结束调整
	EndDeferWindowPos(hDwp);

	return;
}