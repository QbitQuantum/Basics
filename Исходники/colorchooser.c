INT_PTR CALLBACK DlgProcColorToolWindow(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static COLORCHOOSER* pCC = NULL;
    static int iCurrentHotTrack;
    static BOOL bChoosing;
    static int iRows;
    static int iColumns;
    static HWND hPreviousActiveWindow;

    switch(msg) {
    case WM_INITDIALOG:
    {
        RECT rc;
        int iSquareRoot;
        int width ;
        int height;

        TranslateDialogDefault(hwndDlg);
        pCC = (COLORCHOOSER*) lParam;

        iCurrentHotTrack = -2;
        bChoosing = FALSE;

        iSquareRoot = (int)sqrt(pCC->pModule->nColorCount);

        iColumns = iSquareRoot * iSquareRoot == pCC->pModule->nColorCount?iSquareRoot:iSquareRoot+1;
        iRows = iSquareRoot;

        rc.top = rc.left = 100;
        rc.right =  100 +  iColumns * 25 + 1;
        rc.bottom = iRows * 20 + 100 + 20;

        AdjustWindowRectEx(&rc, GetWindowLong(hwndDlg, GWL_STYLE), FALSE, GetWindowLong(hwndDlg, GWL_EXSTYLE));

        width = rc.right - rc.left;
        height = rc.bottom - rc.top;

        pCC->yPosition -= height;


        SetDlgItemText(hwndDlg, IDC_CHAT_COLORTEXT, pCC->bForeground?TranslateT("Text colour"):TranslateT("Background colour"));
        SetWindowPos(GetDlgItem(hwndDlg, IDC_CHAT_COLORTEXT), NULL,  0, 0, width, 20, 0);
        SetWindowPos(hwndDlg, NULL, pCC->xPosition, pCC->yPosition, width, height, SWP_SHOWWINDOW);
    }
    break;

    case WM_CTLCOLOREDIT:
    case WM_CTLCOLORSTATIC:
        if((HWND)lParam==GetDlgItem(hwndDlg,IDC_CHAT_COLORTEXT)) {
            SetTextColor((HDC)wParam,RGB(60,60,150));
            SetBkColor((HDC)wParam,GetSysColor(COLOR_WINDOW));
            return (INT_PTR)GetSysColorBrush(COLOR_WINDOW);
        }
        break;

    case WM_COMMAND:
        switch ( LOWORD( wParam )) {
        case IDOK:
            if (iCurrentHotTrack >= 0)
                PostMessage(hwndDlg, WM_LBUTTONUP, 0, 0);
            break;
        case IDCANCEL:
            DestroyWindow(hwndDlg);
            break;
        }
        break;

    case WM_LBUTTONUP:
        if (iCurrentHotTrack >= 0 && iCurrentHotTrack < pCC->pModule->nColorCount && pCC->hWndTarget != NULL) {
            HWND hWindow;
            CHARFORMAT2 cf;
            cf.cbSize = sizeof(CHARFORMAT2);
            cf.dwMask = 0;
            cf.dwEffects = 0;
            hWindow = GetParent(pCC->hWndTarget);

            if ( pCC->bForeground ) {
                pCC->si->bFGSet = TRUE;
                pCC->si->iFG = iCurrentHotTrack;
                if ( IsDlgButtonChecked( hWindow, IDC_CHAT_COLOR )) {
                    cf.dwMask = CFM_COLOR;
                    cf.crTextColor = pCC->pModule->crColors[iCurrentHotTrack];
                    if (pCC->pModule->bSingleFormat) {
                        SendMessage(pCC->hWndTarget, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
                    } else {
                        SendMessage(pCC->hWndTarget, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
                    }
                }
            }
            else {
                pCC->si->bBGSet = TRUE;
                pCC->si->iBG = iCurrentHotTrack;
                if(IsDlgButtonChecked(hWindow, IDC_CHAT_BKGCOLOR)) {
                    cf.dwMask = CFM_BACKCOLOR;
                    cf.crBackColor = pCC->pModule->crColors[iCurrentHotTrack];
                    if (pCC->pModule->bSingleFormat) {
                        SendMessage(pCC->hWndTarget, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
                    } else {
                        SendMessage(pCC->hWndTarget, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
                    }
                }
            }
        }
        PostMessage(hwndDlg, WM_CLOSE, 0, 0);
        break;

    case WM_ACTIVATE:
        if (wParam == WA_INACTIVE)
            PostMessage(hwndDlg, WM_CLOSE, 0, 0);
        else if ((wParam == WA_ACTIVE) || (wParam == WA_CLICKACTIVE))
            hPreviousActiveWindow = (HWND)lParam;
        break;

    case WM_MOUSEMOVE:
    {
        HDC hdc = GetDC(hwndDlg);
        POINT pt;
        RECT rect;
        int but;

        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        if (iCurrentHotTrack == -2)
            return 0; // prevent focussing when not drawn yet!

        but = CalculateCoordinatesToButton(pCC, pt);

        // weird stuff
        if (but != iCurrentHotTrack) {
            if (iCurrentHotTrack >= 0) {
                rect = CalculateButtonToCoordinates(pCC, iCurrentHotTrack);
                DrawFocusRect(hdc, &rect);
                iCurrentHotTrack = -1;
            }
            iCurrentHotTrack = but;

            if (iCurrentHotTrack >= 0) {
                rect = CalculateButtonToCoordinates(pCC, iCurrentHotTrack);
                DrawFocusRect(hdc, &rect);
            }
        }
        ReleaseDC(hwndDlg, hdc);
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rc;
        int i;
        int iThisRow = 1;
        int iThisColumn = 0;

        GetClientRect(hwndDlg, &rc);

        rc.top += 20;

        hdc = BeginPaint(hwndDlg, &ps);

        // fill background
        FillRect(hdc, &rc, GetSysColorBrush(COLOR_WINDOW));

        for (i=0; i < pCC->pModule->nColorCount; i++)
        {
            HBRUSH hbr;

            // decide place to draw the color block in the window
            iThisColumn ++;
            if (iThisColumn > iColumns) {
                iThisColumn = 1;
                iThisRow++;
            }

            if ( (pCC->bForeground && pCC->si->bFGSet && pCC->si->iFG == i) ||
                    (!pCC->bForeground && pCC->si->bBGSet && pCC->si->iBG == i) ) {
                rc.top = (iThisRow-1) * 20+ 1 +20 ;
                rc.left = (iThisColumn-1) * 25 + 1 + 1 ;
                rc.bottom = iThisRow * 20- 1 + 20 ;
                rc.right = iThisColumn * 25-1 ;

                DrawEdge(hdc, &rc, EDGE_RAISED, BF_TOP|BF_LEFT|BF_RIGHT|BF_BOTTOM);
            }

            rc.top = (iThisRow-1) * 20+ 3 +20 ;
            rc.left = (iThisColumn-1) * 25 + 3 + 1 ;
            rc.bottom = iThisRow * 20- 3 + 20 ;
            rc.right = iThisColumn * 25-3 ;

            FillRect(hdc, &rc, GetStockObject(BLACK_BRUSH));

            hbr = CreateSolidBrush(pCC->pModule->crColors[i]);

            rc.top = (iThisRow-1) * 20+4 +20;
            rc.left = (iThisColumn-1) * 25+ 4 + 1;
            rc.bottom = iThisRow * 20-4 + 20;
            rc.right = iThisColumn * 25-4;

            FillRect(hdc, &rc, hbr);
            DeleteObject(hbr);
        }

        EndPaint(hwndDlg, &ps);
        iCurrentHotTrack = -1;
    }
    break;

    case WM_CLOSE:
        SetFocus(pCC->hWndTarget);
        DestroyWindow(hwndDlg);
        break;

    case WM_DESTROY:
        mir_free( pCC );
        return TRUE;
    }

    return FALSE;
}