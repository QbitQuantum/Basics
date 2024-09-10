bool CLogGraph::attach(UINT id, CWnd* pParent)
{
	CStatic  wndStatic;		
	CRect    r;

	if (pParent == NULL || !wndStatic.SubclassDlgItem(id, pParent))
		return false;

	wndStatic.GetWindowRect(&r);
	pParent->ScreenToClient(&r);
		
	if ( !CreateEx( wndStatic.GetExStyle(), 
		            NULL, NULL, WS_CHILD | WS_VISIBLE | wndStatic.GetStyle(),
		            r, pParent, id, NULL))
	{		
		wndStatic.DestroyWindow();
		return false;
	}
	
	wndStatic.DestroyWindow();

	EnableScrollBarCtrl(SB_HORZ, TRUE);
	GetClientRect(&m_rectWnd);
	calcRect();
	SetTimer(11839, 1000, NULL);

	m_bCreated = true;
	return true;
}