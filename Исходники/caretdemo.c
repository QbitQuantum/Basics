/* a simple edit window */
static int MyeditWindowProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    int w = 0;
    SIZE Size;
    static char *pBuffer = NULL;
    static int pos = 0, len = 0;
    HDC hdc;

    switch (message) {
        case MSG_CREATE:
            SetWindowFont(hWnd, GetSystemFont(SYSLOGFONT_DEFAULT));
            if (!CreateCaret (hWnd, NULL, 1, GetSysCharHeight())) {
                return -1;
            }
            pBuffer = (char *) calloc(1, 11);
            *pBuffer = 0;
            break;

        case MSG_SETFOCUS:
            hdc = GetClientDC(hWnd);
            w = GetTextExtent (hdc, pBuffer, pos, &Size);
            SetCaretPos(hWnd, w, 0);
            //SetCaretPos(hWnd, pos*GetSysCharWidth(), 0);
            ShowCaret(hWnd);
            ReleaseDC(hdc);
            break;

        case MSG_KILLFOCUS:
            HideCaret(hWnd);
            break;

        case MSG_CHAR:
            switch (wParam) {
                case '\t':
                case '\b':
                case '\n':
                    SetCaretBlinkTime(hWnd, GetCaretBlinkTime(hWnd)-100);
                    break;

                default:
                    {
                        char ch, buf[11];
                        char *tmp;
                        ch = wParam;
                        if (!isalpha(ch) && !isdigit(ch))
                            break;
                        if (len == 10)
                            break;
                        tmp = pBuffer+pos;
                        if (*tmp != 0) {
                            strcpy(buf, tmp);
                            strcpy(tmp+1, buf);
                        }
                        *tmp = ch;
                        pos++;
                        len++;

                        hdc = GetClientDC(hWnd);
                        InvalidateRect(hWnd, NULL, TRUE);
                        w = GetTextExtent (hdc, pBuffer, pos, &Size);
                        SetCaretPos(hWnd, w, 0);
                        //SetCaretPos(hWnd, pos*GetSysCharWidth(), 0);
                        ShowCaret(hWnd);
                        ReleaseDC(hdc);
                    }
                    break;
            }
            break;

        case MSG_KEYDOWN:
            switch (wParam) {
                case SCANCODE_CURSORBLOCKLEFT:
                    pos = MAX(pos-1, 0);
                    break;
                case SCANCODE_CURSORBLOCKRIGHT:
                    pos = MIN(pos+1, len);
                    break;
                case SCANCODE_BACKSPACE:
                    {
                        char buf[11];
                        char *tmp;
                        if (len == 0 || pos == 0)
                            break;
                        tmp = pBuffer+pos;
                        strcpy(buf, tmp);
                        strcpy(tmp-1, buf);
                        pos--;
                        len--;
                        break;
                    }
            }
            if (wParam == SCANCODE_CURSORBLOCKLEFT || wParam == SCANCODE_CURSORBLOCKRIGHT ||
                    wParam == SCANCODE_BACKSPACE) {
                hdc = GetClientDC(hWnd);
                InvalidateRect(hWnd, NULL, TRUE);
                w = GetTextExtent (hdc, pBuffer, pos, &Size);
                //SetCaretPos(hWnd, pos*GetSysCharWidth(), 0);
                SetCaretPos(hWnd, w, 0);
                ReleaseDC(hdc);
            }
            break;

        case MSG_PAINT:
            hdc = BeginPaint(hWnd);
            TextOut(hdc, 0, 0, pBuffer);
            EndPaint(hWnd, hdc);
            return 0;

        case MSG_DESTROY:
            DestroyCaret (hWnd);
            if (pBuffer)
                free(pBuffer);
            return 0;
    }

    return DefaultControlProc(hWnd, message, wParam, lParam);
}