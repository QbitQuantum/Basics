LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    RECT rcClient;                       // The parent window's client area.
    static HMENU hMainMenu, hFileMenu;
    static HWND hSearchButton;
    int i;

    OPENFILENAME ofn;
    TCHAR szFileName[256] = "";

    static struct {
        TCHAR *name;
        int width;
    } columns[] = {
        { TEXT("Номер телефона:"), 100},
        { TEXT("Фамилия:"), 100},
        { TEXT("Имя:"), 100},
        { TEXT("Отчество:"), 100},
        { TEXT("Улица:"), 150},
        { TEXT("Дом:"), 100},
        { TEXT("Корпус:"), 100},
        { TEXT("Квартира:"), 100}
    };
    const int ColumnsCount = _countof(columns);

    switch (message)
    {
    case WM_CREATE:
        LoadDatabaseDLL();
        hMainMenu=CreateMenu();
        hFileMenu=CreatePopupMenu();
        i=0;
        CreateMenuItem(hFileMenu,"&Load database",i++,ID_BUTTONLOADDB,NULL,FALSE,MFT_STRING);
        CreateMenuItem(hFileMenu,"&Show database",i++,ID_BUTTONSHOWDB,NULL,FALSE,MFT_STRING);
        CreateMenuItem(hFileMenu,"&Exit",i++,IDM_EXIT,NULL,FALSE,MFT_STRING);
        i=0;
        CreateMenuItem(hMainMenu,"&File",i++,0,hFileMenu,FALSE,MFT_STRING);
        SetMenu(hWnd,hMainMenu);
        DrawMenuBar(hWnd);

        GetClientRect (hWnd, &rcClient);
        hListView = CreateWindowEx(
                        WS_EX_STATICEDGE,
                        WC_LISTVIEW,
                        NULL,
                        WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_EDITLABELS,
                        0, 0,
                        rcClient.right, rcClient.bottom-100,
                        hWnd, NULL, hInst, NULL);
        ListView_SetExtendedListViewStyle(hListView,LVS_EX_FULLROWSELECT);
        //adding columns
        for (int i=0; i<ColumnsCount; i++)
        {
            AddColumnToListView(hListView, columns[i].name, i, columns[i].width);
        }

        hPhoneLabel = CreateWindowEx( WS_EX_TRANSPARENT, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU , 5, 400, 65, 25, hWnd, hMainMenu, hInst, NULL);
        SendMessage(hPhoneLabel, WM_SETTEXT, NULL, (LPARAM) "Телефон:");
        hLastNameLabel = CreateWindowEx( WS_EX_TRANSPARENT, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU , 90, 400, 100, 25, hWnd, hMainMenu, hInst, NULL);
        SendMessage(hLastNameLabel, WM_SETTEXT, NULL, (LPARAM) "Фамилия:");
        hNameLabel = CreateWindowEx( WS_EX_TRANSPARENT, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU , 190, 400, 100, 25, hWnd, hMainMenu, hInst, NULL);
        SendMessage(hNameLabel, WM_SETTEXT, NULL, (LPARAM) "Имя:");
        hPatronymLabel = CreateWindowEx( WS_EX_TRANSPARENT, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU , 290, 400, 100, 25, hWnd, hMainMenu, hInst, NULL);
        SendMessage(hPatronymLabel, WM_SETTEXT, NULL, (LPARAM) "Отчество:");
        hStreetLabel = CreateWindowEx( WS_EX_TRANSPARENT, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU , 390, 400, 150, 25, hWnd, hMainMenu, hInst, NULL);
        SendMessage(hStreetLabel, WM_SETTEXT, NULL, (LPARAM) "Улица");
        hHouseLabel = CreateWindowEx( WS_EX_TRANSPARENT, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU , 540, 400, 50, 25, hWnd, hMainMenu, hInst, NULL);
        SendMessage(hHouseLabel, WM_SETTEXT, NULL, (LPARAM) "Дом");
        hHousingLabel = CreateWindowEx( WS_EX_TRANSPARENT, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU , 590, 400, 60, 25, hWnd, hMainMenu, hInst, NULL);
        SendMessage(hHousingLabel, WM_SETTEXT, NULL, (LPARAM)"Корпус:");
        hApartmentLabel = CreateWindowEx( WS_EX_TRANSPARENT, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU , 650, 400, 30, 25, hWnd, hMainMenu, hInst, NULL);
        SendMessage(hApartmentLabel, WM_SETTEXT, NULL, (LPARAM) "кв:");

        hPhoneEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,	3, 425, 83, 25,	hWnd, (HMENU)(101),	hInst, NULL);
        hLastNameEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,	90, 425, 98, 25,	hWnd, (HMENU)(101),	hInst, NULL);
        hNameEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,	190, 425, 98, 25,	hWnd, (HMENU)(101),	hInst, NULL);
        hPatronymEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,	290, 425, 98, 25,	hWnd, (HMENU)(101),	hInst, NULL);
        hStreetEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,	390, 425, 148, 25,	hWnd, (HMENU)(101),	hInst, NULL);
        hHouseEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,	540, 425, 98, 25,	hWnd, (HMENU)(101),	hInst, NULL);
        hHousingEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,	590, 425, 58, 25,	hWnd, (HMENU)(101),	hInst, NULL);
        hApartmentEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,	650, 425, 28, 25,	hWnd, (HMENU)(101),	hInst, NULL);

        hSearchButton = CreateWindowEx(
                            WS_EX_STATICEDGE,
                            WC_BUTTON,
                            NULL,
                            WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_EDITLABELS,
                            690, 425,
                            50, 25,
                            hWnd, NULL, hInst, NULL);
        SendMessage(hSearchButton, WM_SETTEXT, NULL, (LPARAM) "Поиск");

        ShowWindow(hWnd, NULL);
        UpdateWindow(hWnd);
        break;
    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case BN_CLICKED:
            if ((HWND)lParam == hSearchButton)
                SearchDB(hWnd, hListView);
            break;
        case ID_BUTTONLOADDB:
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFilter = "Text files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
            ofn.lpstrFile = szFileName;
            ofn.nMaxFile = MAX_PATH;
            ofn.lpstrTitle = "Open File";
            ofn.Flags = OFN_PATHMUSTEXIST;
            ofn.lpstrDefExt = "txt";

            if(GetOpenFileName(&ofn))
            {
                LoadDB(szFileName,hWnd);
            }
            InvalidateRect(hWnd,NULL,TRUE);
            UpdateWindow(hWnd);

            break;
        case ID_BUTTONSHOWDB:
            ShowDB(hWnd);
            break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code here...
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}