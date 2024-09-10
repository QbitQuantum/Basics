int CUndoBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPPopupMenuBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CFont* pMenuFont = (CFont*) &CBCGPMenuBar::GetMenuFont ();

	//------------------
	// Set label height:
	//------------------
	CClientDC dc (this);
	CFont* pOldFont = dc.SelectObject (pMenuFont);

	TEXTMETRIC tm;
	dc.GetTextMetrics (&tm);

	m_nLabelHeight = tm.tmHeight + 2;

	dc.SelectObject (pOldFont);

	CRect rectDummy (0, 0, 0, 0);
	m_wndList.Create (WS_VISIBLE | WS_CHILD | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY | WS_VSCROLL | LBS_MULTIPLESEL, 
						rectDummy, this, ID_LIST);
	m_wndList.ModifyStyleEx (0, WS_EX_CLIENTEDGE);

	m_wndList.SetFont (pMenuFont);

	CUndoButton* pUndoButton = GetParentButton ();
	ASSERT_VALID (pUndoButton);

	for (POSITION pos = pUndoButton->m_lstActions.GetHeadPosition (); pos != NULL;)
	{
		m_wndList.AddString (pUndoButton->m_lstActions.GetNext (pos));
	}

	return 0;
}