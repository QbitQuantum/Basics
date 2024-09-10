LRESULT WINAPI
RealDefWindowProcW(HWND hWnd,
                   UINT Msg,
                   WPARAM wParam,
                   LPARAM lParam)
{
    LRESULT Result = 0;
    PWND Wnd;

    Wnd = ValidateHwnd(hWnd);

    if ( !Wnd &&
         Msg != WM_CTLCOLORMSGBOX &&
         Msg != WM_CTLCOLORBTN    &&
         Msg != WM_CTLCOLORDLG    &&
         Msg != WM_CTLCOLORSTATIC )
       return 0;

    SPY_EnterMessage(SPY_DEFWNDPROC, hWnd, Msg, wParam, lParam);
    switch (Msg)
    {
        case WM_NCCREATE:
        {
            if ( Wnd &&
                 Wnd->style & (WS_HSCROLL | WS_VSCROLL) )
            {
               if (!Wnd->pSBInfo)
               {
                  SCROLLINFO si = {sizeof si, SIF_ALL, 0, 100, 0, 0, 0};
                  SetScrollInfo( hWnd, SB_HORZ, &si, FALSE );
                  SetScrollInfo( hWnd, SB_VERT, &si, FALSE );
               }
            }

            if (lParam)
            {
                LPCREATESTRUCTW cs = (LPCREATESTRUCTW)lParam;
                /* check for string, as static icons, bitmaps (SS_ICON, SS_BITMAP)
                 * may have child window IDs instead of window name */
                if (HIWORD(cs->lpszName))
                {
                    DefSetText(hWnd, cs->lpszName, FALSE);
                }
                Result = 1;
            }
            break;
        }

        case WM_GETTEXTLENGTH:
        {
            PWSTR buf;
            ULONG len;

            if (Wnd != NULL && Wnd->strName.Length != 0)
            {
                buf = DesktopPtrToUser(Wnd->strName.Buffer);
                if (buf != NULL &&
                    NT_SUCCESS(RtlUnicodeToMultiByteSize(&len,
                                                         buf,
                                                         Wnd->strName.Length)))
                {
                    Result = (LRESULT) (Wnd->strName.Length / sizeof(WCHAR));
                }
            }
            else Result = 0L;

            break;
        }

        case WM_GETTEXT:
        {
            PWSTR buf = NULL;
            PWSTR outbuf = (PWSTR)lParam;

            if (Wnd != NULL && wParam != 0)
            {
                if (Wnd->strName.Buffer != NULL)
                    buf = DesktopPtrToUser(Wnd->strName.Buffer);
                else
                    outbuf[0] = L'\0';

                if (buf != NULL)
                {
                    if (Wnd->strName.Length != 0)
                    {
                        Result = min(Wnd->strName.Length / sizeof(WCHAR), wParam - 1);
                        RtlCopyMemory(outbuf,
                                      buf,
                                      Result * sizeof(WCHAR));
                        outbuf[Result] = L'\0';
                    }
                    else
                        outbuf[0] = L'\0';
                }
            }
            break;
        }

        case WM_SETTEXT:
        {
            DefSetText(hWnd, (PCWSTR)lParam, FALSE);

            if ((GetWindowLongPtrW(hWnd, GWL_STYLE) & WS_CAPTION) == WS_CAPTION)
                UserPaintCaption(hWnd);
            Result = 1;
            break;
        }

        case WM_IME_CHAR:
        {
            PostMessageW(hWnd, WM_CHAR, wParam, lParam);
            Result = 0;
            break;
        }

        case WM_IME_KEYDOWN:
        {
            Result = PostMessageW(hWnd, WM_KEYDOWN, wParam, lParam);
            break;
        }

        case WM_IME_KEYUP:
        {
            Result = PostMessageW(hWnd, WM_KEYUP, wParam, lParam);
            break;
        }

        case WM_IME_STARTCOMPOSITION:
        case WM_IME_COMPOSITION:
        case WM_IME_ENDCOMPOSITION:
        case WM_IME_SELECT:
        case WM_IME_NOTIFY:
        {
            HWND hwndIME;

            hwndIME = DefWndImmGetDefaultIMEWnd(hWnd);
            if (hwndIME)
                Result = SendMessageW(hwndIME, Msg, wParam, lParam);
            break;
        }

        case WM_IME_SETCONTEXT:
        {
            HWND hwndIME;

            hwndIME = DefWndImmGetDefaultIMEWnd(hWnd);
            if (hwndIME)
                Result = DefWndImmIsUIMessageW(hwndIME, Msg, wParam, lParam);
            break;
        }

        default:
            Result = User32DefWindowProc(hWnd, Msg, wParam, lParam, TRUE);
    }
    SPY_ExitMessage(SPY_RESULT_DEFWND, hWnd, Msg, Result, wParam, lParam);

    return Result;
}