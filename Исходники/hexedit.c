//
//	Main Window message handler
//
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    NMHDR *hdr;
    POINT pt;
    RECT  rect;
    HMENU hMenu;
    HWND hwndHV = GetActiveHexView(hwnd);//g_hwndHexView;
    int i;
    TCITEM tci;

    MAINWND *mainWnd = (MAINWND *)GetWindowLongPtr(hwnd, 0);

    switch(msg)
    {
    case WM_NCCREATE:

        if((mainWnd = malloc(sizeof(MAINWND))) == 0)
            return FALSE;

        SetWindowLongPtr(hwnd, 0, (LONG_PTR)mainWnd);
        ZeroMemory(mainWnd, sizeof(MAINWND));
        return TRUE;

    case WM_NCDESTROY:
        free(mainWnd);
        return 0;

    case WM_CREATE:

        g_hwndMain = hwnd;

        SetWindowIcon(hwnd, IDI_APP);

        // create a child-window EDIT control
        //g_hwndHexView	= CreateHexViewCtrl(hwnd);
        g_hwndTabView	= CreateWindow(WC_TABVIEW, TEXT(""), WS_CHILD|WS_VISIBLE,0,0,0,0,hwnd, 0, g_hInstance, 0);
        g_hwndStatusBar = CreateStatusBar(hwnd);

        SendMessage(g_hwndTabView, TCM_SETITEMSIZE, 0, MAKELPARAM(150, 0));

        SetStatusBarParts(g_hwndStatusBar);

        hwndHV = g_hwndHexView;

        mainWnd->hwndMain		= hwnd;
        mainWnd->hwndStatusBar	= g_hwndStatusBar;
        mainWnd->hwndTabView	= g_hwndTabView;

        CreateToolTip(g_hwndHexView);

//		g_hwndDock[0] = CreateDockWnd(&dock, hwnd, TEXT("Toolbar"));



        //g_hwndToolbar   = InitToolbar(hwnd);
        //g_hwndSearchBar = CreateSearchBar(hwnd);
        //g_hwndTypeView  = CreateTypeView(hwnd);


        SetFocus(hwndHV);


        // tell windows that we can handle drag+drop'd files
        DragAcceptFiles(hwnd, TRUE);

        UpdateRecentMenu(GetSubMenu(GetMenu(hwnd), 0));

        SetTimer(hwnd, 0xdeadbeef, 1000, 0);

        return TRUE;

    case WM_TIMER:
        if(wParam == 0xdeadbeef)
        {
            KillTimer(hwnd, wParam);
            //FirstTimeOptions(hwnd);
        }
        return 0;

    case WM_DROPFILES:

        // get the screen coordinates of the drop-location
        if(DragQueryPoint((HDROP)wParam, &pt))
            ClientToScreen(hwnd, &pt);

        GetWindowRect(hwndHV, &rect);

        // drop anywhere *except* the hexview, as that does D&D itself
        if(!PtInRect(&rect, pt))
        {
            HandleDropFiles(hwnd, (HDROP)wParam);
        }

        //CreateToolTip(mainWnd->hwndTabView);
        return 0;

    case WM_ENABLE:
        EnableWindow(g_hwndSearch, (BOOL)wParam);
        EnableWindow(g_hwndGoto, (BOOL)wParam);
        return 0;

    case WM_CONTEXTMENU:
        if((HWND)wParam == DockWnd_GetWindow(hwnd, DWID_TYPEVIEW))
        {
            HMENU hMenu = GetSubMenu(LoadMenu(g_hInstance, MAKEINTRESOURCE(IDR_TYPECONTEXT)), 0);
            UINT  u;

            MenuCheckMark(hMenu, IDM_TYPEVIEW_HEX, g_fDisplayHex);
            MenuCheckMark(hMenu, IDM_TYPEVIEW_BIGENDIAN, g_fDisplayBigEndian);
            u = TrackPopupMenu(hMenu, TPM_RETURNCMD, (short)LOWORD(lParam), (short)HIWORD(lParam), 0, hwnd, 0);

            SendMessage(DockWnd_GetContents(hwnd, DWID_TYPEVIEW), WM_COMMAND, u, 0);
        }

        break;

    case WM_COMMAND:
        return HexEdit_OnCommand(hwnd, LOWORD(wParam), HIWORD(wParam), (HWND)lParam);

    case WM_NOTIFY:
        hdr = (NMHDR *)lParam;
        if(hdr->hwndFrom == hwndHV)
            return HexViewNotifyHandler(mainWnd, hwnd, hdr);
        else
            return HexEdit_OnNotify(mainWnd, hwnd, (UINT)wParam, (NMHDR *)lParam);

    case WM_CLOSE:

        tci.mask = TCIF_PARAM;

        for(i = 0; (hwndHV = EnumHexView(hwnd, i)) != NULL; )
        {
            UINT uAnswer = HexFileCloseNotify(hwnd, hwndHV);

            if(uAnswer == IDCANCEL)
            {
                return 0;
            }
            else if(uAnswer == IDNO)
            {
                SaveHighlights(hwndHV);
                TabCtrl_DeleteItem(mainWnd->hwndTabView, i);
            }
            else
            {
                i++;
            }
        }

        // save settings *before* we destroy anything!
        DockWnd_SaveSettings(hwnd);

        // shut program down
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        DestroyWindow(hwndHV);

        //
        PostQuitMessage(0);
        return 0;

    case WM_SETFOCUS:
        SetFocus(hwndHV);
        return 0;

    case WM_SIZE:

        MainWndSize(mainWnd, LOWORD(lParam), HIWORD(lParam));
        UpdateStatusbar(mainWnd->hwndStatusBar);

        return 0;

    case WM_INITMENUPOPUP:
        hMenu = (HMENU)wParam;//GetMenu(hwnd);

        MenuCheckMark(hMenu, IDM_VIEW_TOOLBAR, DockWnd_IsOpen(hwnd, DWID_TOOLBAR));
        MenuCheckMark(hMenu, IDM_TOOLS_TYPEVIEW, DockWnd_IsOpen(hwnd, DWID_TYPEVIEW));
        MenuCheckMark(hMenu, IDM_TOOLS_SEARCHBAR, DockWnd_IsOpen(hwnd, DWID_SEARCHBAR));

        CheckMenuRadioItem(hMenu, IDM_VIEW_HEX, IDM_VIEW_BIN,
                           IDM_VIEW_HEX + (HexView_GetStyle(hwndHV) & HVS_FORMAT_MASK),
                           MF_BYCOMMAND);

        {   int look[32] = { 0, 0, 1, 0, 2 };
            CheckMenuRadioItem(hMenu, IDM_GROUP_BYTE, IDM_GROUP_DWORD,
                               IDM_GROUP_BYTE + look[HexView_GetGrouping(hwndHV)],
                               MF_BYCOMMAND);
        }

        {
            size_w selsize;
            UINT   edmode  = HexView_GetEditMode(hwndHV);
            BOOL   cftext  = IsClipboardFormatAvailable(CF_TEXT);
            BOOL   canundo = HexView_CanUndo(hwndHV);
            BOOL   canredo = HexView_CanRedo(hwndHV);

            HexView_GetSelSize(hwndHV, &selsize);

            //hMenu = GetSubMenu(GetMenu(hwnd), 1);

            EnableMenuCmdItem(hMenu, IDM_EDIT_UNDO,  canundo);
            EnableMenuCmdItem(hMenu, IDM_EDIT_REDO,  canredo);
            EnableMenuCmdItem(hMenu, IDM_EDIT_CUT,  selsize > 0 && edmode == HVMODE_INSERT);
            EnableMenuCmdItem(hMenu, IDM_EDIT_COPY, selsize > 0);
            EnableMenuCmdItem(hMenu, IDM_EDIT_COPYAS, selsize > 0);
            EnableMenuCmdItem(hMenu, IDM_EDIT_PASTE, cftext && edmode != HVMODE_READONLY  );
            EnableMenuCmdItem(hMenu, IDM_EDIT_PASTESPECIAL, edmode != HVMODE_READONLY  );
            EnableMenuCmdItem(hMenu, IDM_EDIT_DELETE, selsize > 0 && edmode != HVMODE_READONLY );

            EnableMenuCmdItem(hMenu, IDM_EDIT_REVERSE, selsize > 0 && edmode != HVMODE_READONLY );
            EnableMenuCmdItem(hMenu, IDM_TOOLS_TRANSFORM, selsize > 0 && edmode != HVMODE_READONLY );

            EnableMenuCmdItem(hMenu, IDM_FILE_REVERT, canundo || canredo);
        }

        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}