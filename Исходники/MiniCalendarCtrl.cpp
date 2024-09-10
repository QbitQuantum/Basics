// draw the month/year header (ie. January 2000)
int CMiniCalendarCtrl::DrawHeader(CDC& _dc,
								  int _iY,
								  int _iLeftX,
								  int _iRow,
								  int _iMonth,
								  int _iYear)
{
	CString strText = GetMonthName(_iMonth);
	strText += " ";
	strText += CCalendarUtils::LongToString(_iYear);

	_dc.FillSolidRect(_iLeftX, _iY, m_szMonthSize.cx-1, m_iHeaderHeight, ::GetSysColor(COLOR_BTNFACE));
	_dc.Draw3dRect(_iLeftX, _iY, m_szMonthSize.cx-1, m_iHeaderHeight, m_cBackColor, ::GetSysColor(COLOR_3DSHADOW));

	CFont* pOldFont = _dc.SelectObject(m_pFontBold);
	_dc.SetBkColor(::GetSysColor(COLOR_BTNFACE));
	_dc.SetTextColor(MINICAL_COLOUR_HEADERFONT);
	_dc.SetBkMode(TRANSPARENT);

	_dc.DrawText(strText, CRect(_iLeftX+1, _iY+1, _iLeftX+m_szMonthSize.cx-2, _iY+m_iHeaderHeight-2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	_dc.SelectObject(pOldFont);

	SetCellHeaderPosition(_iRow, CRect(_iLeftX+10, _iY+1, _iLeftX+m_szMonthSize.cx - 20, _iY+m_iHeaderHeight-2));

	if (_iRow == 1)
	{
		// deal with left scroll bar
		const int iMiddle = _iY + (m_iHeaderHeight / 2);
		const int iTop = iMiddle - (m_iHeaderHeight / 4);
		const int iBottom = iMiddle + (m_iHeaderHeight / 4);
		int iLineY = 0;

		int iX1 = _iLeftX + 6;
		int iX2 = iX1 + ((m_iHeaderHeight / 4));

		for (iLineY = iTop; iLineY <= iBottom; iLineY++)
		{
			_dc.MoveTo(iX1, iMiddle);
			_dc.LineTo(iX2, iLineY);
		}
		m_rectScrollLeft.SetRect(iX1-1, iTop-1, iX2+1, iBottom+1);


		// deal with right scroll bar
		iX1 = _iLeftX + m_szMonthSize.cx - 10;
		iX2 = iX1 - (m_iHeaderHeight / 4);

		for (iLineY = iTop; iLineY <= iBottom; iLineY++)
		{
			_dc.MoveTo(iX1, iMiddle);
			_dc.LineTo(iX2, iLineY);
		}
		m_rectScrollRight.SetRect(iX2-1, iTop-1, iX1+1, iBottom+1);
	}

	return m_iHeaderHeight;
}