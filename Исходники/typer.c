LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int cxChar, cyChar;
    static int xCaret, yCaret;
    static int cxClient, cyClient;
    static int cxBuffer, cyBuffer;
    static DWORD dwCharSet = DEFAULT_CHARSET;
    static TCHAR    *szBuffer;

    HDC         hdc;
    PAINTSTRUCT ps;
    TEXTMETRIC  tm;
    int         x, y;
    int         j;


    switch(uMsg)
    {
    case WM_INPUTLANGCHANGE:
    case WM_CREATE:
        if(uMsg == WM_INPUTLANGCHANGE)
        {
            dwCharSet = wParam ;
        }

        hdc = GetDC (hwnd) ;
        SelectObject (hdc, CreateFont (0, 0, 0, 0, 0, 0, 0, 0, dwCharSet, 0, 0, 0, FIXED_PITCH, NULL)) ;

        GetTextMetrics (hdc, &tm) ;
        cxChar = tm.tmAveCharWidth ;
        cyChar = tm.tmHeight ;

        DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;
        ReleaseDC (hwnd, hdc) ;

        for (x = 0; x < cxBuffer; ++x)
            for(y=0; y < cyBuffer; ++y)
                BUFFER(x, y) = ' ';
        xCaret = 0;
        yCaret = 0;
        if (hwnd == GetFocus())
        {
            SetCaretPos(xCaret * cxChar, yCaret * cyChar);
        }
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);

        cxBuffer = cxClient / cxChar;
        cyBuffer = cyClient / cyChar;

        if (szBuffer != NULL)
        {
            free(szBuffer);
        }
        szBuffer = (TCHAR *)malloc(cxBuffer * cyBuffer * sizeof(TCHAR));

        for (x = 0; x < cxBuffer; ++x)
            for(y=0; y < cyBuffer; ++y)
                BUFFER(x, y) = ' ';
        xCaret = 0;
        yCaret = 0;
        if (hwnd == GetFocus())
        {
            SetCaretPos(xCaret * cxChar, yCaret * cyChar);
        }
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_SETFOCUS:
        {
            CreateCaret (hwnd, NULL, cxChar, cyChar) ;
            SetCaretPos (xCaret * cxChar, yCaret * cyChar) ;
            ShowCaret (hwnd) ;
            return 0 ;
        }
    case WM_KILLFOCUS:
        {
            HideCaret (hwnd) ;
            DestroyCaret () ;
            return 0 ;
        }
    case WM_KEYDOWN:
        {
            switch(wParam)
            {
            case VK_DELETE:
                for (x = xCaret; x < cxBuffer -1; ++x)
                {
                    BUFFER(x, yCaret) = BUFFER(x+1, yCaret);
                }
                BUFFER(cxBuffer-1, yCaret) = ' ';

                hdc = GetDC(hwnd);
                HideCaret(hwnd);
                SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0, dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));  
                TextOut(hdc, xCaret * cxChar, yCaret * cyChar, &BUFFER(xCaret, yCaret), cxBuffer - xCaret);
                DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
                ShowCaret(hwnd);
                ReleaseDC(hwnd, hdc);
                break;
            case VK_UP:
                if (yCaret > 0)
                    yCaret--;
                break;
            case VK_DOWN:
                if (yCaret < cyBuffer - 1)
                    yCaret++;
                break;
            case VK_LEFT:
                if (xCaret > 0)
                    xCaret--;
                break;
            case VK_RIGHT:
                if (xCaret < cxBuffer - 1)
                    xCaret++;
                break;
            case VK_HOME:
                xCaret = 0;
                break;
            case VK_END:
                xCaret = cxBuffer - 1;
                break;
            case VK_PRIOR:
                yCaret = 0;
                break;
            case VK_NEXT:
                yCaret = cyBuffer - 1;
                break;
            default:
                break;
            }
            SetCaretPos(xCaret*cxChar, yCaret*cyChar);
            return 0;
        }
    case WM_CHAR:
        {
            for (j = 0; j < LOWORD(lParam); ++j)
            {
                hdc = GetDC(hwnd);
                HideCaret(hwnd);
                switch(wParam)
                {
                    // Ctrl + Enter
                case '\n':
                    {
                        if (++yCaret == cyBuffer)
                        {
                            yCaret = 0;
                        }
                        break;
                    }
                    //Enter
                case '\r':
                    {
                        xCaret = 0;
                        if (++yCaret == cyBuffer)
                        {
                            yCaret = 0;
                        }
                        break;
                    }
                case '\t':
                    {
                        do
                        {
                            SendMessage(hwnd, WM_CHAR, ' ', 1);
                        }
                        while(xCaret % 8);
                        break;
                    }
                case '\b':      //backspace
                    {
                        if (xCaret > 0)
                        {
                            xCaret--;
                            SendMessage(hwnd, WM_KEYDOWN, VK_DELETE, 1);
                        }
                        break;
                    }
                case '\x1B':    //Escape
                    {
                        for (x = 0; x < cxBuffer; ++x)
                        {
                            for (y = 0; y < cyBuffer; ++y)
                            {
                                BUFFER(x, y) = ' ';
                            }
                        }
                        xCaret = 0;
                        yCaret = 0;
                        SetCaretPos(xCaret * cxChar, yCaret * cyChar);
                        InvalidateRect(hwnd, NULL, TRUE);
                        break;
                    }
                default:
                    {
                    BUFFER(xCaret, yCaret) = (TCHAR)wParam;
                    SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0, dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));  
                    TextOut(hdc, xCaret * cxChar, yCaret * cyChar, &BUFFER(xCaret, yCaret), sizeof(BUFFER(xCaret, yCaret))/sizeof(TCHAR));
                    DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
                    xCaret++;
                    break;
                    }
                }

                if (xCaret >= cxBuffer)
                {
                    xCaret = 0;
                    yCaret++;
                }
                if (yCaret >= cyBuffer)
                {
                    yCaret = 0;
                }
                SetCaretPos(xCaret * cxChar, yCaret * cyChar);
                ReleaseDC(hwnd, hdc);
                ShowCaret(hwnd);
            }
            return 0;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            SelectObject (hdc, CreateFont (0, 0, 0, 0, 0, 0, 0, 0, dwCharSet, 0, 0, 0, FIXED_PITCH, NULL)) ;
            for (y = 0; y < cyBuffer; ++y)
            {
                TextOut(hdc, 0, y * cyChar, &szBuffer[y*cxBuffer], cxBuffer);
            }
            DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
            EndPaint(hwnd, &ps);
            break;
        }
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    default:
        {
            break;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}