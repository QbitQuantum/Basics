static VOID
MonSelPaintMonitor(IN OUT PMONITORSELWND infoPtr,
                   IN HDC hDC,
                   IN DWORD Index,
                   IN OUT PRECT prc,
                   IN COLORREF crDefFontColor,
                   IN BOOL bHideNumber)
{
    HFONT hFont, hPrevFont;
    COLORREF crPrevText;

    if ((INT)Index == infoPtr->SelectedMonitor)
    {
        FillRect(hDC,
                 prc,
                 (HBRUSH)(COLOR_HIGHLIGHT + 1));

        if (infoPtr->HasFocus && !(infoPtr->UIState & UISF_HIDEFOCUS))
        {
            /* NOTE: We need to switch the text color to the default, because
                     DrawFocusRect draws a solid line if the text is white! */

            crPrevText = SetTextColor(hDC,
                                      crDefFontColor);

            DrawFocusRect(hDC,
                          prc);

            SetTextColor(hDC,
                         crPrevText);
        }
    }

    InflateRect(prc,
                -infoPtr->SelectionFrame.cx,
                -infoPtr->SelectionFrame.cy);

    Rectangle(hDC,
              prc->left,
              prc->top,
              prc->right,
              prc->bottom);

    InflateRect(prc,
                -1,
                -1);

    if (!bHideNumber)
    {
        hFont = MonSelGetMonitorFont(infoPtr,
                                     hDC,
                                     Index);
        if (hFont != NULL)
        {
            hPrevFont = SelectObject(hDC,
                                     hFont);

            DrawText(hDC,
                     infoPtr->Monitors[Index].szCaption,
                     -1,
                     prc,
                     DT_VCENTER | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);

            SelectObject(hDC,
                         hPrevFont);
        }
    }

    if (infoPtr->MonitorInfo[Index].Flags & MSL_MIF_DISABLED)
    {
        InflateRect(prc,
                    1,
                    1);

        MonSelDrawDisabledRect(infoPtr,
                               hDC,
                               prc);
    }
}