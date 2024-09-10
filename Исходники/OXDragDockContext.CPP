// start dragging. This is the only routine exposed externally. 
// pt = mouse position at start of drag (screen co-ords) 
void COXDragDockContext::StartDrag(CPoint pt)
{
   	ASSERT_VALID(m_pBar);
   	ASSERT(m_pBar->IsKindOf(RUNTIME_CLASS(COXSizeControlBar)));

   	COXSizeControlBar* pSzBar = (COXSizeControlBar*)m_pBar;

    // get styles from bar
   	m_dwDockStyle = m_pBar->m_dwDockStyle;
   	m_dwStyle = m_pBar->m_dwStyle & CBRS_ALIGN_ANY;
   	ASSERT(m_dwStyle != 0);
	
	// check to see we're not hanging from a COXMDIFloatWnd. 
	// Disallow dragging if we are...
	if (m_pBar->IsFloating())
	{
		CFrameWnd* pFrameWnd = m_pBar->GetParentFrame();
		ASSERT(pFrameWnd != NULL);
		ASSERT(pFrameWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)));
		if (pFrameWnd->IsKindOf(RUNTIME_CLASS(COXMDIFloatWnd)))
			return;				// do nothing if floating inside a COXMDIFloatWnd
	}
	
	// dragging has started message (only if window will actually dock !)
    if ((m_dwDockStyle & CBRS_ALIGN_ANY) == CBRS_ALIGN_ANY)
		AfxGetMainWnd()->SendMessage(WM_SETMESSAGESTRING, IDS_OX_MRC_STARTDOCKING);
	
    // handle pending WM_PAINT messages
    MSG msg;
    while (::PeekMessage(&msg, NULL, WM_PAINT, WM_PAINT, PM_NOREMOVE))
	{
		if (!GetMessage(&msg, NULL, WM_PAINT, WM_PAINT))
			return;
		ASSERT(msg.message == WM_PAINT);
        DispatchMessage(&msg);
	}
	
    // initialize drag state
   	m_rectLast.SetRectEmpty();
   	m_sizeLast.cx = m_sizeLast.cy = 0;
   	m_bForceFrame = m_bFlip = m_bDitherLast = FALSE;
	
	
   	// get current bar location 
   	CRect rect;
   	m_pBar->GetWindowRect(rect);
   	m_ptLast = pt;
   	m_ptStart = pt;
	BOOL bHorz = HORZF(m_dwStyle);
	
   	// MFC includes code for flipping orientation using the shift key - I wasn't keen
	// on this... (sorry) so I've left it out for now. Some references are still left
	// in for it, in case I decide to implement it.
   	
   	// Start by working out the possible rectangles that dragging could result in.
	// These are:
	// m_rectFrameDragHorz	: floating frame, horizontal orientation
	// m_rectFrameDragVert	: floating frame, vertical orientation (not used, 'cos
	//									flipping not allowed)
	//
	// m_rectDragHorz		: docking horizontally, another bar already on this row
	// m_rectDragVert		: docking vertically, another bar already on this row
	
	// m_rectDragHorzAlone  : docking horizontally, on a new row
	// m_rectDragVertAlone  : docking vertically, on a new row
	
	
	// calculate dragging rects if you drag on the new row/column
	//
	CRect rectBorder;
	m_pDockSite->RepositionBars(0,0xffff,AFX_IDW_PANE_FIRST, 
		CFrameWnd::reposQuery,&rectBorder);
	m_pDockSite->ClientToScreen(rectBorder);
	CWnd* pLeftDockBar=m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_LEFT);
	if(pLeftDockBar!=NULL && pLeftDockBar->GetStyle()&WS_VISIBLE)
	{
		CRect rectDockBar;
		pLeftDockBar->GetWindowRect(rectDockBar);
		rectBorder.left-=rectDockBar.Width();
	}
	CWnd* pRightDockBar=m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_RIGHT);
	if(pRightDockBar!=NULL && pRightDockBar->GetStyle()&WS_VISIBLE)
	{
		CRect rectDockBar;
		pRightDockBar->GetWindowRect(rectDockBar);
		rectBorder.right+=rectDockBar.Width();
	}
	m_rectDragHorzAlone=CRect(CPoint(rectBorder.left,rect.top),rectBorder.Size());
	m_rectDragVertAlone=CRect(CPoint(rect.left,rectBorder.top),rectBorder.Size());
	m_rectDragHorzAlone.bottom=m_rectDragHorzAlone.top+pSzBar->m_HorzDockSize.cy;
	m_rectDragVertAlone.right=m_rectDragVertAlone.left+pSzBar->m_VertDockSize.cx;
	//
	//////////////////////////////////////////////////////////////


	//////////////////
	//
	int nDockAreaWidth = rectBorder.Width();
	int nDockAreaHeight = rectBorder.Height();

	CSize HorzAloneSize(nDockAreaWidth, pSzBar->m_HorzDockSize.cy);
	CSize VertAloneSize(pSzBar->m_VertDockSize.cx, nDockAreaHeight);
	
	// sizes to use when docking into a row that already has some bars.
	// use the stored sizes - unless they are > the max dock area - 
	// in which case make a guess.
	if (pSzBar->m_VertDockSize.cy >= nDockAreaHeight - 16)
		VertAloneSize.cy = nDockAreaHeight / 3;
	else 
		VertAloneSize.cy = pSzBar->m_VertDockSize.cy;
	
	if (pSzBar->m_HorzDockSize.cx >= nDockAreaWidth - 16)
		HorzAloneSize.cx = nDockAreaWidth / 3;
	else
		HorzAloneSize.cx = pSzBar->m_HorzDockSize.cx;
	

	m_rectDragHorz = CRect(rect.TopLeft(), HorzAloneSize);
	m_rectDragVert = CRect(rect.TopLeft(), VertAloneSize);
	//
	///////////////////


   	// rectangle for the floating frame...
   	m_rectFrameDragVert = m_rectFrameDragHorz = 
		CRect(rect.TopLeft(), pSzBar->m_FloatSize);
   	
   	// To work out the size we actually create a floating mini frame, and then see how big
   	// it is
	CMiniDockFrameWnd* pFloatFrame =
		m_pDockSite->CreateFloatingFrame(bHorz ? CBRS_ALIGN_TOP : CBRS_ALIGN_LEFT);
   	if (pFloatFrame == NULL)
		AfxThrowMemoryException();
   	pFloatFrame->CalcWindowRect(&m_rectFrameDragHorz);
   	pFloatFrame->CalcWindowRect(&m_rectFrameDragVert);
// 	m_rectFrameDragHorz.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
// 	m_rectFrameDragVert.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
   	pFloatFrame->DestroyWindow();

	// adjust rectangles so that point is inside
	AdjustRectangle(m_rectDragHorzAlone, pt);
	AdjustRectangle(m_rectDragVertAlone, pt);
   	AdjustRectangle(m_rectDragHorz, pt);
   	AdjustRectangle(m_rectDragVert, pt);
   	AdjustRectangle(m_rectFrameDragHorz, pt);
   	AdjustRectangle(m_rectFrameDragVert, pt);
	
   	// lock window update while dragging
   	ASSERT(m_pDC == NULL);
   	CWnd* pWnd = CWnd::GetDesktopWindow();
#ifndef _MAC
    if (pWnd->LockWindowUpdate()) 
		m_pDC = pWnd->GetDCEx(NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
    else
#endif
		m_pDC = pWnd->GetDCEx(NULL, DCX_WINDOW|DCX_CACHE);
    ASSERT(m_pDC != NULL); 
	
	// initialize tracking state and enter tracking loop
	m_dwOverDockStyle = CanDock();
    Move(pt);   // call it here to handle special keys
    Track();
}