void CRoundButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();

	ModifyStyle(0, BS_OWNERDRAW);

	CRect rect;
	GetClientRect(rect);

	// Resize the window to make it square
	rect.bottom = rect.right = min(rect.bottom,rect.right);

	// Get the vital statistics of the window
	m_ptCentre = rect.CenterPoint();
	m_nRadius  = rect.bottom/2-1;

	// Set the window region so mouse clicks only activate the round section 
	// of the button
	m_rgn.DeleteObject(); 
	SetWindowRgn(NULL, FALSE);
	m_rgn.CreateEllipticRgnIndirect(rect);
	SetWindowRgn(m_rgn, TRUE);

	// Convert client coords to the parents client coords
	ClientToScreen(rect);
	CWnd* pParent = GetParent();
	if (pParent) pParent->ScreenToClient(rect);

	// Resize the window
	MoveWindow(rect.left, rect.top, rect.Width(), rect.Height(), TRUE);
}