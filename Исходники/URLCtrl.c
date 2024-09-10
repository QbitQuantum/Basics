BOOL urlctrl_set(HWND hwnd,TCHAR *szURL,COLORREF *unvisited,COLORREF *visited,DWORD dwFlags, COLORREF clr)
{   BOOL fResult=FALSE;
    if (IsWindow(hwnd)) {
        URLCTRL *url;
        if (GetWindowLong(hwnd,GWL_WNDPROC)==(LONG)urlctrl_proc) { //update old
            url=(URLCTRL*)GetWindowLong(hwnd,GWL_USERDATA);
        } else { //create new
            url=(URLCTRL*)this_malloc(sizeof(URLCTRL));
            if (url) { //init once
                HFONT hfont=(HFONT)SendMessage(hwnd,WM_GETFONT,0,0);
                url->oldproc=(WNDPROC)SetWindowLong(hwnd,GWL_WNDPROC,(LONG)urlctrl_proc);
                SetWindowLong(hwnd,GWL_USERDATA,(LONG)url);//store in control
                url->fClicking=FALSE;
                url->hcur=CreateCursor(GetModuleHandle(NULL),5,0,32,32,curAND,curXOR);
                SendMessage(hwnd,WM_SETFONT,(WPARAM)hfont,0);//modify current font
                url->bkg = clr;
            }
        }
        if (url) { //init always
            LONG style=GetWindowLong(hwnd,GWL_STYLE);
            if (szURL) lstrcpyn(url->szURL,szURL,MAX_PATH);
            else url->szURL[0]=0;
            url->crUnvisited=(unvisited)?(*unvisited):(RGB(0,0,255));
            url->crVisited=(visited)?(*visited):(RGB(128,0,128));
            //if(dwFlags&UCF_TXT_RIGHT) dwFlags&=~UCF_TXT_HCENTER;//patch
            //if(dwFlags&UCF_TXT_BOTTOM) dwFlags&=~UCF_TXT_VCENTER;//patch
            url->dwFlags=dwFlags;
            style&=~(WS_BORDER|WS_TABSTOP);//remove
            style|=SS_NOTIFY;//add
            if (url->dwFlags&UCF_KBD) style|=WS_TABSTOP;//add?
            SetWindowLong(hwnd,GWL_STYLE,style);
            if (url->dwFlags&UCF_FIT) util_url_fit(hwnd,FALSE);
            InvalidateRect(hwnd,NULL,TRUE);
            UpdateWindow(hwnd);
            fResult=TRUE;
        }
    }
    return fResult;
}