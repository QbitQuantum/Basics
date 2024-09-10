wyBool  
TabMessage::Create()
{
    wyWChar* items[] = {
        _(L"All"),
        _(L"Queries with errors"),
        _(L"Queries with warnings"),
        _(L"Queries with errors/warnings"),
        _(L"Queries with result set"), 
        _(L"Queries without result set")
    };

    wyInt32 count, i, width = 0;
    HDC     hdc;
    HFONT   hfont = GetStockFont(DEFAULT_GUI_FONT);
    RECT    rect = {0};
    COMBOBOXINFO cbinfo = {0};

    CreateQueryMessageEdit(m_hwndparent, m_pmdi);
    m_hwndcombo = CreateWindowEx(0, L"combobox", L"", WS_CHILD | CBS_DROPDOWNLIST | WS_VISIBLE, 
        0, 0, 0, 0, m_hwndparent, (HMENU)IDC_TOOLCOMBO, (HINSTANCE)GetModuleHandle(0), NULL);
    SendMessage(m_hwndcombo, WM_SETFONT, (WPARAM)hfont, 0);
    cbinfo.cbSize = sizeof(COMBOBOXINFO);
    GetComboBoxInfo(m_hwndcombo, &cbinfo);
    SetWindowLongPtr(cbinfo.hwndList, GWLP_USERDATA, (LONG_PTR)this);
    //m_origlistproc = (WNDPROC)SetWindowLongPtr(cbinfo.hwndList, GWLP_WNDPROC, (LONG)ComboListProc);
   
    count = sizeof(items)/sizeof(items[0]);
    hdc = GetDC(m_hwndcombo);
    hfont = SelectFont(hdc, hfont);

    for(i = 0; i < count; ++i)
    {
        SendMessage(m_hwndcombo, CB_ADDSTRING, 0, (LPARAM)items[i]);
        DrawText(hdc, items[i], -1, &rect, DT_CALCRECT | DT_NOPREFIX);

        if(rect.right > width)
        {
            width = rect.right;
        }
    }

    SelectFont(hdc, hfont);
    ReleaseDC(m_hwndcombo, hdc);
    SendMessage(m_hwndcombo, CB_SETCURSEL, 0, 0);
    GetWindowRect(m_hwndcombo, &rect);
    SetWindowPos(m_hwndcombo, NULL, 0, 0, width + (cbinfo.rcButton.right - cbinfo.rcButton.left) + 10, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE);
    //SendMessage(m_hwndcombo, CB_SETDROPPEDWIDTH, width + 10, 0);
	return wyTrue;
}