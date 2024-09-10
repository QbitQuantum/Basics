static void GB_draw(HTHEME theme, HWND hwnd, HDC hDC, ButtonState drawState, UINT dtFlags, BOOL focused)
#endif
{
    static const int states[] = { GBS_NORMAL, GBS_NORMAL, GBS_NORMAL, GBS_DISABLED, GBS_NORMAL };

    RECT bgRect, textRect, contentRect;
    int state = states[ drawState ];
    WCHAR *text = get_button_text(hwnd);
    LOGFONTW lf;
    HFONT font, hPrevFont = NULL;
    BOOL created_font = FALSE;
#ifdef __REACTOS__ /* r74406 */
    HWND parent;
    HBRUSH hBrush;
    RECT clientRect;
#endif

    HRESULT hr = GetThemeFont(theme, hDC, BP_GROUPBOX, state, TMT_FONT, &lf);
    if (SUCCEEDED(hr)) {
        font = CreateFontIndirectW(&lf);
        if (!font)
            TRACE("Failed to create font\n");
        else {
            hPrevFont = SelectObject(hDC, font);
            created_font = TRUE;
        }
    } else {
#ifdef __REACTOS__ /* r73885 */
        font = get_button_font(hwnd);
#else
        font = (HFONT)SendMessageW(hwnd, WM_GETFONT, 0, 0);
#endif
        hPrevFont = SelectObject(hDC, font);
    }

    GetClientRect(hwnd, &bgRect);
    textRect = bgRect;

    if (text)
    {
        SIZE textExtent;
        GetTextExtentPoint32W(hDC, text, lstrlenW(text), &textExtent);
        bgRect.top += (textExtent.cy / 2);
        textRect.left += 10;
        textRect.bottom = textRect.top + textExtent.cy;
        textRect.right = textRect.left + textExtent.cx + 4;

        ExcludeClipRect(hDC, textRect.left, textRect.top, textRect.right, textRect.bottom);
    }

    GetThemeBackgroundContentRect(theme, hDC, BP_GROUPBOX, state, &bgRect, &contentRect);
    ExcludeClipRect(hDC, contentRect.left, contentRect.top, contentRect.right, contentRect.bottom);

#ifdef __REACTOS__ /* r73885 & r74149 */
    if (prfFlag == 0)
    {
        if (IsThemeBackgroundPartiallyTransparent(theme, BP_GROUPBOX, state))
            DrawThemeParentBackground(hwnd, hDC, NULL);
    }
#else
    if (IsThemeBackgroundPartiallyTransparent(theme, BP_GROUPBOX, state))
        DrawThemeParentBackground(hwnd, hDC, NULL);
#endif

#ifdef __REACTOS__ /* r74406 */
    parent = GetParent(hwnd);
    if (!parent) parent = hwnd;
    hBrush = (HBRUSH)SendMessageW(parent, WM_CTLCOLORSTATIC,
                                  (WPARAM)hDC, (LPARAM)hwnd);
    if (!hBrush) /* did the app forget to call defwindowproc ? */
        hBrush = (HBRUSH)DefWindowProcW(parent, WM_CTLCOLORSTATIC,
                                       (WPARAM)hDC, (LPARAM)hwnd );
    GetClientRect(hwnd, &clientRect);
    FillRect( hDC, &clientRect, hBrush );
#endif

    DrawThemeBackground(theme, hDC, BP_GROUPBOX, state, &bgRect, NULL);

    SelectClipRgn(hDC, NULL);

    if (text)
    {
        InflateRect(&textRect, -2, 0);
        DrawThemeText(theme, hDC, BP_GROUPBOX, state, text, lstrlenW(text), 0, 0, &textRect);
        HeapFree(GetProcessHeap(), 0, text);
    }

    if (created_font) DeleteObject(font);
    if (hPrevFont) SelectObject(hDC, hPrevFont);
}