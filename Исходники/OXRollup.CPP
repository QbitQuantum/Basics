void COXRollup::Arrange()
	{
	ASSERT_VALID(this);
	if (IsArranged()) return;
	
	CWnd* pMainWnd = AfxGetMainWnd();
	ASSERT((pMainWnd != NULL) && ::IsWindow(pMainWnd->m_hWnd));		// don´t care about OLE
	if (!pMainWnd->IsWindowEnabled() && pMainWnd->IsIconic())
		return;
	
	InternalRollUp();
	
	COXRollup* pRollup = NULL;
	if (!m_ArrangedRollups.IsEmpty())
		pRollup = (COXRollup*)m_ArrangedRollups.GetTail();	// get last rolled up element
	
	// we have got a rollup (or not...)
	CPoint topLeft(0,0);
	if (pRollup == NULL)
		{
		// we found no college that was rolled up, so we arrange to the left of the screen
		CRect rcLeftOver;
		CWnd* pWndLeftOverPane = pMainWnd->GetDlgItem(AFX_IDW_PANE_FIRST);
		ASSERT(pWndLeftOverPane != NULL);
		pWndLeftOverPane->GetWindowRect(&rcLeftOver);
		topLeft = CPoint(rcLeftOver.left, rcLeftOver.top);
		}
	else
		{
		ASSERT(pRollup != this);		// can´t happen, otherwise we would have been arranged
		ASSERT(pRollup->IsRolledUp());	// must be up if arranged
		CRect rcLastRollup;
		pRollup->GetWindowRect(&rcLastRollup);
		topLeft = CPoint(rcLastRollup.left, rcLastRollup.bottom - 1);
		}
	
	SetWindowPos(NULL, topLeft.x, topLeft.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	m_ArrangedRollups.AddTail(this);
	m_bIsArranged = TRUE;			
	}