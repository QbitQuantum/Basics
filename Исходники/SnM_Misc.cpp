// http://forum.cockos.com/showthread.php?p=612065
void SimulateMouseClick(COMMAND_T* _ct)
{
    POINT p;
    GetCursorPos(&p);
    mouse_event(MOUSEEVENTF_LEFTDOWN, p.x, p.y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, p.x, p.y, 0, 0);
    WinWaitForEvent(WM_LBUTTONUP);
}