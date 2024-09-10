int addtooltip(control c, const char *tp)
{
    TOOLINFO ti;
    char *cc = (char*) &ti;
    int i, lim = sizeof (ti);
    for (i = 0; i++ < lim; *cc++ = 0);
    if (hwndToolTip == 0) {
        InitCommonControls();
    	hwndToolTip = CreateWindowEx(
           0,TOOLTIPS_CLASS,NULL,WS_POPUP|TTS_ALWAYSTIP,
           CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
           hwndFrame,NULL,this_instance,NULL);
        if(!hwndToolTip) return 0;
    }
    ti.cbSize = sizeof(ti);
    ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
    ti.hwnd = (HWND) c->parent->handle;
    ti.uId = (UINT_PTR) c->handle;
    ti.lpszText = (LPSTR) tp;
    return
    (SendMessage(hwndToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti)==TRUE)?
      1:0;
}