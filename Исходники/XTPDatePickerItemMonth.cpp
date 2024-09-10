void CXTPDatePickerItemMonth::AutoAdjustLayout(CRect rcClient)
{
	m_rcMonth = rcClient;
	// calc header rect
	m_rcHeader = m_rcMonth;
	m_rcHeader.bottom = m_rcHeader.top + 18; // TODO: change to font height

	// calc days of week rect
	m_rcDaysOfWeek = m_rcMonth;
	m_rcDaysOfWeek.top = m_rcHeader.bottom;
	m_rcDaysOfWeek.bottom = m_rcDaysOfWeek.top + 18; // TODO: change to font height

	// draw week numbers
	m_rcWeekNumbers = m_rcMonth;
	m_rcWeekNumbers.top = m_rcDaysOfWeek.bottom;
	m_rcWeekNumbers.right = m_rcWeekNumbers.left + 18; // TODO: change to font width

	// calc triangles rect
	m_rcLeftScroll = m_rcHeader;
	m_rcRightScroll = m_rcHeader;
	int nScrollWidth = min(m_rcWeekNumbers.Width(), m_rcHeader.Width() / 8);
	m_rcHeader.left += nScrollWidth;
	m_rcHeader.right -= nScrollWidth;
	m_rcLeftScroll.right = m_rcHeader.left;
	m_rcRightScroll.left = m_rcHeader.right;

	// calc days display params
	m_rcDaysArea = m_rcMonth;
	m_rcDaysArea.top = m_rcDaysOfWeek.bottom;
	m_rcDaysArea.left = m_rcWeekNumbers.right;
	m_rcDaysArea.right -= m_rcWeekNumbers.Width();

	// calc simple day rect sizes
	CSize szDay(m_rcDaysArea.Width() / XTP_WEEK_DAYS,
				m_rcDaysArea.Height() / XTP_MAX_WEEKS);

	// calc rects for all days
	CRect rcDay;
	int nIndex = 0;
	for (int nWeek = 0; nWeek < XTP_MAX_WEEKS; nWeek++)
	{
		for (int nDay = 0; nDay < XTP_WEEK_DAYS; nDay++)
		{
			CXTPDatePickerItemDay* pDay = GetDay(nIndex);
			nIndex++;

			rcDay.left = m_rcDaysArea.left + nDay * szDay.cx + 1;
			rcDay.top = m_rcDaysArea.top + nWeek * szDay.cy;
			rcDay.right = rcDay.left + szDay.cx;
			rcDay.bottom = rcDay.top + szDay.cy;
			pDay->SetRect(rcDay);
		}
	}
}