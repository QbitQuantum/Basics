void CUnreadWavesFlyout::PaintBottom(CDC & dc, RECT & rcBounds)
{
	static HPEN hBorderPen = CreatePen(PS_SOLID, 1, RGB(204, 217, 234));
	static HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(241, 245, 251));
	static HFONT hFont = CreateFontIndirectEx(GetMessageBoxFont(), FW_NORMAL, FALSE, TRUE);

	CHECK_HANDLE(hBorderPen);
	CHECK_HANDLE(hBackgroundBrush);
	CHECK_HANDLE(hFont);

	//
	// Draw the background
	//

	RECT rc = rcBounds;

	rc.top = rc.bottom - FL_BOTTOM_HEIGHT;

	HGDIOBJ hOriginal = dc.SelectPen(hBorderPen);

	dc.MoveToEx(rc.left, rc.top, NULL);
	dc.LineTo(rc.right, rc.top);

	dc.SelectObject(hOriginal);

	rc.top += 1;

	dc.FillRect(&rc, hBackgroundBrush);

	dc.SelectObject(hOriginal);

	//
	// Draw the label
	//

	hOriginal = dc.SelectFont(hFont);

	TEXTMETRIC tm;

	dc.GetTextMetrics(&tm);

	rc = rcBounds;
	rc.top = rc.bottom - FL_BOTTOM_HEIGHT + 1;

	INT nOffset = ((rc.bottom - rc.top) - tm.tmHeight) / 2;

	rc.top += nOffset;
	rc.left += nOffset;
	rc.right -= nOffset;

	dc.DrawText(L"Go to Inbox", &rc, DT_CALCRECT | DT_END_ELLIPSIS | DT_NOPREFIX | DT_SINGLELINE);

	dc.SetTextColor(RGB(0, 102, 204));
	dc.SetBkColor(RGB(241, 245, 251));

	dc.DrawText(L"Go to Inbox", &rc, DT_END_ELLIPSIS | DT_NOPREFIX | DT_SINGLELINE);

	INT nCount = m_lpWaves->GetChanges().size() - FL_MAXIMUM_WAVES;

	if (nCount > 0)
	{
		wstring szBuffer;

		if (nCount == 1)
		{
			szBuffer = L"1 more unread wave";
		}
		else
		{
			szBuffer = Format(L"%d more unread waves", nCount);
		}

		RECT rc2 = rc;
		rc2.left = rc2.right;
		rc2.right = rcBounds.right - nOffset;

		dc.SetTextColor(GetSysColor(COLOR_BTNTEXT));
		dc.SelectFont(GetMessageBoxFont());

		dc.DrawText(szBuffer, &rc2, DT_END_ELLIPSIS | DT_NOPREFIX | DT_SINGLELINE | DT_RIGHT);
	}

	dc.SelectObject(hOriginal);
}