void CBCGPPlannerViewMulti::OnDrawClient (CDC* pDC, const CRect& rect)
{
	ASSERT_VALID (pDC);

	CRect rectFill (rect);

//	const int nWeekStart = CBCGPPlannerManagerCtrl::GetFirstDayOfWeek () + 1;
	const int yOffset = m_nScrollOffset * m_nRowHeight;

	int nFirstWorkingHour   = GetFirstWorkingHour ();
	int nFirstWorkingMinute = GetFirstWorkingMinute ();
	int nLastWorkingHour    = GetLastWorkingHour ();
	int nLastWorkingMinute  = GetLastWorkingMinute ();

	const int nDays = GetViewDuration ();
	const int nRes  = (int) m_Resources.GetSize ();

	rectFill.OffsetRect (0, -yOffset);

	const int nMinuts = CBCGPPlannerView::GetTimeDeltaInMinuts (GetTimeDelta ());
	const int nCount = 60 / nMinuts;

	CPen     penHour[2];
	CPen     penHalfHour[2];

	for (int i = 0; i < 2; i++)
	{
		penHour[i].CreatePen (PS_SOLID, 0,
			GetHourLineColor (i == 0 /* Working */, TRUE));

		penHalfHour[i].CreatePen (PS_SOLID, 0, 
			GetHourLineColor (i == 0 /* Working */, FALSE));
	}

	XBCGPPlannerWorkingParameters WorkingParameters(this);
	COLORREF DefaultWorkingColorFill = visualManager->GetPlannerWorkColor ();

	OnFillPlanner (pDC, rect, FALSE /* Non-working */);

	CBrush brHilite (visualManager->GetPlannerSelectionColor (this));

	CPen penBlack (PS_SOLID, 0, visualManager->GetPlannerSeparatorColor (this));
	CPen* pOldPen = pDC->SelectObject (&penBlack);

	const int iStart = GetViewHourOffset();
	const int iEnd   = min (iStart + rect.Height () / m_nRowHeight, nCount * 24);

	COleDateTime dtStart (GetDateStart ());

	BOOL bShowSelection = !((m_Selection[0].GetHour ()   == 0 &&
							 m_Selection[0].GetMinute () == 0 &&
							 m_Selection[0].GetSecond () == 0 &&
							 m_Selection[1].GetHour ()   == 23 &&
							 m_Selection[1].GetMinute () == 59 &&
							 m_Selection[1].GetSecond () == 59) ||
							(m_Selection[1].GetHour ()   == 0 &&
							 m_Selection[1].GetMinute () == 0 &&
							 m_Selection[1].GetSecond () == 0 &&
							 m_Selection[0].GetHour ()   == 23 &&
							 m_Selection[0].GetMinute () == 59 &&
							 m_Selection[0].GetSecond () == 59));

	BOOL bIsDrawDuration = 
		(GetPlanner ()->GetDrawFlags () & BCGP_PLANNER_DRAW_VIEW_NO_DURATION) == 0;
	const int nDurationWidth = bIsDrawDuration ? BCGP_PLANNER_DURATION_BAR_WIDTH + 1 : 0;

	visualManager->PreparePlannerBackItem (FALSE, FALSE);

	const UINT nResourceID = GetCurrentResourceID ();

	int nDay = 0;
	for (nDay = 0; nDay < nDays; nDay++)
	{
		int nWD = dtStart.GetDayOfWeek ();
		BOOL bWeekEnd = nWD == 1 || nWD == 7;

		for (int i = 0; i < nRes; i++)
		{
			XResource& res = m_Resources[i];

			int nFirstHour   = nFirstWorkingHour;
			int nFirstMinute = nFirstWorkingMinute;
			int nLastHour    = nLastWorkingHour;
			int nLastMinute  = nLastWorkingMinute;

			if (res.m_WorkStart < res.m_WorkEnd)
			{
				nFirstHour   = res.m_WorkStart.GetHour ();
				nFirstMinute = res.m_WorkStart.GetMinute ();
				nLastHour    = res.m_WorkEnd.GetHour ();
				nLastMinute  = res.m_WorkEnd.GetMinute ();
			}

			int iWorkStart = nFirstHour * nCount + (int)(nFirstMinute / nMinuts);
			int iWorkEnd   = nLastHour * nCount + (int)(nLastMinute / nMinuts);

			rectFill = res.m_Rects[nDay];

			rectFill.left   += nDurationWidth;
			rectFill.bottom = rectFill.top + m_nRowHeight - 1;

			BCGP_PLANNER_WORKING_STATUS AllPeriodWorkingStatus = 
				GetWorkingPeriodParameters (res.m_ResourceID, dtStart + COleDateTimeSpan (0, 0, iStart * nMinuts, 0), dtStart + COleDateTimeSpan (0, 0, (iEnd * nMinuts) - 1, 59), WorkingParameters); 
			BCGP_PLANNER_WORKING_STATUS SpecificPeriodWorkingStatus = AllPeriodWorkingStatus; 

			for (int iStep = iStart; iStep < iEnd; iStep++)
			{
				BOOL bIsWork = TRUE;
				if (AllPeriodWorkingStatus == BCGP_PLANNER_WORKING_STATUS_UNKNOWN)
				{ // We don't know for the day -> we should see for the period
					COleDateTime CurrentPeriodStart = dtStart + COleDateTimeSpan (0, 0, iStep * nMinuts, 0);
					COleDateTime CurrentPeriodEnd = CurrentPeriodStart + COleDateTimeSpan (0, 0, nMinuts - 1, 59);
					SpecificPeriodWorkingStatus = GetWorkingPeriodParameters (res.m_ResourceID, CurrentPeriodStart, CurrentPeriodEnd, WorkingParameters); 
				}

				switch (SpecificPeriodWorkingStatus)
				{
				case BCGP_PLANNER_WORKING_STATUS_ISNOTWORKING: // not a working period
					bIsWork = FALSE;
					break;
				case BCGP_PLANNER_WORKING_STATUS_ISWORKING: // forced to be a working period (we do not control working hours)
					bIsWork = TRUE;
					break;
				case BCGP_PLANNER_WORKING_STATUS_ISNORMALWORKINGDAY: // regular working day without control of week-end (so it may be a week-end day !)
					bIsWork = (iWorkStart <= iStep && iStep < iWorkEnd);
					break;
				case BCGP_PLANNER_WORKING_STATUS_ISNORMALWORKINGDAYINWEEK: // regular working day in a week (the week end is not a working day)
				default: // could not determine if period is working or not so we calculate as "standard"
					bIsWork = !bWeekEnd && (iWorkStart <= iStep && iStep < iWorkEnd);
				}

				if (!IsDateInSelection (dtStart + 
					COleDateTimeSpan (0, (iStep * nMinuts) / 60, (iStep * nMinuts) % 60, 0)) ||
					!bShowSelection || res.m_ResourceID != nResourceID)
				{
					if (bIsWork)
					{
						if (WorkingParameters.m_clrWorking != CLR_DEFAULT)
						{
							CBrush brush(WorkingParameters.m_clrWorking);
							pDC->FillRect (rectFill, &brush);
						}
						else
						{
							OnFillPlanner (pDC, rectFill, TRUE /* Working */);
						}
					}
					else
					{ // IF non working color is different from default non working color -> we should draw it with new color..
						if ((WorkingParameters.m_clrNonWorking != CLR_DEFAULT) && 
							(WorkingParameters.m_clrNonWorking != DefaultWorkingColorFill))
						{
							CBrush brush(WorkingParameters.m_clrNonWorking);
							pDC->FillRect (rectFill, &brush);
						}
					}
				}
				else
				{
					pDC->FillRect (rectFill, &brHilite);
				}

				int nPenIndex = bIsWork ? 0 : 1;

				pDC->SelectObject (((iStep + 1) % nCount == 0) ? 
					&penHour [nPenIndex] : &penHalfHour [nPenIndex]);

				pDC->MoveTo (rectFill.left, rectFill.bottom);
				pDC->LineTo (rectFill.right, rectFill.bottom);

				rectFill.OffsetRect (0, m_nRowHeight);
			}
		}	

		dtStart += COleDateTimeSpan (1, 0, 0, 0);
	}

	pDC->SelectObject (&penBlack);

	if (bIsDrawDuration)
	{
		for (nDay = 0; nDay < nDays; nDay++)
		{
			for (int i = 0; i < nRes; i++)
			{
				CRect rectDurBar (m_Resources[i].m_Rects[nDay]);
				rectDurBar.right = rectDurBar.left + BCGP_PLANNER_DURATION_BAR_WIDTH;

				// Draw duration bar (at left):
				pDC->FillRect (rectDurBar, &globalData.brWindow);

				if (nDay > 0 || i > 0)
				{
					pDC->MoveTo (rectDurBar.left, rectDurBar.top);
					pDC->LineTo (rectDurBar.left, rectDurBar.bottom);
				}

				pDC->MoveTo (rectDurBar.right, rectDurBar.top);
				pDC->LineTo (rectDurBar.right, rectDurBar.bottom);
			}	
		}
	}
	else
	{
		for (nDay = 0; nDay < nDays; nDay++)
		{
			for (int i = 0; i < nRes; i++)
			{
				CRect rectDurBar (m_Resources[i].m_Rects[nDay]);

				if (nDay > 0 || i > 0)
				{
					pDC->MoveTo (rectDurBar.left, rectDurBar.top);
					pDC->LineTo (rectDurBar.left, rectDurBar.bottom);
				}
			}
		}
	}

	pDC->SelectObject (pOldPen);
}