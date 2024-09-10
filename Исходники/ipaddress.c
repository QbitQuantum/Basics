static LRESULT IPADDRESS_Draw (const IPADDRESS_INFO *infoPtr, HDC hdc)
{
    static const WCHAR dotW[] = { '.', 0 };
    RECT rect, rcPart;
    COLORREF bgCol, fgCol;
    HTHEME theme;
    int i, state = ETS_NORMAL;

    TRACE("\n");

    GetClientRect (infoPtr->Self, &rect);

    theme = OpenThemeData(infoPtr->Self, WC_EDITW);

    if (theme) {
        DWORD dwStyle = GetWindowLongW (infoPtr->Self, GWL_STYLE);

        if (!infoPtr->Enabled)
            state = ETS_DISABLED;
        else if (dwStyle & ES_READONLY)
            state = ETS_READONLY;
        else if (GetFocus() == infoPtr->Self)
            state = ETS_FOCUSED;

        GetThemeColor(theme, EP_EDITTEXT, state, TMT_FILLCOLOR, &bgCol);
        GetThemeColor(theme, EP_EDITTEXT, state, TMT_TEXTCOLOR, &fgCol);

        if (IsThemeBackgroundPartiallyTransparent (theme, EP_EDITTEXT, state))
            DrawThemeParentBackground(infoPtr->Self, hdc, &rect);
        DrawThemeBackground (theme, hdc, EP_EDITTEXT, state, &rect, 0);
    } else {
        if (infoPtr->Enabled) {
            bgCol = comctl32_color.clrWindow;
            fgCol = comctl32_color.clrWindowText;
        } else {
            bgCol = comctl32_color.clr3dFace;
            fgCol = comctl32_color.clrGrayText;
        }

        FillRect (hdc, &rect, (HBRUSH)(DWORD_PTR)(bgCol+1));
        DrawEdge (hdc, &rect, EDGE_SUNKEN, BF_RECT | BF_ADJUST);
    }
    
    SetBkColor  (hdc, bgCol);
    SetTextColor(hdc, fgCol);

    for (i = 0; i < 3; i++) {
        GetWindowRect (infoPtr->Part[i].EditHwnd, &rcPart);
        MapWindowPoints( 0, infoPtr->Self, (POINT *)&rcPart, 2 );
        rect.left = rcPart.right;
        GetWindowRect (infoPtr->Part[i+1].EditHwnd, &rcPart);
        MapWindowPoints( 0, infoPtr->Self, (POINT *)&rcPart, 2 );
        rect.right = rcPart.left;

        if (theme)
            DrawThemeText(theme, hdc, EP_EDITTEXT, state, dotW, 1, DT_SINGLELINE | DT_CENTER | DT_BOTTOM, 0, &rect);
        else
            DrawTextW(hdc, dotW, 1, &rect, DT_SINGLELINE | DT_CENTER | DT_BOTTOM);
    }

    if (theme)
        CloseThemeData(theme);

    return 0;
}