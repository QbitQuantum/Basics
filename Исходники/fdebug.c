LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int                    wmId, wmEvent;
    PAINTSTRUCT            ps;
    HDC                    hdc;
    RECT                rc;
    TCHAR                WndText[MAX_PATH];
    DWORD                Index;
    NONCLIENTMETRICS    ncm;
    HFONT                hFont;

    switch (message)
    {
    case WM_CREATE:

        hEditWnd = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""), WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_AUTOHSCROLL|ES_LEFT|ES_MULTILINE, 0, 0, 0, 0, hWnd, NULL, hInst, NULL);
        hDisplayWnd = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""), WS_CHILD|WS_VISIBLE|WS_HSCROLL|WS_VSCROLL|ES_MULTILINE, 0, 0, 0, 0, hWnd, NULL, hInst, NULL);

        memset(&ncm, 0, sizeof(NONCLIENTMETRICS));
        ncm.cbSize = sizeof(NONCLIENTMETRICS);
        SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);

        hFont = CreateFontIndirect(&ncm.lfMessageFont);

        SendMessage(hEditWnd, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hDisplayWnd, WM_SETFONT, (WPARAM)hFont, TRUE);

        break;
    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);

        if (lParam == (LPARAM)hEditWnd && wmEvent == EN_CHANGE)
        {
            GetWindowText(hEditWnd, WndText, MAX_PATH);

            if (_tcslen(WndText) > 0)
            {
                SetWindowText(hEditWnd, TEXT(""));

                if (!bConnected)
                {
                    MessageBox(hWnd, TEXT("You are not currently connected!"), TEXT("Error"), MB_OK|MB_ICONSTOP);
                    break;
                }

                for (Index=0; Index<_tcslen(WndText); Index++)
                {
                    if (dwThreadId != 0)
                    {
                        PostThreadMessage(dwThreadId, WM_CHAR, (WPARAM)WndText[Index], (LPARAM)0);
                    }
                }
            }
        }

        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
           DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
           break;
        case IDM_EXIT:
           DestroyWindow(hWnd);
           break;
        case IDM_FILE_CLEARDISPLAY:
            SetWindowText(hDisplayWnd, TEXT(""));
            break;
        case IDM_FILE_CONNECT:
            if (bConnected)
            {
                MessageBox(hWnd, TEXT("You are already connected!"), TEXT("Error"), MB_OK|MB_ICONSTOP);
            }
            else
            {
                if (DialogBox(hInst, (LPCTSTR)IDD_CONNECTION, hWnd, (DLGPROC)ConnectionDialogProc) == IDOK)
                {
                    bConnected = TRUE;
                    EnableFileMenuItemByID(IDM_FILE_DISCONNECT, TRUE);
                    EnableFileMenuItemByID(IDM_FILE_CONNECT, FALSE);
                    _beginthread(Rs232Thread, 0, NULL);
                }
            }
            break;
        case IDM_FILE_DISCONNECT:
            if (bConnected)
            {
                bConnected = FALSE;
                EnableFileMenuItemByID(IDM_FILE_DISCONNECT, FALSE);
                EnableFileMenuItemByID(IDM_FILE_CONNECT, TRUE);
            }
            else
            {
                MessageBox(hWnd, TEXT("You are not currently connected!"), TEXT("Error"), MB_OK|MB_ICONSTOP);
            }
            break;
        case IDM_FILE_STARTCAPTURE:
            if (DialogBox(hInst, (LPCTSTR)IDD_CAPTURE, hWnd, (DLGPROC)CaptureDialogProc) == IDOK)
            {
                bCapturing = TRUE;
                EnableFileMenuItemByID(IDM_FILE_STOPCAPTURE, TRUE);
                EnableFileMenuItemByID(IDM_FILE_STARTCAPTURE, FALSE);
                hCaptureFile = CreateFile(strCaptureFileName, FILE_APPEND_DATA, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            }
            break;
        case IDM_FILE_STOPCAPTURE:
            if (bCapturing)
            {
                bCapturing = FALSE;
                EnableFileMenuItemByID(IDM_FILE_STOPCAPTURE, FALSE);
                EnableFileMenuItemByID(IDM_FILE_STARTCAPTURE, TRUE);
                CloseHandle(hCaptureFile);
                hCaptureFile = NULL;
            }
            break;
        case IDM_FILE_LOCALECHO:
            if (bLocalEcho)
            {
                bLocalEcho = FALSE;
                CheckLocalEchoMenuItem(bLocalEcho);
            }
            else
            {
                bLocalEcho = TRUE;
                CheckLocalEchoMenuItem(bLocalEcho);
            }
            break;
        default:
           return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        (void)hdc; // FIXME
        EndPaint(hWnd, &ps);
        break;
    case WM_SIZE:

        GetClientRect(hWnd, &rc);

        MoveWindow(hDisplayWnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top - 20, TRUE);
        MoveWindow(hEditWnd, rc.left, rc.bottom - 20, rc.right - rc.left, 20, TRUE);

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}