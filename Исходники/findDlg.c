static LRESULT CALLBACK OwnerWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg == ID_FINDMSGSTRING) {
        return handle_findmsg((FINDREPLACEA*)lParam);
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}