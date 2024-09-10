VOID CALLBACK TflatButton::trackMouseTimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{
    RECT rect;
    POINT pt;
    GetClientRect(hwnd,&rect);
    MapWindowPoints(hwnd,NULL,(LPPOINT)&rect,2);
    GetCursorPos(&pt);
    if (!PtInRect(&rect,pt) || (WindowFromPoint(pt)!=hwnd)) {
        KillTimer(hwnd,idEvent);
        TflatButton *self=(TflatButton*)getDlgItem(hwnd);
        self->isMouse=false;
        InvalidateRect(hwnd,NULL,FALSE);
    }
}