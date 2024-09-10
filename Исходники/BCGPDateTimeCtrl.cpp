//************************************************************************************
void CBCGPDateTimeCtrl::OnLButtonDown(UINT /*nFlags*/, CPoint point) 
{
	m_iPrevDigit = -1;

	int iPrevPart = m_iPartNum;

	SetFocus ();

	if (m_rectDropButton.PtInRect (point) && IsWindowEnabled())
	{
		if (m_dropCalendar && m_bIsChecked && m_showDate)
		{
			m_bDropButtonIsPressed = TRUE;

			SetCapture ();
			RedrawWindow (m_rectDropButton);

			OnShowCalendarPopup ();
		}

		return;
	}

	int iPartNum = GetPartFromPoint (point);
	if (iPartNum == -1)
	{
		m_CurrPartType = NO;

		if (m_rectText.PtInRect (point))
		{
			do
			{
				point.x++;

				if (point.x > m_rectText.right)
				{
					return;
				}

				iPartNum = GetPartFromPoint (point);
			}
			while (iPartNum == -1);
		}
		else
		{
			return;
		}
	}

	if (!m_bIsChecked &&
		m_arPartsOrder [iPartNum] != CHECK_BOX)
	{
		return;
	}

	m_iPartNum = iPartNum;
	m_CurrPartType = m_arPartsOrder [m_iPartNum];

	if (m_CurrPartType == CHECK_BOX)
	{
		ToggleCheck ();
	}

	if (iPrevPart != m_iPartNum)
	{
		CRect rectPrevPart = m_arPartRects [iPrevPart];
		rectPrevPart.InflateRect (1, 1);
		RedrawWindow (rectPrevPart);

		CRect rectPart = m_arPartRects [m_iPartNum];
		rectPart.InflateRect (1, 1);
		RedrawWindow (rectPart);
	}
}