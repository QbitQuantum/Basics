void CCalSupport::Draw()
{
	COLORREF LineColor = m_pCalSym->m_LineColor;
	bool bInvisible = (LineColor == CLR_NONE);
	int LineWidth = m_pCalSym->m_LineWidth;
	if (bInvisible)
		LineWidth = LT_None;

	CAGMatrix LineInverseMatrix = m_dc.GetSymbolMatrix();
	double fAngle = LineInverseMatrix.GetAngle();
	LineInverseMatrix.Rotate(-fAngle, -fAngle);
	LineInverseMatrix = LineInverseMatrix.Inverse();

	int nLineSize = (LineWidth == LT_Hairline ? 0 : LineWidth);
	int nLineWidth = dtoi(LineInverseMatrix.TransformWidth(nLineSize));
	int nLineHeight = dtoi(LineInverseMatrix.TransformHeight(nLineSize));

	RECT SymbolRect = m_pCalSym->m_DestRect;
	int iSymbolHeight = HEIGHT(SymbolRect);
	int iTitleHeight = (iSymbolHeight * m_pCalSym->m_uCalStyles.TitleSize) / 100;
	int iWeekHeight  = (iSymbolHeight * m_pCalSym->m_uCalStyles.DayOfWkSize) / 100;
	int iDatesHeight = (iSymbolHeight - iTitleHeight - iWeekHeight);
	int iDateHeight = ((iDatesHeight - nLineHeight) / 6);
	int iDateWidth = (WIDTH(SymbolRect) - nLineWidth) / 7;

	// Fill the 3 big background areas
	RECT TitleRect = SymbolRect;
	TitleRect.bottom = TitleRect.top + iTitleHeight;
	
	RECT WeekRect = SymbolRect;
	WeekRect.top = TitleRect.bottom;
	WeekRect.bottom = WeekRect.top + iWeekHeight;

	RECT DateRect = SymbolRect;
	DateRect.top = WeekRect.bottom;
	DateRect.bottom = DateRect.top + iDatesHeight;

	COLORREF TitleFillColor = (m_pCalSym->m_FillColor == CLR_DEFAULT ? CLR_NONE : m_pCalSym->m_FillColor);
	COLORREF WeekFillColor = (m_pCalSym->m_FillColor2 == CLR_DEFAULT ? CLR_NONE : m_pCalSym->m_FillColor2);
	COLORREF DateFillColor = (m_pCalSym->m_FillColor3 == CLR_DEFAULT ? CLR_NONE : m_pCalSym->m_FillColor3);

	CAGMatrix Matrix = m_dc.GetSymbolToDeviceMatrix();
	DrawBackgroundRectangle(TitleRect, Matrix, TitleFillColor);
	DrawBackgroundRectangle(WeekRect, Matrix, WeekFillColor);
	DrawBackgroundRectangle(DateRect, Matrix, DateFillColor);

	// Compute the Title rect
	TitleRect = SymbolRect;
	TitleRect.bottom = TitleRect.top + iTitleHeight + nLineHeight;

	// Draw the Title box and text
	m_pCalSym->m_SpecMonth.m_HorzJust = (eTSJust)m_pCalSym->m_uCalStyles1.TitleHorzJust;
	DrawRectangle(TitleRect, Matrix, LineColor, LineWidth, CLR_NONE, GetTitleStr(), m_pCalSym->m_SpecMonth, m_pCalSym->m_uCalStyles1.TitleVertJust, nLineWidth, nLineHeight);

	// Compute the Week rect
	WeekRect.left = SymbolRect.left;
	WeekRect.right = WeekRect.left + iDateWidth + nLineWidth;
	WeekRect.top = TitleRect.bottom - nLineHeight;
	WeekRect.bottom = WeekRect.top + iWeekHeight + nLineHeight;

	// Draw the Week boxes and text
	m_pCalSym->m_SpecWeek.m_HorzJust = (eTSJust)m_pCalSym->m_uCalStyles1.WeekHorzJust;

	bool bSunStart = (m_pCalSym->m_uCalStyles.WeekStart == CALSTYLES::SUNDAY_START);
	for (int i=0; i<7; i++)
	{
		int iDay = (bSunStart ? i : i+1);
		DrawRectangle(WeekRect, Matrix, LineColor, LineWidth, CLR_NONE, GetWeekStr(iDay), m_pCalSym->m_SpecWeek, m_pCalSym->m_uCalStyles1.WeekVertJust, nLineWidth, nLineHeight);

		// Update the Week rect
		WeekRect.left += iDateWidth;
		WeekRect.right = WeekRect.left + iDateWidth + nLineWidth;
		if (i == 5)
			WeekRect.right = SymbolRect.right;
	}

	// Compute the Date rect
	DateRect.left = 0;
	DateRect.right = 0;
	DateRect.top = WeekRect.bottom - nLineHeight;
	DateRect.bottom = DateRect.top + iDateHeight + nLineHeight;

	// Draw the Date boxes and text
	m_pCalSym->m_SpecDays.m_HorzJust = (eTSJust)m_pCalSym->m_uCalStyles1.DateHorzJust;

	int nDaysInMonth = GetDaysInMonth();
	int iDay = 2 - GetFirstDayOfMonth(); 
	for (int y=0; y<6; y++)
	{
		DateRect.left = SymbolRect.left;
		DateRect.right = DateRect.left + iDateWidth + nLineWidth;

		bool bRowEmpty = true;
		for (int x=0; x<7; x++)
		{
			bool bDraw = false;
			CString strText;
			if (iDay <= nDaysInMonth)
			{
				bDraw = true;
				if (iDay >= 1)
				{
					strText = String("%d", iDay);
					bRowEmpty = false;
				}
			}
			else
			{
				bool bHideUnusedBoxes = (m_pCalSym->m_uCalStyles.HideBoxes == 1); 
				bool bHideAllBoxes = (m_pCalSym->m_uCalStyles.HideAllBoxes == 1);
				bool bHideEmptyRows = (m_pCalSym->m_uCalStyles.HideAllBoxes == 0);
				bool bHide = bHideUnusedBoxes && (bHideAllBoxes || (bHideEmptyRows && bRowEmpty));
				bDraw = !bHide;
			}

			if (bDraw)
				DrawRectangle(DateRect, Matrix, LineColor, LineWidth, CLR_NONE, strText, m_pCalSym->m_SpecDays, m_pCalSym->m_uCalStyles1.DateVertJust, nLineWidth, nLineHeight);
			iDay++;

			// Update the Date rect
			DateRect.left += iDateWidth;
			DateRect.right = DateRect.left + iDateWidth + nLineWidth;
			if (x == 5)
				DateRect.right = SymbolRect.right;
		}

		// Update the Date rect
		DateRect.top += iDateHeight;
		DateRect.bottom = DateRect.top + iDateHeight + nLineHeight;
		if (y == 4)
			DateRect.bottom = SymbolRect.bottom;
	}
}