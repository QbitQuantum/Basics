static void test_wiznavigation(void)
{
    HPROPSHEETPAGE hpsp[4];
    PROPSHEETPAGEA psp[4];
    PROPSHEETHEADERA psh;
    HWND hdlg, control;
    LONG_PTR controlID;
    DWORD style;
    LRESULT defidres;
    BOOL hwndtoindex_supported = TRUE;
    const INT nextID = 12324;
    const INT backID = 12323;
    HHOOK hook;

    /* set up a hook proc in order to subclass the main dialog early on */
    hook = SetWindowsHookExW( WH_CBT, hook_proc, NULL, GetCurrentThreadId() );

    /* create the property sheet pages */
    memset(psp, 0, sizeof(PROPSHEETPAGEA) * 4);

    psp[0].dwSize = sizeof(PROPSHEETPAGEA);
    psp[0].hInstance = GetModuleHandleA(NULL);
    U(psp[0]).pszTemplate = (LPCSTR)MAKEINTRESOURCE(IDD_PROP_PAGE_INTRO);
    psp[0].pfnDlgProc = nav_page_proc;
    hpsp[0] = CreatePropertySheetPageA(&psp[0]);

    psp[1].dwSize = sizeof(PROPSHEETPAGEA);
    psp[1].hInstance = GetModuleHandleA(NULL);
    U(psp[1]).pszTemplate = (LPCSTR)MAKEINTRESOURCE(IDD_PROP_PAGE_EDIT);
    psp[1].pfnDlgProc = nav_page_proc;
    hpsp[1] = CreatePropertySheetPageA(&psp[1]);

    psp[2].dwSize = sizeof(PROPSHEETPAGEA);
    psp[2].hInstance = GetModuleHandleA(NULL);
    U(psp[2]).pszTemplate = (LPCSTR)MAKEINTRESOURCE(IDD_PROP_PAGE_RADIO);
    psp[2].pfnDlgProc = nav_page_proc;
    hpsp[2] = CreatePropertySheetPageA(&psp[2]);

    psp[3].dwSize = sizeof(PROPSHEETPAGEA);
    psp[3].hInstance = GetModuleHandleA(NULL);
    U(psp[3]).pszTemplate = (LPCSTR)MAKEINTRESOURCE(IDD_PROP_PAGE_EXIT);
    psp[3].pfnDlgProc = nav_page_proc;
    hpsp[3] = CreatePropertySheetPageA(&psp[3]);

    /* set up the property sheet dialog */
    memset(&psh, 0, sizeof(psh));
    psh.dwSize = PROPSHEETHEADERA_V1_SIZE;
    psh.dwFlags = PSH_MODELESS | PSH_WIZARD;
    psh.pszCaption = "A Wizard";
    psh.nPages = 4;
    psh.hwndParent = GetDesktopWindow();
    U3(psh).phpage = hpsp;
    hdlg = (HWND)PropertySheetA(&psh);
    ok(hdlg != INVALID_HANDLE_VALUE, "got invalid handle %p\n", hdlg);

    ok(active_page == 0, "Active page should be 0. Is: %d\n", active_page);

    style = GetWindowLongA(hdlg, GWL_STYLE) & ~(DS_CONTEXTHELP|WS_SYSMENU);
    ok(style == (WS_POPUP|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CAPTION|
                 DS_MODALFRAME|DS_SETFONT|DS_3DLOOK),
       "got unexpected style: %x\n", style);

    control = GetFocus();
    controlID = GetWindowLongPtrA(control, GWLP_ID);
    ok(controlID == nextID, "Focus should have been set to the Next button. Expected: %d, Found: %ld\n", nextID, controlID);

    /* simulate pressing the Next button */
    SendMessageA(hdlg, PSM_PRESSBUTTON, PSBTN_NEXT, 0);
    if (!active_page) hwndtoindex_supported = FALSE;
    if (hwndtoindex_supported)
        ok(active_page == 1, "Active page should be 1 after pressing Next. Is: %d\n", active_page);

    control = GetFocus();
    controlID = GetWindowLongPtrA(control, GWLP_ID);
    ok(controlID == IDC_PS_EDIT1, "Focus should be set to the first item on the second page. Expected: %d, Found: %ld\n", IDC_PS_EDIT1, controlID);

    defidres = SendMessageA(hdlg, DM_GETDEFID, 0, 0);
    ok(defidres == MAKELRESULT(nextID, DC_HASDEFID), "Expected default button ID to be %d, is %d\n", nextID, LOWORD(defidres));

    /* set the focus to the second edit box on this page */
    SetFocus(GetNextDlgTabItem(hdlg, control, FALSE));

    /* press next again */
    SendMessageA(hdlg, PSM_PRESSBUTTON, PSBTN_NEXT, 0);
    if (hwndtoindex_supported)
        ok(active_page == 2, "Active page should be 2 after pressing Next. Is: %d\n", active_page);

    control = GetFocus();
    controlID = GetWindowLongPtrA(control, GWLP_ID);
    ok(controlID == IDC_PS_RADIO1, "Focus should have been set to item on third page. Expected: %d, Found %ld\n", IDC_PS_RADIO1, controlID);

    /* back button */
    SendMessageA(hdlg, PSM_PRESSBUTTON, PSBTN_BACK, 0);
    if (hwndtoindex_supported)
        ok(active_page == 1, "Active page should be 1 after pressing Back. Is: %d\n", active_page);

    control = GetFocus();
    controlID = GetWindowLongPtrA(control, GWLP_ID);
    ok(controlID == IDC_PS_EDIT1, "Focus should have been set to the first item on second page. Expected: %d, Found %ld\n", IDC_PS_EDIT1, controlID);

    defidres = SendMessageA(hdlg, DM_GETDEFID, 0, 0);
    ok(defidres == MAKELRESULT(backID, DC_HASDEFID), "Expected default button ID to be %d, is %d\n", backID, LOWORD(defidres));

    /* press next twice */
    SendMessageA(hdlg, PSM_PRESSBUTTON, PSBTN_NEXT, 0);
    if (hwndtoindex_supported)
        ok(active_page == 2, "Active page should be 2 after pressing Next. Is: %d\n", active_page);
    SendMessageA(hdlg, PSM_PRESSBUTTON, PSBTN_NEXT, 0);
    if (hwndtoindex_supported)
        ok(active_page == 3, "Active page should be 3 after pressing Next. Is: %d\n", active_page);
    else
        active_page = 3;

    control = GetFocus();
    controlID = GetWindowLongPtrA(control, GWLP_ID);
    ok(controlID == nextID, "Focus should have been set to the Next button. Expected: %d, Found: %ld\n", nextID, controlID);

    /* try to navigate away, but shouldn't be able to */
    SendMessageA(hdlg, PSM_PRESSBUTTON, PSBTN_BACK, 0);
    ok(active_page == 3, "Active page should still be 3 after pressing Back. Is: %d\n", active_page);

    defidres = SendMessageA(hdlg, DM_GETDEFID, 0, 0);
    ok(defidres == MAKELRESULT(nextID, DC_HASDEFID), "Expected default button ID to be %d, is %d\n", nextID, LOWORD(defidres));

    DestroyWindow(hdlg);
    UnhookWindowsHookEx( hook );
}