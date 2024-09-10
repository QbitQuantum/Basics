/************************************************************************
PositionScrollBars  ListCtrl 기본 스크롤바를 숨기고 비트맵 스크롤 바로 변경한다.
@PARAM  : 
@RETURN : 
@REMARK : 
    http://www.codeguru.com/forum/showthread.php?s=36a2689f1a0c1395ba30950f993c559b&threadid=178221&highlight=hide+scrollbars
@AUTHOR : youngchang ([email protected])
@HISTORY :
    2006/01/02:CREATED
************************************************************************/
void CFishListCtrl::PositionScrollBars()
{
    enum { SCROLLBAR_WIDTH=12, SCROLLBAR_HEIGHT=12};

	CWnd* pParent = GetParent();
	
	CRect windowRT;
	GetWindowRect(&windowRT);

	int nTitleBarHeight = 0;
	
	if(pParent->GetStyle() & WS_CAPTION)
		nTitleBarHeight = GetSystemMetrics(SM_CYSIZE);

    // WINDOW SYSTEM VALUE
	int nDialogFrameHeight = 0;
	int nDialogFrameWidth = 0;
    int cxvs    =   0;
    int cyvs    =   0;
    int cxhs    =   0;
    int cyhs    =   0;

    if (pParent->GetStyle() & WS_VSCROLL)   {
        cxvs = GetSystemMetrics (SM_CXVSCROLL);
        cyvs = GetSystemMetrics (SM_CYVSCROLL);
    }

    if (pParent->GetStyle() & WS_HSCROLL)   {
        cxhs = GetSystemMetrics (SM_CXHSCROLL);
        cyhs = GetSystemMetrics (SM_CYHSCROLL);
    }
    
	if((pParent->GetStyle() & WS_BORDER))	{
		nDialogFrameHeight = GetSystemMetrics(SM_CYDLGFRAME);
		nDialogFrameWidth = GetSystemMetrics(SM_CYDLGFRAME);
	}
	
	if(pParent->GetStyle() & WS_THICKFRAME)    {
		nDialogFrameHeight+=1;
		nDialogFrameWidth+=1;
	}
	
	pParent->ScreenToClient(&windowRT);

    windowRT.InflateRect(nDialogFrameWidth,
        nTitleBarHeight+nDialogFrameHeight,
        nDialogFrameWidth,
        nTitleBarHeight+nDialogFrameHeight);

    // Vertical Scrollbar
    BOOL bVShow, bHShow;
	BOOL bVChanged = FALSE, bHChanged = FALSE;
    CRect regionRT  =   windowRT;
    if (GetScrollLimit(SB_VERT) != 0)
    {
		if(!m_SkinVerticleScrollbar.IsWindowVisible()) bVChanged = TRUE;

        regionRT.left   =   windowRT.left-nDialogFrameWidth;
        regionRT.right  =   windowRT.right-nDialogFrameWidth - SCROLLBAR_WIDTH;
        m_SkinVerticleScrollbar.ShowWindow(SW_NORMAL);
        bVShow  =   TRUE;
    }   else    {
		if(m_SkinVerticleScrollbar.IsWindowVisible()) bVChanged = TRUE;

        m_SkinVerticleScrollbar.ShowWindow(SW_HIDE);
        bVShow  =   FALSE;
    }

    // Horizontal Scrollbar
    if (GetScrollLimit(SB_HORZ) != 0)
    {
		if(!m_SkinHorizontalScrollbar.IsWindowVisible()) bHChanged = TRUE;

        regionRT.top    =   windowRT.top-nTitleBarHeight-nDialogFrameHeight;
        regionRT.bottom =   windowRT.bottom-nTitleBarHeight-nDialogFrameHeight - SCROLLBAR_HEIGHT;
        m_SkinHorizontalScrollbar.ShowWindow(SW_NORMAL);
        bHShow  =   TRUE;
    }   else        {
		if(m_SkinHorizontalScrollbar.IsWindowVisible()) bHChanged = TRUE;

        m_SkinHorizontalScrollbar.ShowWindow(SW_HIDE);
        bHShow  =   FALSE;
    }

    if (bVChanged) m_ctrlHeader.Invalidate(FALSE);

    HRGN iehrgn = CreateRectRgn(regionRT.left, regionRT.top, regionRT.right, regionRT.bottom);
    SetWindowRgn(iehrgn, TRUE);

    // SCROLLBAR SIZE SET
	CRect vBar(windowRT.right-nDialogFrameWidth - SCROLLBAR_WIDTH, 
        windowRT.top-nTitleBarHeight-nDialogFrameHeight- SCROLLBAR_WIDTH + 1, 
        windowRT.right+0-nDialogFrameWidth, 
        windowRT.bottom-nTitleBarHeight-nDialogFrameHeight);
	CRect hBar(windowRT.left-nDialogFrameWidth, 
        windowRT.bottom-nTitleBarHeight-nDialogFrameHeight - SCROLLBAR_HEIGHT, 
        bVShow ? windowRT.right-nDialogFrameWidth - SCROLLBAR_WIDTH:windowRT.right-nDialogFrameWidth, 
        windowRT.bottom+0-nTitleBarHeight-nDialogFrameHeight);

    // SCROLLBAR WINDOWS RESIZING
	m_SkinVerticleScrollbar.SetWindowPos(NULL,vBar.left,vBar.top,vBar.Width(),vBar.Height(),SWP_NOZORDER);
	m_SkinHorizontalScrollbar.SetWindowPos(NULL,hBar.left,hBar.top,hBar.Width(),hBar.Height(),SWP_NOZORDER);
	
	m_SkinHorizontalScrollbar.UpdateThumbPosition();
	m_SkinVerticleScrollbar.UpdateThumbPosition();
}