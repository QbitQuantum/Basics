void CBCGPPlannerViewMonth::AdjustRects ()
{
	const int nDays = GetViewDuration ();

	const int nRows    = nDays / 7;
	const int dxColumn = CBCGPPlannerView::round (m_rectApps.Width () / (m_bCompressWeekend ? 6.0 : 7.0)) - 1;
	const int dxRow    = CBCGPPlannerView::round (m_rectApps.Height () / (double)nRows) - 1;

	const int nDayStart = (IsCompressWeekend () && CBCGPPlannerManagerCtrl::GetFirstDayOfWeek () == 0)
		? 1
		: CBCGPPlannerManagerCtrl::GetFirstDayOfWeek ();

	if (m_ViewRects.GetSize () != nDays)
	{
		m_ViewRects.SetSize (nDays);
	}

	int iRow = 0;
	for (iRow = 0; iRow < nRows; iRow++)
	{
		CRect rect (m_rectApps);
		rect.right   = rect.left + dxColumn;
		rect.top    += iRow * (dxRow + 1);
		rect.bottom  = iRow == (nRows - 1) ? rect.bottom : rect.top + dxRow;

		int nTop    = rect.top;
		int nBottom = rect.bottom;

		int nColumn = 0;

		for (int iDay = 0; iDay < 7; iDay++)
		{
			int nWeekDay = nDayStart + iDay - 7;

			if (m_bCompressWeekend)
			{
				if (nWeekDay == -1)
				{
					rect.bottom = rect.top + dxRow / 2;
				}
				else if (nWeekDay == 0)
				{
					rect.top = rect.bottom + 1;
					rect.bottom = nBottom;
				}
				else
				{
					rect.top = nTop;
				}
			}

			m_ViewRects[iRow * 7 + iDay] = rect;

			if ((m_bCompressWeekend && nWeekDay != -1) || !m_bCompressWeekend)
			{
				rect.OffsetRect (dxColumn + 1, 0);

				nColumn++;

				if ((m_bCompressWeekend && nColumn == 5) ||
					(!m_bCompressWeekend && nColumn == 6))
				{
					rect.right = m_rectApps.right;
				}
			}
		}
	}

	if (m_nWeekBarWidth > 0)
	{
		int nIndex = 0;
		if (IsCompressWeekend () && m_ViewRects[0].top != m_ViewRects[1].top)
		{
			nIndex = 2;
		}

		m_WeekRects.SetSize (nRows);

		for (iRow = 0; iRow < nRows; iRow++)
		{
			CRect rect (m_ViewRects[nIndex]);
			rect.right = m_rectApps.left;
			rect.left  = rect.right - m_nRowHeight;

			rect.top    += m_nRowHeight;
			rect.InflateRect (0, 1);

			m_WeekRects[iRow] = rect;

			nIndex += 7;
		}
	}
}