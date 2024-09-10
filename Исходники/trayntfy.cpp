    LRESULT OnEraseBackground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        HDC hdc = (HDC) wParam;

        if (!TrayTheme)
        {
            bHandled = FALSE;
            return 0;
        }

        RECT rect;
        GetClientRect(&rect);
        if (IsThemeBackgroundPartiallyTransparent(TrayTheme, TNP_BACKGROUND, 0))
            DrawThemeParentBackground(m_hWnd, hdc, &rect);

        DrawThemeBackground(TrayTheme, hdc, TNP_BACKGROUND, 0, &rect, 0);

        return TRUE;
    }