// Function to create Combo Box as child of Custom Combo Box
wyBool
CCustomComboBox::CreateCtrls(HWND hwnd, LPARAM lParam)
{
    CREATESTRUCT    *ctst = (CREATESTRUCT *)lParam;
    wyInt32         ret = 0;
    DWORD           style = CBS_DROPDOWN | CBS_SORT | CBS_HASSTRINGS | WS_VSCROLL | WS_TABSTOP | WS_CHILD | WS_CLIPCHILDREN;
    HFONT           hfont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    m_id            = (wyInt32)ctst->hMenu;
    m_hwndParent    = ctst->hwndParent;
    m_hwnd          = hwnd;

    if((ctst->style &  CBS_OWNERDRAWFIXED))
        style |=  CBS_OWNERDRAWFIXED;
    m_hwndCombo     = CreateWindowExW(NULL, WC_COMBOBOX, NULL, 
                                style, 
                                0, 0, ctst->cx,ctst->cy, 
                                hwnd, (HMENU)IDC_COMBOCUSTOM, GetModuleHandle(NULL), 0);
    
    if(m_hwndCombo == NULL)
        return wyFalse;

    SendMessage(m_hwndCombo, WM_SETFONT, (WPARAM)hfont, (LPARAM)TRUE);
    
    ShowWindow(m_hwndCombo, SW_SHOW);

    ret = GetComboBoxInfo(m_hwndCombo, &m_cbif);

    m_editRect.bottom   = m_cbif.rcItem.bottom;
    m_editRect.right    = m_cbif.rcItem.right;
    m_editRect.left     = m_cbif.rcItem.left;
    m_editRect.top      = m_cbif.rcItem.top;
    
    if(ctst->style & WS_DISABLED)
    {
        SendMessage(hwnd, WM_ENABLE, FALSE, NULL);
    }

    SetWindowLongPtr(m_hwndCombo, GWLP_USERDATA, (LONG_PTR) this);
    m_origComboCtrlProc = (WNDPROC)SetWindowLongPtr(m_hwndCombo, GWLP_WNDPROC, (LONG_PTR) CCustomComboBox::ComboCtrlProc);
    
    SetWindowLongPtr(m_cbif.hwndItem, GWLP_USERDATA, (LONG_PTR)this);
    m_origEditCtrlProc = (WNDPROC)SetWindowLongPtr(m_cbif.hwndItem, GWLP_WNDPROC, (LONG_PTR) CCustomComboBox::EditCtrlProc);

    return wyTrue;
}