//**************************************************************************
void CBCGPComboBox::OnPaint() 
{
#ifndef _BCGSUITE_
	if (globalData.bIsWindows9x)
	{
		Default();
		return;
	}
#endif

	if ((GetStyle () & 0x0003L) == CBS_SIMPLE)
	{
		Default ();
		return;
	}

	if (!m_bVisualManagerStyle && !m_bOnGlass)
	{
		Default ();
		return;
	}

	CPaintDC dc(this); // device context for painting

	BYTE alpha = 0;
	if (m_bOnGlass)
	{
		alpha = 255;
	}

	CBCGPMemDC memDC (dc, this, alpha);
	CDC* pDC = &memDC.GetDC ();
	
	CRect rectClient;
	GetClientRect (rectClient);

	CBCGPDrawManager dm (*pDC);
	dm.DrawRect (rectClient, globalData.clrWindow, (COLORREF)-1);

	SendMessage (WM_PRINTCLIENT, (WPARAM) pDC->GetSafeHdc (), (LPARAM) PRF_CLIENT);

	const int cxDropDown = ::GetSystemMetrics (SM_CXVSCROLL) + 4;

	m_rectBtn = rectClient;
	m_rectBtn.left = m_rectBtn.right - cxDropDown;

	m_rectBtn.DeflateRect (2, 2);

	CBCGPDrawOnGlass dog (m_bOnGlass);

	CBCGPToolbarComboBoxButton buttonDummy;
#ifndef _BCGSUITE_
	buttonDummy.m_bIsCtrl = TRUE;

	CBCGPVisualManager::GetInstance ()->OnDrawComboDropButton (
		pDC, m_rectBtn, !IsWindowEnabled (), m_bIsDroppedDown,
		m_bIsButtonHighlighted,
		&buttonDummy);
#else
	CMFCVisualManager::GetInstance ()->OnDrawComboDropButton (
		pDC, m_rectBtn, !IsWindowEnabled (), m_bIsDroppedDown,
		m_bIsButtonHighlighted,
		&buttonDummy);
#endif

	dm.DrawRect (rectClient, (COLORREF)-1, globalData.clrBarShadow);
	rectClient.DeflateRect (1, 1);
	dm.DrawRect (rectClient, (COLORREF)-1, globalData.clrWindow);
}