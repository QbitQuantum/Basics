void CBCGPPlannerPrintMonth::OnDrawClient (CDC* pDC)
{
	ASSERT_VALID (pDC);

	CRect rectFill (m_rectApps);

	int nMonth = m_Date.GetMonth ();

	const int nRows = GetViewDuration () / 7;

	COleDateTime day (GetDateStart ());

	int nIndex = 0;
	int iRow = 0;

	{
		CPen* pOldPen = pDC->SelectObject (&m_penBlack);

		const int nEnd = 7;

		int nCol = 0;
		int iColumn = 1;

		for (iColumn = 1; iColumn < 7; iColumn++)
		{
			if (m_ViewRects [iColumn - 1].right == m_ViewRects [iColumn].right)
			{
				nCol = iColumn - 1;
				break;
			}
		}

		for (iColumn = 1; iColumn < nEnd; iColumn++)
		{
			pDC->MoveTo (m_ViewRects [iColumn].left - m_OnePoint.cx, m_rectApps.top);
			pDC->LineTo (m_ViewRects [iColumn].left - m_OnePoint.cx, m_rectApps.bottom);
		}

		for (iRow = 0; iRow < nRows; iRow++)
		{
			int nIndex = iRow * 7 + 6;

			pDC->MoveTo (m_rectApps.left , m_ViewRects [nIndex].bottom);
			pDC->LineTo (m_rectApps.right, m_ViewRects [nIndex].bottom);

			if (m_bCompressWeekend)
			{
				nIndex -= (6 - nCol);
				pDC->MoveTo (m_ViewRects [nIndex].left, m_ViewRects [nIndex].bottom);
				pDC->LineTo (m_ViewRects [nIndex].right, m_ViewRects [nIndex].bottom);
			}
		}

		pDC->SelectObject (pOldPen);
	}

	DWORD dwFlags = GetDrawFlags ();
	BOOL bBold = (dwFlags & BCGP_PLANNER_DRAW_VIEW_CAPTION_DAY_BOLD) ==
			BCGP_PLANNER_DRAW_VIEW_CAPTION_DAY_BOLD;
	BOOL bCompact = (dwFlags & BCGP_PLANNER_DRAW_VIEW_CAPTION_DAY_COMPACT) ==
			BCGP_PLANNER_DRAW_VIEW_CAPTION_DAY_COMPACT;

	CFont* pOldFont = NULL;
	if (bBold)
	{
		pOldFont = pDC->SelectObject (&m_FontBold);
	}

	const BOOL bDateBeforeMonth = CBCGPPlannerView::IsDateBeforeMonth ();

	for (iRow = 0; iRow < nRows; iRow++)
	{
		for (int iDay = 0; iDay < 7; iDay++)
		{
			BOOL bAnotherMonth = nMonth != day.GetMonth ();

			int nDay = iRow * 7 + iDay;

			CRect rectDayCaption (m_ViewRects [nDay]);

			if (m_nRowHeight <= rectDayCaption.Height () + 2 * m_OnePoint.cy)
			{
				rectDayCaption.bottom = rectDayCaption.top + m_nRowHeight + m_OnePoint.cy;

				CString strFormat (_T("d"));
				CString strDate;

				BOOL bNewYear = FALSE;

				if (!bCompact)
				{
					if ((iRow == 0 && iDay == 0) || day.GetDay () == 1)
					{
						if (bDateBeforeMonth)
						{
							strFormat = _T("d MMMM");
						}
						else
						{
							strFormat = _T("MMMM d");
						}

						if (day.GetDay () == 1 && day.GetMonth () == 1)
						{
							bNewYear = TRUE;
							strFormat += _T(" yyyy");
						}			
					}

					if (!strFormat.IsEmpty ())
					{
						strDate.GetBuffer (_MAX_PATH);

						SYSTEMTIME st;
						day.GetAsSystemTime (st);

						::GetDateFormat (LOCALE_USER_DEFAULT, 0, &st, 
							strFormat, (LPTSTR)(LPCTSTR)strDate, _MAX_PATH);

						strDate.ReleaseBuffer ();

						CSize szSize (pDC->GetTextExtent (strDate));

						if (rectDayCaption.Width () - 4 < szSize.cx)
						{
							if (bDateBeforeMonth)
							{
								strFormat = _T("d MMM");
							}
							else
							{
								strFormat = _T("MMM d");
							}

							if (bNewYear)
							{
								strFormat += _T(" yy");
							}

							strDate.GetBuffer (_MAX_PATH);

							::GetDateFormat (LOCALE_USER_DEFAULT, 0, &st, 
								strFormat, (LPTSTR)(LPCTSTR)strDate, _MAX_PATH);

							strDate.ReleaseBuffer ();
						}
					}
				}
				else
				{
					if ((iRow == 0 && iDay == 0) || day.GetDay () == 1)
					{
						if (bDateBeforeMonth)
						{
							strFormat = _T("d MMM");
						}
						else
						{
							strFormat = _T("MMM d");
						}

						if (day.GetDay () == 1 && day.GetMonth () == 1)
						{
							bNewYear = TRUE;
							strFormat += _T(" yy");
						}
					}

					if (!strFormat.IsEmpty ())
					{
						strDate.GetBuffer (_MAX_PATH);

						SYSTEMTIME st;
						day.GetAsSystemTime (st);

						::GetDateFormat (LOCALE_USER_DEFAULT, 0, &st, 
							strFormat, (LPTSTR)(LPCTSTR)strDate, _MAX_PATH);

						strDate.ReleaseBuffer ();

						CSize szSize (pDC->GetTextExtent (strDate));

						if (rectDayCaption.Width () - 4 < szSize.cx)
						{
							strFormat = _T("d");
							BOOL bNeedFormat = TRUE;

							if (bNewYear)
							{
								if (bDateBeforeMonth)
								{
									strFormat += _T(" MMM");
								}
								else
								{
									strFormat = _T("MMM ") + strFormat;
								}

								bNeedFormat = FALSE;

								strDate.GetBuffer (_MAX_PATH);

								::GetDateFormat (LOCALE_USER_DEFAULT, 0, &st, 
									strFormat, (LPTSTR)(LPCTSTR)strDate, _MAX_PATH);

								strDate.ReleaseBuffer ();

								szSize = pDC->GetTextExtent (strDate);

								if (rectDayCaption.Width () - 4 < szSize.cx)
								{
									strFormat = _T("d");
									bNeedFormat = TRUE;
								}
							}

							if (bNeedFormat)
							{
								strDate.GetBuffer (_MAX_PATH);

								::GetDateFormat (LOCALE_USER_DEFAULT, 0, &st, 
									strFormat, (LPTSTR)(LPCTSTR)strDate, _MAX_PATH);

								strDate.ReleaseBuffer ();
							}
						}
					}
				}

				DrawCaption (pDC, rectDayCaption, strDate, FALSE, TRUE, 
					bAnotherMonth ? m_brDarkGray : m_brGray);
			}

			day += COleDateTimeSpan (1, 0, 0, 0);

			nIndex++;
		}
	}

	if (bBold && pOldFont != NULL)
	{
		pDC->SelectObject (pOldFont);
	}
}