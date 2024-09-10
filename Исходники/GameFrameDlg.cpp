//调整界面
void CGameFrameDlg::RectifyControl(int nWidth, int nHeight)
{
	//状态判断
	if (m_bInitDialog==false) return;

	//变量定义
	CRect rcVorSplitter;
	const int nSplitterWidth=6;
	const int iXExc=GetXExcursionPos();
	const int iYExc=GetYExcursionPos();
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;

	//获取位置
	m_VorSplitter.GetWindowRect(&rcVorSplitter);
	ScreenToClient(&rcVorSplitter);

	//调整拆分条
	if (m_bRectify==false)
	{
		//设置变量
		m_bRectify=true;

		//设置位置
		if (m_bHideList==false)
		{
			rcVorSplitter.left=nWidth*75/100;
			rcVorSplitter.right=rcVorSplitter.left+nSplitterWidth;
		}
		else
		{
			rcVorSplitter.right=nWidth;
			rcVorSplitter.left=nWidth-nSplitterWidth;
		}
	}

	//设置拆分范围
	if (m_bHideList==false)
	{
		int nLessPos=nWidth*3/5,nMaxPos=nWidth*75/100;
		m_VorSplitter.SetSplitterRange(nLessPos,nMaxPos);
		if ((nWidth!=0)&&(nHeight!=0))
		{
			if (rcVorSplitter.left<nLessPos) 
			{
				rcVorSplitter.left=nLessPos;
				rcVorSplitter.right=rcVorSplitter.left+nSplitterWidth;
			}
			if (rcVorSplitter.right>nMaxPos)
			{
				rcVorSplitter.right=nMaxPos;
				rcVorSplitter.left=rcVorSplitter.right-nSplitterWidth;
			}
		}
	}

	if (m_VorSplitter.GetSplitterType()==HorSpliter) rcVorSplitter.SetRect(nWidth,0,nWidth,nHeight);

	//锁定屏幕
	LockWindowUpdate();

	//移动控件
	HDWP hDwp=BeginDeferWindowPos(32);
	DeferWindowPos(hDwp,m_pGameFrameView->GetSafeHwnd(),NULL,iXExc,iYExc,rcVorSplitter.left-iXExc,nHeight-iYExc,uFlags);
	DeferWindowPos(hDwp,m_VorSplitter,NULL,rcVorSplitter.left,iYExc,rcVorSplitter.Width(),nHeight-iYExc,uFlags);
	DeferWindowPos(hDwp,m_pGameFrameControl->GetSafeHwnd(),NULL,rcVorSplitter.right,iYExc,nWidth-rcVorSplitter.right,nHeight-iYExc,uFlags);
	EndDeferWindowPos(hDwp);

	//重画界面
	Invalidate(FALSE);
	UpdateWindow();

	//解除锁定
	UnlockWindowUpdate();

	//控制按钮
	CRect rcControl;
	m_btControl.GetClientRect(&rcControl);
	m_btControl.SetWindowPos(NULL,rcVorSplitter.left+(rcVorSplitter.Width()-rcControl.Width())/2,(nHeight-rcControl.Height())/2,0,0,uFlags|SWP_NOSIZE);

	//设置变量
	m_bRectify=false;

	return;
}