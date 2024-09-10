void CBCGPSDPlaceMarkerWnd::ShowTabbedAt (CRect rect, CRect rectTab)
{
    if (!m_bTabbed || m_rectLast != rect || m_rectTab != rectTab)
    {
        Hide ();

        CRgn rgnMain;
        CBCGPTabbedControlBar::m_bTabsAlwaysTop ? 
			rgnMain.CreateRectRgn (0, rectTab.Height (), rect.Width(), rect.Height() + rectTab.Height ()) :
			rgnMain.CreateRectRgn (0, 0, rect.Width(), rect.Height());

        CRgn rgnTab;
        if (CBCGPTabbedControlBar::m_bTabsAlwaysTop)
		{
			rgnTab.CreateRectRgn (rectTab.left, 0, rectTab.Width (), rectTab.Height ());
		}
		else
		{
			rgnTab.CreateRectRgnIndirect (rectTab);
		}

        rgnMain.CombineRgn (&rgnMain, &rgnTab, RGN_OR);
        SetWindowRgn (rgnMain, FALSE);

        m_bTabbed = TRUE;

        m_rectLast = rect;
		m_rectTab = rectTab;

		if (CBCGPTabbedControlBar::m_bTabsAlwaysTop)
		{
			SetWindowPos (&CWnd::wndTop, rect.left, rectTab.top, 
				rect.Width(), rect.Height() + m_rectTab.Height (),
				SWP_NOACTIVATE | SWP_SHOWWINDOW | SWP_NOREDRAW);
		}
		else
		{
			SetWindowPos (&CWnd::wndTop, rect.left, rect.top, 
				rect.Width(), rect.Height() + m_rectTab.Height (),
				SWP_NOACTIVATE | SWP_SHOWWINDOW | SWP_NOREDRAW);
		}
		m_bShown = TRUE;
        RedrawWindow ();
    }
}