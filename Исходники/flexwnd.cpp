void CFlexWnd::RenderInto(HDC hDC, int x, int y)
{
	if (hDC == NULL)
		return;
		
	int sdc = SaveDC(hDC);
	{
		OffsetViewportOrgEx(hDC, x, y, NULL);
		SIZE size = GetClientSize();
		IntersectClipRect(hDC, 0, 0, size.cx, size.cy);

		m_hRenderInto = hDC;

		int sdc2 = SaveDC(hDC);
		{
			EnumChildWindows/*ZDown*/(m_hWnd, ::RenderIntoClipChild, (LPARAM)(PVOID)this);
			EnumSiblingsAbove(m_hWnd, ::RenderIntoClipChild, (LPARAM)(PVOID)this);
			DoOnPaint(hDC);
		}
		if (sdc2)
			RestoreDC(hDC, sdc2);

		EnumChildWindows/*ZDown*/(m_hWnd, ::RenderIntoRenderChild, (LPARAM)(PVOID)this);

		m_hRenderInto = NULL;
	}

	if (sdc)
		RestoreDC(hDC, sdc);
}