BOOL CALLBACK NHRIPWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PNHRIPWindow data;

    data = (PNHRIPWindow)GetWindowLong(hWnd, GWL_USERDATA);
    switch (message)
    {
    case WM_INITDIALOG:
        /* set text control font */
        hdc = GetDC(hWnd);
        SendMessage(hWnd, WM_SETFONT,
                    (WPARAM)mswin_get_font(NHW_TEXT, ATR_NONE, hdc, FALSE), 0);
        ReleaseDC(hWnd, hdc);

        SetFocus(GetDlgItem(hWnd, IDOK));
        return FALSE;

    case WM_MSNH_COMMAND:
        onMSNHCommand(hWnd, wParam, lParam);
        break;

    case WM_PAINT:
    {
        int bitmap_offset;
        RECT clientrect;
        RECT textrect;
        HDC hdcBitmap;
        HANDLE OldBitmap;
        PAINTSTRUCT ps;
        HFONT OldFont;

        hdc = BeginPaint (hWnd, &ps);
        OldFont = SelectObject (hdc, mswin_get_font(NHW_TEXT, 0, hdc, FALSE));
        hdcBitmap = CreateCompatibleDC(hdc);
        SetBkMode (hdc, TRANSPARENT);
        GetClientRect (hWnd, &clientrect);
        textrect = clientrect;
        textrect.top += RIP_OFFSET_Y;
        textrect.left += RIP_OFFSET_X;
        textrect.right -= RIP_OFFSET_X;
        if (data->window_text)
        {
            DrawText (hdc, data->window_text, strlen(data->window_text), &textrect,
                      DT_LEFT | DT_NOPREFIX | DT_CALCRECT);
            DrawText (hdc, data->window_text, strlen(data->window_text), &textrect,
                      DT_LEFT | DT_NOPREFIX);
        }
        OldBitmap = SelectObject(hdcBitmap, GetNHApp()->bmpRip);
        SetBkMode (hdc, OPAQUE);
        bitmap_offset = (textrect.right - textrect.left - RIP_WIDTH) / 2;
        BitBlt (hdc, textrect.left + bitmap_offset, textrect.bottom, RIP_WIDTH,
                RIP_HEIGHT, hdcBitmap, 0, 0, SRCCOPY);
        SetBkMode (hdc, TRANSPARENT);
        if (data->rip_text)
        {
            textrect.left += RIP_GRAVE_X + bitmap_offset;
            textrect.top = textrect.bottom + RIP_GRAVE_Y;
            textrect.right = textrect.left + RIP_GRAVE_WIDTH;
            textrect.bottom = textrect.top + RIP_GRAVE_HEIGHT;
            DrawText (hdc, data->rip_text, strlen(data->rip_text), &textrect,
                      DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_WORDBREAK);
        }
        SelectObject (hdcBitmap, OldBitmap);
        SelectObject (hdc, OldFont);
        DeleteDC (hdcBitmap);
        EndPaint (hWnd, &ps);
    }
    break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            mswin_window_mark_dead(mswin_winid_from_handle(hWnd));
            if( GetNHApp()->hMainWnd==hWnd )
                GetNHApp()->hMainWnd=NULL;
            DestroyWindow(hWnd);
            SetFocus(GetNHApp()->hMainWnd);
            return TRUE;
        }
        break;

    case WM_CLOSE:
        /* if we get this here, we saved the bones so we can just force a quit */

        mswin_window_mark_dead(mswin_winid_from_handle(hWnd));
        if( GetNHApp()->hMainWnd==hWnd )
            GetNHApp()->hMainWnd=NULL;
        DestroyWindow(hWnd);
        SetFocus(GetNHApp()->hMainWnd);
        program_state.stopprint++;
        return TRUE;

    case WM_DESTROY:
        if( data ) {
            if( data->window_text ) free(data->window_text);
            if( data->rip_text ) free(data->rip_text);
            if (data->rip_bmp != NULL) DeleteObject(data->rip_bmp);
            free(data);
            SetWindowLong(hWnd, GWL_USERDATA, (LONG)0);
        }
        break;

    }
    return FALSE;
}