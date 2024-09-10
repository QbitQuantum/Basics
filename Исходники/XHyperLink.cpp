// Move and resize the window so that the window is the same size
// as the hyperlink text. This stops the hyperlink cursor being active
// when it is not directly over the text. If the text is left justified
// then the window is merely shrunk, but if it is centred or right
// justified then the window will have to be moved as well.
//
// Suggested by Pål K. Tønder 
//
void CXHyperLink::PositionWindow()
{
	if (!::IsWindow(GetSafeHwnd()) || !m_bAdjustToFit) 
		return;

	// Get the current window position
	CRect WndRect, ClientRect;
	GetWindowRect(WndRect);
	GetClientRect(ClientRect);

	ClientToScreen(ClientRect);

	CWnd* pParent = GetParent();
	if (pParent)
	{
		pParent->ScreenToClient(WndRect);
		pParent->ScreenToClient(ClientRect);
	}

	// Get the size of the window text
	CString strWndText;
	GetWindowText(strWndText);

	CDC* pDC = GetDC();
	CFont* pOldFont = pDC->SelectObject(&m_UnderlineFont);
	CSize Extent = pDC->GetTextExtent(strWndText);
	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);

	// Adjust for window borders
	Extent.cx += WndRect.Width() - ClientRect.Width(); 
	Extent.cy += WndRect.Height() - ClientRect.Height(); 

	// Get the text justification via the window style
	DWORD dwStyle = GetStyle();

	// Recalc the window size and position based on the text justification
	if (dwStyle & SS_CENTERIMAGE)
		WndRect.DeflateRect(0, (WndRect.Height() - Extent.cy)/2);
	else
		WndRect.bottom = WndRect.top + Extent.cy;

	if (dwStyle & SS_CENTER) 
		WndRect.DeflateRect((WndRect.Width() - Extent.cx)/2, 0);
	else if (dwStyle & SS_RIGHT) 
		WndRect.left = WndRect.right - Extent.cx;
	else // SS_LEFT = 0, so we can't test for it explicitly 
		WndRect.right = WndRect.left + Extent.cx;

	// Move the window
	SetWindowPos(NULL, 
				 WndRect.left, WndRect.top, 
				 WndRect.Width(), WndRect.Height(), 
				 SWP_NOZORDER);
}