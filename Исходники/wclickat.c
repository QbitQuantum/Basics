static void do_click(HWND window, DWORD down, DWORD up)
{
    WINDOWINFO window_info;
    long x, y;

    SetForegroundWindow(GetParent(window));
    window_info.cbSize=sizeof(window_info);
    GetWindowInfo(window, &window_info);

    /* The calculations below convert the coordinates so they are absolute
     * screen coordinates in 'Mickeys' as required by mouse_event.
     * In mickeys the screen size is always 65535x65535.
     */
    x=window_info.rcWindow.left+g_x;
    if (x<window_info.rcWindow.left || x>=window_info.rcWindow.right)
        x=(window_info.rcWindow.right+window_info.rcWindow.left)/2;
    x=(x << 16)/GetSystemMetrics(SM_CXSCREEN);

    y=window_info.rcWindow.top+g_y;
    if (y<window_info.rcWindow.top || y>=window_info.rcWindow.bottom)
        y=(window_info.rcWindow.bottom+window_info.rcWindow.top)/2;
    y=(y << 16)/GetSystemMetrics(SM_CYSCREEN);

    mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x, y, 0, 0);
    if (down) {
        mouse_event(MOUSEEVENTF_ABSOLUTE | down, x, y, 0, 0);
        if ((g_dragto_x > 0) && (g_dragto_y > 0)) {
            int i;
            long dx, dy;
            long step_per_x, step_per_y;
            long dragto_x, dragto_y;

            dragto_x=window_info.rcWindow.left+g_dragto_x;
            if (dragto_x<window_info.rcWindow.left || dragto_x>=window_info.rcWindow.right)
                dragto_x=(window_info.rcWindow.right+window_info.rcWindow.left)/2;
            dragto_x=(dragto_x << 16)/GetSystemMetrics(SM_CXSCREEN);

            dragto_y=window_info.rcWindow.top+g_dragto_y;
            if (dragto_y<window_info.rcWindow.top || dragto_y>=window_info.rcWindow.bottom)
                dragto_y=(window_info.rcWindow.bottom+window_info.rcWindow.top)/2;
            dragto_y=(dragto_y << 16)/GetSystemMetrics(SM_CYSCREEN);

            dx = g_dragto_x - g_x;
            dy = g_dragto_y - g_y;
            step_per_x = dx / 4;
            step_per_y = dy / 4;
            for (i = 0; i < 4; i++) {
                mouse_event(MOUSEEVENTF_MOVE, step_per_x, step_per_y, 0, 0);
            }
            x=dragto_x;
            y=dragto_y;
        }
    }
    if (up)
       mouse_event(MOUSEEVENTF_ABSOLUTE | up, x, y, 0, 0);
}