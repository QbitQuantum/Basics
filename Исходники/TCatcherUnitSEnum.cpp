static void __fastcall KillDialog(HWND hh) {
//-------------------------------------------------------------------------------
//          Убивает диалоговое окно автокада - с целью его продвижения          |
//-------------------------------------------------------------------------------
//    DestroyWindow(hh);

//    DWORD CurId, DlgId;
//    CurId = ::GetCurrentThreadId();
//    DlgId = ::GetWindowThreadProcessId(hh, NULL);
//    ::AttachThreadInput(CurId, DlgId, TRUE);
//    ::SetFocus(hh);

    RECT wr;
    int x, y;

    ::GetWindowRect(hh, &wr);
    x = (wr.left + wr.right) / 2; y = wr.top + 5;
    ::SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); aWait(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0); aWait(20);

    aWait(100);
    if (SpecCatcherMode) {
        keybd_event(VK_RETURN, 0, 0, 0); aWait(30);
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); aWait(30);
    } else {
        keybd_event(VK_ESCAPE, 0, 0, 0); aWait(30);
        keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0); aWait(30);
    }
}