//*********************************************************************************************************
void CBCGPBaseFilterPopupMenu::RecalcLayout(BOOL bNotify /* = TRUE */)
{
	CBCGPPopupMenu::RecalcLayout(bNotify);

	if (m_wndMenuBar.GetSafeHwnd() != NULL)
	{
		m_wndMenuBar.m_arColumns.RemoveAll();
		m_wndMenuBar.AdjustLayout();
	}

	if (m_wndList.GetSafeHwnd() == NULL)
	{
		return;
	}

	const int nShadowSize = CBCGPToolBar::IsCustomizeMode () ? 0 : m_iShadowSize;
	const int nBorderSize = GetBorderSize();

	CRect rectClient;
	GetClientRect(rectClient);

	rectClient.DeflateRect (nBorderSize, nBorderSize);

	if (GetExStyle() & WS_EX_LAYOUTRTL)
	{
		rectClient.left += nShadowSize;
	}
	else
	{
		rectClient.right -= nShadowSize;
	}
	
	rectClient.top += m_nMenuBarHeight;
	rectClient.bottom -= nShadowSize;

#ifndef _BCGSUITE_
	rectClient.left += m_wndMenuBar.GetGutterWidth();
#endif

	if (!m_rectResize.IsRectEmpty())
	{
		if (m_bIsResizeBarOnTop)
		{
			rectClient.top += m_rectResize.Height();
		}
		else
		{
			rectClient.bottom -= m_rectResize.Height();
		}
	}

	m_wndList.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOZORDER | SWP_NOACTIVATE);
	m_wndList.m_bIsEmptyMenu = GetMenuItemCount() == 0;
}