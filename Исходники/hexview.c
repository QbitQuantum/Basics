LRESULT CALLBACK HexviewProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static unsigned char **pBuffer = NULL ;
    unsigned char	ascii, *bin_data;
    static int  cxChar, cxCaps, cxClient, cyClient,
           iVscrollPos, iVscrollMax,
           cyChar, xCaret = 6, yCaret;
    HDC         hdc ;
    int			y, i, nResult, iVscrollInc;
    static int	iPaintBeg, iPaintEnd;
    char		szFilename[MAX_PATH], szBuffer[256];

    RECT			rect = {50, 50, 620, 300};
    PAINTSTRUCT		ps;
    TEXTMETRIC		tm;
    static HFONT	hFont;
    HDROP			hDrop;


    switch (iMsg)
    {
    //case WM_INITDIALOG:
    case WM_CREATE :
        hdc = GetDC (hwnd) ;
        hFont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, FIXED_PITCH | FF_DONTCARE, "Courier");
        SelectObject (hdc, hFont) ;
        GetTextMetrics (hdc, &tm) ;
        cxChar = tm.tmAveCharWidth ;
        cyChar = tm.tmHeight ;
        ReleaseDC (hwnd, hdc) ;

        pBuffer = CreateBuffer(64);
        return 0 ;


    case WM_SIZE :
        cxClient = LOWORD (lParam) ;
        cyClient = HIWORD (lParam) ;

        iVscrollMax = max (0, rows + 2 - cyClient / cyChar) ;
        iVscrollPos = min (iVscrollPos, iVscrollMax) ;

        SetScrollRange (hwnd, SB_VERT, 0, iVscrollMax, FALSE) ;
        SetScrollPos   (hwnd, SB_VERT, iVscrollPos, TRUE) ;

        return 0;


    case WM_VSCROLL:
        switch (LOWORD(wParam))
        {
        case SB_TOP:
            iVscrollInc = -iVscrollPos;
            break;

        case SB_BOTTOM:
            iVscrollInc = iVscrollMax = iVscrollPos;
            break;

        case SB_LINEUP:
            iVscrollInc = -1;
            break;

        case SB_LINEDOWN:
            iVscrollInc = 1;
            break;

        case SB_PAGEUP:
            iVscrollInc = min(-1, -cyClient / cyChar);
            break;

        case SB_PAGEDOWN:
            iVscrollInc = max(1, cyClient / cyChar);
            break;

        case SB_THUMBTRACK:
            iVscrollInc = HIWORD(wParam) - iVscrollPos;
            break;

        default:
            iVscrollInc = 0;
        }

        iVscrollInc = max (-iVscrollPos,
                           min (iVscrollInc, iVscrollMax - iVscrollPos));

        if (iVscrollInc != 0)
        {
            iVscrollPos += iVscrollInc;
            ScrollWindow(hwnd, 0, -cyChar * iVscrollInc, NULL, NULL);
            SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);

            xCaret = 6;
            yCaret = 0;
            SetCaretPos (xCaret * cxChar, 0) ;
            //UpdateWindow(hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
        }

        return 0;


    case WM_SETFOCUS :
        // create and show the caret

        CreateCaret (hwnd, NULL, cxChar, cyChar) ;
        SetCaretPos (xCaret * cxChar, yCaret * cyChar) ;
        ShowCaret (hwnd) ;
        return 0 ;

    case WM_KILLFOCUS :
        // hide and destroy the caret
        HideCaret (hwnd) ;
        DestroyCaret () ;
        return 0 ;

    case WM_KEYDOWN :
        switch (wParam)
        {
        case VK_HOME :
            xCaret = 6 ;
            break ;

        case VK_PRIOR :
            yCaret = 0 ;
            break ;

        case VK_LEFT :
            xCaret = max (xCaret - 1, 6);
            if (pBuffer[yCaret][xCaret] == ' ')
                xCaret = max (xCaret - 1, 6);
            break ;

        case VK_RIGHT :
            ++xCaret;

            if (lastrow && (yCaret + iPaintBeg == rows-1))
                if (xCaret > (4 + lastrow*3))
                {
                    --xCaret;
                    break;
                }

            if (xCaret > 52)
            {
                xCaret = 6;
                ++yCaret;
                if (yCaret + iPaintBeg> rows - 1)
                {
                    --yCaret;
                    xCaret = 52;
                }
            }
            if ((xCaret % 3) == 2)
                ++xCaret;
            break ;

        case VK_UP :
            yCaret = max (yCaret - 1, 0) ;
            break ;

        case VK_DOWN :
            if (lastrow && (xCaret > (4 + lastrow*3)))
                yCaret = min(yCaret + 1, rows - iPaintBeg - 2);
            else
                yCaret = min(yCaret + 1, rows - iPaintBeg - 1);
            break ;
        }

        SetCaretPos (xCaret * cxChar, yCaret * cyChar) ;
        return 0 ;

    case WM_CHAR :
        for (i = 0 ; i < (int) LOWORD (lParam) ; i++)
        {
            if (!((wParam >= '0' && wParam <='9') || (wParam >= 'a' && wParam <= 'f')))
                return 0;


            HideCaret (hwnd) ;
            hdc = GetDC (hwnd) ;

            SelectObject (hdc, hFont);

            pBuffer[yCaret + iPaintBeg][xCaret] = wParam;
            TextOut(hdc, xCaret * cxChar, (yCaret) * cyChar, &pBuffer[yCaret + iPaintBeg][xCaret], 1);

            if (pBuffer[yCaret + iPaintBeg][xCaret-1] == ' ')
                ascii = hextoint(pBuffer[yCaret + iPaintBeg][xCaret], pBuffer[yCaret + iPaintBeg][xCaret + 1]);
            else
                ascii = hextoint(pBuffer[yCaret + iPaintBeg][xCaret - 1], pBuffer[yCaret + iPaintBeg][xCaret]);

            if (ascii > 33 && ascii < 125)
            {
                pBuffer[yCaret + iPaintBeg][(xCaret/3) + 54] = ascii;
                TextOut(hdc, ((xCaret/3) + 54)* cxChar, yCaret * cyChar, &pBuffer[yCaret + iPaintBeg][(xCaret/3) + 54], 1);
            }
            else
            {
                pBuffer[yCaret + iPaintBeg][(xCaret/3) + 54] = '.';
                TextOut(hdc, ((xCaret/3) + 54)* cxChar, yCaret * cyChar, &pBuffer[yCaret + iPaintBeg][(xCaret/3) + 54], 1);
            }

            ShowCaret (hwnd) ;
            ReleaseDC (hwnd, hdc) ;

            SendMessage(hwnd, WM_KEYDOWN, VK_RIGHT, 0);
            break ;
        }
        return 0 ;


    case WM_DROPFILES:
        hDrop = (HANDLE) wParam;
        DragQueryFile(hDrop, 0, szFilename, sizeof(szFilename));
        pBuffer = LoadPacket(szFilename);
        GetWindowRect(hwnd, &rect);
        SendMessage(hwnd, WM_SIZE, 0, MAKEWPARAM(rect.bottom - rect.top, rect.right - rect.left));
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;


    case WM_PAINT :
        hdc = BeginPaint (hwnd, &ps) ;
        SelectObject (hdc, hFont) ;

        iPaintBeg = max (0, iVscrollPos + ps.rcPaint.top / cyChar );
        iPaintEnd = min (rows,
                         iVscrollPos + ps.rcPaint.bottom / cyChar);

        i =0;
        for (y = iPaintBeg; y < iPaintEnd; y++, i++)
            TextOut(hdc, 0, i * cyChar, pBuffer[y], 72);

        EndPaint (hwnd, &ps) ;
        return 0 ;

    case WM_DESTROY :
        DeleteBuffer(pBuffer);
        DeleteObject(hFont);
        return 0 ;
    }
    return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
}