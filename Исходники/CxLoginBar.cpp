//********************************************************************************
BOOL CCxLoginBar::CreateEx (CWnd* pParentWnd, DWORD /*dwCtrlStyle*/, DWORD dwStyle, 
							 UINT nID)
{
	ASSERT_VALID(pParentWnd);   // must have a parent

	m_dwStyle |= CBRS_HIDE_INPLACE;

	//dwStyle &= ~CBRS_GRIPPER;

	m_dwStyle = (dwStyle & CBRS_ALL);
	// save the style
	SetBarAlignment (dwStyle & CBRS_ALL);

	SetBorders (CRect(1, 0, 1, 0));

	// create the HWND
	CRect rect;
	rect.SetRectEmpty();

#ifndef _BCGSUITE_
	m_dwBCGStyle = 0; // can't float, resize, close, slide
#else
	m_dwControlBarStyle = 0; // can't float, resize, close, slide
#endif

	if (!CBCGPBaseToolBar::Create (
		globalData.RegisterWindowClass (_T("CCxLoginBar")), dwStyle, rect, pParentWnd, nID, 0))
	{
		return FALSE;
	}

	////if (!CWnd::Create (globalData.RegisterWindowClass (_T("CCxLoginBar")),
	//if (!CWnd::Create (globalData.RegisterWindowClass (_T("CCxLoginBar")),
	//	NULL, dwStyle | WS_CLIPSIBLINGS, rect, pParentWnd, nID))
	//{
	//	return FALSE;
	//}

	//if (pParentWnd->IsKindOf (RUNTIME_CLASS (CBCGPFrameWnd)))
	//{
	//	((CBCGPFrameWnd*) pParentWnd)->AddControlBar (this);
	//}
	//else if (pParentWnd->IsKindOf (RUNTIME_CLASS (CBCGPMDIFrameWnd)))
	//{
	//	((CBCGPMDIFrameWnd*) pParentWnd)->AddControlBar (this);
	//}
	//else
	//{
	//	ASSERT (FALSE);
	//	return FALSE;
	//}

	m_ToolTip.Create(this);
	return TRUE;
}