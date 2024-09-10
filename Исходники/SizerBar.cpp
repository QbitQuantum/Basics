//////////////////
// User pressed mouse: intialize and enter drag state
//
void CSizerBar::OnLButtonDown(UINT nFlags, CPoint pt)
{
	m_bDragging=TRUE;
	m_ptOriginal = m_ptPrevious = Rectify(pt);
	
	GetWindowRect(&m_rcBar); // bar location in screen coords
	
	DrawBar();					 // draw it
	SetCapture();				 // all mouse messages are MINE
	m_hwndPrevFocus = ::SetFocus(m_hWnd);  // set focus to me to get Escape key

	ASSERT(m_pWinMgr);
	CWinMgr& wm = *m_pWinMgr;

	// get WINRECTs on either side of me
	WINRECT* pwrcSizeBar = wm.FindRect(GetDlgCtrlID());
	ASSERT(pwrcSizeBar);
	WINRECT* prev = pwrcSizeBar->Prev();
	ASSERT(prev);
	WINRECT* next = pwrcSizeBar->Next();
	ASSERT(next);

	// get rectangles on eithr side of me
	CRect rcPrev = prev->GetRect();
	CRect rcNext = next->GetRect();

	// get parent window
	CWnd * pParentWnd = GetParent();
	ASSERT(pParentWnd);

	// Get size info for next/prev rectangles, so I know what the min/max
	// sizes are and don't violate them. Max size never tested.
	SIZEINFO szi;
	wm.OnGetSizeInfo(szi, prev, pParentWnd);
	CRect rcPrevMin(rcPrev.TopLeft(),szi.szMin);
	CRect rcPrevMax(rcPrev.TopLeft(),szi.szMax);

	wm.OnGetSizeInfo(szi, next, pParentWnd);
	CRect rcNextMin(rcNext.BottomRight()-szi.szMin, rcNext.BottomRight());
	CRect rcNextMax(rcNext.BottomRight()-szi.szMax, rcNext.BottomRight());

	// Initialize m_rcConstrain. This is the box the user is allowed to move
	// the sizer bar in. Can't go outside of this--would violate min/max
	// constraints of windows on either side.
	m_rcConstrain.SetRect(
		max(rcPrevMin.right, rcNextMax.left),
		max(rcPrevMin.bottom,rcNextMax.top),
		min(rcPrevMax.right, rcNextMin.left),
		min(rcPrevMax.bottom,rcNextMin.top));

	// convert to my client coords
	pParentWnd->ClientToScreen(&m_rcConstrain);
	ScreenToClient(&m_rcConstrain);

	// Now adjust m_rcConstrain for the fact the bar is not a pure line, but
	// has solid width -- so I have to make a little bigger/smaller according
	// to the offset of mouse coords within the sizer bar rect iteself.
	ClientToScreen(&pt);
	m_rcConstrain.SetRect(m_rcConstrain.TopLeft() + (pt - m_rcBar.TopLeft()),
		m_rcConstrain.BottomRight() - (m_rcBar.BottomRight()-pt));
}