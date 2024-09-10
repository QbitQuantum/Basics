static BOOL TaskEnumFunc(const struct tasklist *p, LPARAM lParam)
{
    HWND hwnd = p->hwnd;
    Desk *f = (Desk*)lParam;
    int n;
    for (n = 0;;)
    {
        winStruct ws;
        memset(&ws, 0, sizeof ws);

        if (false == GetTaskLocation(hwnd, &ws.info))
            break;

        if (GetMonitorRect(hwnd, NULL, GETMON_FROM_WINDOW) != f->mon)
            break;

        ws.hwnd = hwnd;
        ws.iconic = FALSE != IsIconic(hwnd);
        ws.active = p->active;
        ws.index = 0;

        if (0 == ws.info.width && 0 == ws.info.height && !ws.iconic)
        {
            if (2 == ++n)
                break;
            hwnd = GetLastActivePopup(hwnd);
            continue;
        }

        winStruct *p = new winStruct(ws);
        p->next = f->winList;
        f->winList = p;

        ++f->winCount;
        break;
    }
    return TRUE;
}