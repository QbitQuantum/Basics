BOOL CDxDatePickerDay::DrawDay(CDCHandle dc)
{
    // check this day item
    BOOL bThisMonthItem = FALSE;
    BOOL bNextMonthItem = FALSE;
    BOOL bPreviousMonthItem = FALSE;

    CDxMonthPicker* pControl = GetDatePicker();
    CDxDatePickerMonth* pMonth = GetMonth();

    COleDateTime dtDay = GetDate();
    CRect rcDay = GetRect();

    if (dtDay.GetYear() > pMonth->GetMonth().GetYear())
    {
        bNextMonthItem = TRUE;
    }
    else if (dtDay.GetYear() < pMonth->GetMonth().GetYear())
    {
        bPreviousMonthItem = TRUE;
    }
    else
    {
        // years the same
        if (dtDay.GetMonth() > pMonth->GetMonth().GetMonth())
            bNextMonthItem = TRUE;
        else if (dtDay.GetMonth() < pMonth->GetMonth().GetMonth())
            bPreviousMonthItem = TRUE;
        else // months the same
            bThisMonthItem = TRUE;
    }

    if (bPreviousMonthItem && !pMonth->GetShowDaysBefore())
        return FALSE;

    if (bNextMonthItem && !pMonth->GetShowDaysAfter())
        return FALSE;


    // apply settings to the DC
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
    dc.FillSolidRect(rcDay, GetSysColor(COLOR_WINDOW));

    // change default drawing metrics if day is selected
    if (pControl->IsSelected(dtDay))
    {
        dc.SetTextColor(GetSysColor(COLOR_WINDOW));
        dc.FillSolidRect(rcDay, GetSysColor(COLOR_WINDOWTEXT));
    }

    // make a text for drawing
    CString strText;
    strText.Format(_T("%i"), dtDay.GetDay());

    // draw item content
    {
        // draw item text
        HFONT hFontOld = (HFONT)dc.SelectFont(CDxFontManager::GetSingleton().GetFont(DUIF_DEFAULTFONT));
        dc.DrawText(strText, strText.GetLength(), &rcDay, DT_SINGLELINE | DT_VCENTER | DT_CENTER | DT_NOCLIP);
    }

    CRect rcFocus = rcDay;
    BOOL bToday = FALSE;

    // highlight today item
    if (IsToday(dtDay))
    {
        dc.Draw3dRect(rcDay, GetSysColor(COLOR_HIGHLIGHT), GetSysColor(COLOR_HIGHLIGHT));
        bToday = TRUE;
    }

    if (pControl->IsSelected(dtDay))
    {
        if (!bToday)
        {
            dc.SetTextColor(0);
            dc.SetBkColor(RGB(255, 255, 255));
            dc.DrawFocusRect(&rcFocus);
        }
        else
        {
            COLORREF clrFocus = GetSysColor(COLOR_HIGHLIGHT);
            clrFocus = clrFocus ^ RGB(255, 128, 128);

            rcFocus.DeflateRect(0, 0, 1, 1);

            CPen pen1;
            pen1.CreatePen(PS_DOT, 1, clrFocus);

            HPEN hOldPen = dc.SelectPen(pen1);

            dc.MoveTo(rcFocus.TopLeft());
            dc.LineTo(rcFocus.right, rcFocus.top);
            dc.LineTo(rcFocus.right, rcFocus.bottom);
            dc.LineTo(rcFocus.left, rcFocus.bottom);
            dc.LineTo(rcFocus.left, rcFocus.top);

            dc.SelectPen(hOldPen);
        }
    }

    return TRUE;
}