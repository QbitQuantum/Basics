HWND WINAPI DoCreateComboControl(HWND hwndParent) {

    HWND hwndCombo; 
    //TCITEM tie; 

    hwndCombo=CreateWindow(_T("COMBOBOX"), NULL, 
        WS_BORDER| WS_CHILD | WS_VISIBLE | WS_VSCROLL
        | CBS_DROPDOWN /*| CBS_LOWERCASE*/ | CBS_HASSTRINGS, 
        0, 0, 32 /*CW_USEDEFAULT*/, CW_USEDEFAULT, 
        hwndParent, NULL, g_hInst, NULL); 

    POINT pt;
    pt.x=6; pt.y=6;
    HWND hWndEdit = ChildWindowFromPoint(hwndCombo, pt); 

    WNDPROC OldEditWndProc = (WNDPROC)SetWindowLong(hWndEdit, GWL_WNDPROC,  (LONG)ComboSubClassProc); 
    SetWindowLong(hWndEdit, GWL_USERDATA, (LONG)OldEditWndProc);

    return hwndCombo;
}