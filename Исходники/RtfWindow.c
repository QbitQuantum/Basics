BOOL RtfNotify(HWND hDlg, NMHDR* nmhdr)
{
    static BOOL FindFirst = TRUE;
#define BUFF_LEN 2048
    static TCHAR FindWhat[BUFF_LEN];

    if (nmhdr->code == EN_PROTECTED && !PuttingChar) {
        //block
        ENPROTECTED* enp = (ENPROTECTED*) nmhdr;
        CHARRANGE cr;
        INT TextLen = RtfWindowTextLength();
        BOOL Reset = FALSE, Disallow = FALSE;


        // just let it go ahead anyway
        if (enp->msg == WM_COPY)
            return FALSE;

        // they hit backspace
        if (enp->wParam == VK_BACK) {
            if ((DWORD) enp->chrg.cpMin < StartOfInput ||
                    ((DWORD) enp->chrg.cpMin == StartOfInput &&
                     enp->chrg.cpMin == enp->chrg.cpMax)) {
                Reset = TRUE;
                Disallow = TRUE;
            }
        } else if ((DWORD) enp->chrg.cpMin < StartOfInput) {
            Reset = TRUE;
            Disallow = (enp->wParam == VK_DELETE);
        }

        if (Reset) {
            cr.cpMin = TextLen;
            cr.cpMax = cr.cpMin;
            SendMessage(hWndRtf, EM_EXSETSEL, 0, (LPARAM) &cr);
        }

        // we don't want to paste rich text, as that makes it look weird
        // so send only plain text paste commands
        if ((enp->msg == WM_PASTE) && !Disallow) {
            LPTSTR Buffer = NULL;
            Disallow = TRUE;
#if defined _UNICODE
#define CLIP_FORMAT  CF_UNICODETEXT
#else
#define CLIP_FORMAT  CF_TEXT
#endif
            if (IsClipboardFormatAvailable(CLIP_FORMAT) &&
                    OpenClipboard(hWndMain)) {
                HGLOBAL hGlb;
                LPTSTR str;

                if ((hGlb = GetClipboardData(CLIP_FORMAT)) != NULL &&
                        (str = GlobalLock(hGlb)) != NULL) {
                    Buffer = StringDup(str);
                    GlobalUnlock(hGlb);
                }
                CloseClipboard();
            }

            if (Buffer != NULL) {
                // strip trailing new line characters
                INT i;
                for (i = StringLen(Buffer)-1;
                        i >= 0 && (Buffer[i] == TEXT('\r') || Buffer[i] == TEXT('\n'));
                        i--)
                    Buffer[i] = 0;

#if defined _UNICODE
                {
                    SETTEXTEX stt;

                    stt.codepage = CP_UNICODE;
                    stt.flags = ST_SELECTION;
                    SendMessage(hWndRtf,EM_SETTEXTEX,(WPARAM)&stt,(LPARAM)Buffer);
                }
#else
                SendMessage(hWndRtf, EM_REPLACESEL, FALSE, (LPARAM)Buffer);
#endif


                free(Buffer);
            }
        }

        return (Disallow ? TRUE : FALSE);
    } else if (nmhdr->code == EN_LINK) {
        // should really fire on up
        // but that screws up the cursor position

        ENLINK* enl = (ENLINK*) nmhdr;
        if (enl->msg == WM_LBUTTONDOWN) {
            TEXTRANGE tr;
            TCHAR Buffer[1000];
            tr.lpstrText = Buffer;
            tr.chrg.cpMin = enl->chrg.cpMin;
            tr.chrg.cpMax = enl->chrg.cpMax;

            SendMessage(hWndRtf, EM_GETTEXTRANGE, 0, (LPARAM) &tr);
            ExecuteFile(Buffer);

            return TRUE;
        }
    } else if (nmhdr->code == EN_MSGFILTER) {
        MSGFILTER* mf = (MSGFILTER*) nmhdr;
#if 0
        //if (mf->msg == WM_CHAR && Running) {
        if (mf->msg == WM_CHAR && 0) {
            WinGHCiReceiveC((TCHAR)mf->wParam == TEXT('\r') ? TEXT('\n') : mf->wParam);
            SetWindowLong(hDlg, DWL_MSGRESULT, 1);
            return FALSE;
        } //else if (Running && mf->msg == WM_KEYDOWN) {
        else if (0) {
            SHORT n = GetKeyState(VK_CONTROL);
            BOOL Control = (n & (1 << 16));
            if(((CHAR)(mf->wParam) ==(CHAR)TEXT('C')) && Control)
                AbortExecution();
            else
                SetWindowLong(hDlg, DWL_MSGRESULT, 1);
            return FALSE;
        } //else if (mf->msg == WM_KEYDOWN && !Running) {
        else
#endif


            if (mf->msg == WM_CHAR) {

                if (mf->wParam == VK_TAB) {

                    INT pos;

                    if(FindFirst) {
                        RtfWindowGetCommand(FindWhat,BUFF_LEN);
                        pos = FindFirstHistory(FindWhat);
                        FindFirst = FALSE;
                    } else
                        pos = FindNextHistory();

                    if(pos>=0)
                        RtfWindowSetCommand(GoToHistory(pos));
                    else
                        MessageBeep((UINT)-1);

                    return TRUE;

                } else {
                    // any other key resets search
                    FindFirst = TRUE;

                    if (mf->wParam == VK_ESCAPE) {

                        //Clear current command
                        RtfWindowSetCommand(TEXT(""));
                        // Go to last item in history
                        AddHistory(TEXT(""));
                        return TRUE;
                    } else {
                        return FALSE;
                    }
                }


            } else if (mf->msg == WM_KEYDOWN) {
                BOOL History = (mf->wParam == VK_UP || mf->wParam == VK_DOWN);
                SHORT n = GetKeyState(VK_CONTROL);
                BOOL Control = (n & (1 << 16));

                if(((CHAR)(mf->wParam) ==(CHAR)TEXT('C')) && Control) {
                    if(RtfWindowCanCutCopy() && DROPEFFECT_COPY)
                        RtfWindowClipboard(WM_COPY);
                    else
                        AbortExecution();
                } else if (History && (mf->lParam & (1 << 24))) {
                    CHARRANGE cr;
                    SendMessage(hWndRtf, EM_EXGETSEL, 0, (LPARAM) &cr);
                    if ((DWORD) cr.cpMin >= StartOfInput) {
                        RtfWindowRelativeHistory(mf->wParam == VK_UP ? -1 : +1);
                        return TRUE;
                    }
                } else if (mf->wParam == VK_RETURN) {
#define BUFF_LEN 2048
                    TCHAR Buffer[BUFF_LEN];


                    RtfWindowGetCommand(Buffer,BUFF_LEN);

                    if(Running) {
                        if(!(mf->lParam & (1<<30))) //avoid repetition
                            FireCommandExt(Buffer,FALSE,TRUE,FALSE,FALSE);
                    }
                    else
                        //if(!(mf->lParam & (1<<30)))
                        FireAsyncCommand(Buffer);
                    return TRUE;
                } else if (mf->wParam == VK_HOME) {
                    CHARRANGE cr;
                    SendMessage(hWndRtf, EM_EXGETSEL, 0, (LPARAM) &cr);
                    if ((DWORD) cr.cpMin >= StartOfInput) {
                        SHORT n = GetKeyState(VK_SHIFT);
                        BOOL Shift = (n & (1 << 16));

                        cr.cpMin = StartOfInput;
                        cr.cpMax = (Shift ? cr.cpMax : StartOfInput);
                        SendMessage(hWndRtf, EM_EXSETSEL, 0, (LPARAM) &cr);
                        return TRUE;
                    }
                }
            }
    } else if (nmhdr->code == EN_SELCHANGE) {
        EnableButtons();
        return FALSE;
    }

    return FALSE;
}