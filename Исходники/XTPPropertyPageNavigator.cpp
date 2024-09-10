HBRUSH CXTPPropertyPageTabNavigator::GetPageBrush(CDC* pDC, CXTPPropertyPage* pPage)
{
	COLORREF clrClient = COLORREF_NULL;

	if (GetPaintManager()->GetColor() == xtpTabColorWinNative)
	{
		clrClient = COLOR_WINXP;
	}
	else
	{
		CXTPTabManagerItem* pItem = GetSelectedItem();
		if (!pItem)
			return NULL;

		clrClient = GetPaintManager()->GetColorSet()->GetItemColor(pItem);
	}

	if (m_clrBrush != clrClient)
	{
		m_brushPage.DeleteObject();
		m_clrBrush = clrClient;
	}

	if (m_brushPage.GetSafeHandle())
		return m_brushPage;

	if (m_clrBrush == GetXtremeColor(COLOR_3DFACE))
		return 0;

	if (m_clrBrush != COLOR_WINXP)
	{
		m_brushPage.CreateSolidBrush(m_clrBrush);
		return m_brushPage;

	}

	if (m_brushPage.GetSafeHandle() == 0)
	{
		CXTPClientRect rc(pPage);
		if (rc.IsRectEmpty())
			 return 0;

		CXTPWinThemeWrapper wrapper;
		wrapper.OpenTheme(0, L"TAB");

		if (!wrapper.IsAppThemed())
			return 0;

		CBitmap bmp;
		bmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
		{
			CRect   rectContent(0, 0, 0, 0);
			if (FAILED(wrapper.GetThemeBackgroundContentRect(pDC->GetSafeHdc(), TABP_PANE, 0, rc, rectContent)))
			{
				rectContent = rc;
				rectContent.DeflateRect(2, 2, 4, 4);
			}

			CRect rcPane(-rectContent.left, -rectContent.top, rc.right + (rc.right - rectContent.right),
				rc.bottom + (rc.bottom - rectContent.bottom));

			CXTPCompatibleDC dc(pDC, bmp);
			wrapper.DrawThemeBackground(dc, TABP_PANE, 0, rcPane, 0);
		}

		m_brushPage.Attach( ::CreatePatternBrush(bmp));
	}

	return m_brushPage;
}