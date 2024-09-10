int SameGameProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case MSG_CREATE:
    {
        RECT rcClient;
        MENUBUTTONITEM mbi;

        GetClientRect (hWnd, &rcClient);

        CreateWindow (CTRL_STATIC, SM_ST_SCENARIO, 
                    WS_CHILD | WS_VISIBLE | SS_RIGHT, 0,
                    0, rcClient.bottom - GetSysCharHeight () - 4,
                    100, GetSysCharHeight () + 4, hWnd, 0);

        hwnd_menu = CreateWindow ("menubutton",
                     SM_ST_MNB,
                     WS_CHILD | WS_VISIBLE, 100,
                     100, rcClient.bottom - GetSysCharHeight () - 4, 
                     100, GetSysCharHeight () + 4, hWnd, 0);
        if (fill_menu (hwnd_menu) <= 0) {
            fprintf (stderr, "Can not find scenario.\n");
            return -1;
        }

        SendMessage (hwnd_menu, MBM_SETCURITEM, 0, 0);

        hwnd_score = CreateWindow (CTRL_STATIC, SM_ST_SETSCORE, 
                    WS_CHILD | WS_VISIBLE | SS_RIGHT, 0,
                    200, rcClient.bottom - GetSysCharHeight () - 4,
                    rcClient.right - 200, GetSysCharHeight () + 4, hWnd, 0);

        mbi.which = MB_WHICH_TEXT;
        SendMessage (hwnd_menu, MBM_GETITEMDATA, 0, (LPARAM)&mbi);
        create_same_board (mbi.text);
        new_game (hWnd);
    }
    break;
        
    case MSG_COMMAND:
        if (LOWORD(wParam) == 100 && HIWORD (wParam) == MBN_CHANGED) {
            int sel = SendMessage (hwnd_menu, MBM_GETCURITEM, 0, 0);
            if (sel >= 0)
                sel_scenario (hWnd, sel);
            break;
        }

        switch (wParam) {
        case IDM_NEW:
            new_game (hWnd);
        break;

        case IDM_SCORES:
        break;
            
        case IDM_EXIT:
            SendMessage (hWnd, MSG_CLOSE, 0, 0L);
        break;

        case IDM_PREF:
        break;
            
        case IDM_ABOUT:
        break;
    }
    break;


    case MSG_PAINT:
    {
        HDC hdc;
        hdc = BeginPaint (hWnd);
        paint (hWnd, hdc);
        EndPaint (hWnd, hdc);
        return 0;
    }

    case MSG_LBUTTONDOWN:
    {
        int x = LOWORD (lParam);
        int y = HIWORD (lParam);

        kill_balls (hWnd, x / STONE_SIZE, y / STONE_SIZE);
        old_x = -1;
        old_y = -1;
    }
    break;

    case MSG_MOUSEMOVE:
    {
        int x = LOWORD (lParam);
        int y = HIWORD (lParam);
        
        if (PtInRect (&rcBoard, x, y))
            mark_balls (hWnd, x / STONE_SIZE, y / STONE_SIZE);
        else
            unmark_balls (hWnd);
    }
    break;

    case MSG_NCMOUSEMOVE:
        if (wParam != HT_CLIENT)
            unmark_balls (hWnd);
    break;

    case MSG_MOUSEMOVEIN:
        if (!wParam)
            unmark_balls (hWnd);
        break;

    case MSG_TIMER:
        if (wParam == ID_TIMER) {
            HDC hdc = GetClientDC (hWnd);
            move_tagged_balls (hdc);
            ReleaseDC (hdc);
        }
        break;

    case MSG_CLOSE:
        if (MessageBox (hWnd, 
                    SM_ST_QUIT, 
                    SM_ST_SAME, 
                    MB_YESNO | MB_ICONQUESTION |
                    MB_BASEDONPARENT) != IDYES)
            return 0;

        DestroyAllControls (hWnd);
           DestroyMainWindow (hWnd);
        PostQuitMessage (hWnd);
        return 0;
    }

    return DefaultMainWinProc (hWnd, message, wParam, lParam);
}