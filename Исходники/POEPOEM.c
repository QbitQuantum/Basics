LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static int          nLineCount,lineNo;
    static int          cyClient, cxChar, cyChar;
    static int          xScroll;
    static HGLOBAL      hResource;
    static HWND         hwndScroll;
    static HWND         hScroll;

    CHAR        *szText;
    HINSTANCE   hInstance;
    HDC         hdc;
    PAINTSTRUCT ps;
    RECT        clientRect;
    int         i;

    switch(msg)
    {
    case WM_CREATE:
        hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
        lineNo = 0;
        //Load Text resource
        hResource = LoadResource(hInstance, FindResource(hInstance, TEXT("ANNABELLEE"), TEXT("TEXT")));
        szText = (CHAR *)LockResource(hResource);

        //Create Scrollbar
        hScroll = CreateWindow(TEXT("scrollbar"), NULL, SB_VERT | WS_CHILD | WS_VISIBLE, 
                    0, 0, 0, 0,
                    hwnd, (HMENU)1, hInstance, NULL);
        //calculate line count
        while(*szText != '\0' && *szText != '\\')
        {
            if (*szText == '\n')
                ++nLineCount;
            szText = AnsiNext(szText);
        }
        *szText == '\0';

        //Get char size
        cxChar = LOWORD(GetDialogBaseUnits());
        cyChar = HIWORD(GetDialogBaseUnits());
        xScroll = GetSystemMetrics(SM_CXVSCROLL);

        //Setup scroll 
        SetScrollRange(hScroll, SB_CTL, 0, nLineCount, TRUE);
        SetScrollPos(hScroll, SB_CTL, 0, TRUE);
        break;
    case WM_SIZE:
        {
            MoveWindow(hScroll, LOWORD(lParam) - xScroll, 0, xScroll, HIWORD(lParam), TRUE); 
            cyClient = HIWORD(lParam);
            SetFocus(hScroll);
            break;
        }
    case WM_SETFOCUS:
        {
            SetFocus(hScroll);
            break;
        }
    case WM_VSCROLL:
        {
            switch(wParam)
            {
                case SB_TOP:
                    lineNo = 0;
                    break;
                case SB_BOTTOM:
                    lineNo = nLineCount;
                    break;
                case SB_LINEDOWN:
                    lineNo++;
                    break;
                case SB_LINEUP:
                    lineNo--;
                    break;
                case SB_PAGEDOWN:
                    lineNo += cyClient / cyChar;
                    break;
                case SB_PAGEUP:
                    lineNo -= cyClient / cyChar;
                    break;
                default:
                    break;
            }
            lineNo = max(0, lineNo);
            lineNo = min(lineNo, nLineCount);
            SetScrollPos(hScroll, SB_CTL, lineNo, TRUE);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &clientRect);
            clientRect.left += cxChar;
            clientRect.top += cyChar*(1 - lineNo);
            szText = (CHAR *)LockResource(hResource);
            DrawTextA(hdc, szText, -1, &clientRect, DT_TOP); 
            EndPaint(hwnd, &ps);
            break;
        }
    case WM_DESTROY:
        {
            FreeResource(hResource);
            PostQuitMessage(0);
            break;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}