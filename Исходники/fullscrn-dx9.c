void SwitchToWindowedModeDx9(HWND hwnd)
{
    video_canvas_t *c;

    fullscreen_transition = 1;

    c = video_canvas_for_hwnd(hwnd);

    video_device_release_dx9(c);

    /* Create statusbar here to get correct dimensions for client window */
    statusbar_create(hwnd);
    ui_set_render_window(c, 0);

    LockWindowUpdate(hwnd);
    SetWindowLong(hwnd, GWL_STYLE, old_style);
    /* Restore  Menu */
    SetMenu(hwnd,old_menu);
    ui_show_menu();
    SetWindowPos(hwnd, HWND_NOTOPMOST, old_rect.left, old_rect.top, old_rect.right - old_rect.left, old_rect.bottom - old_rect.top, SWP_NOCOPYBITS);
    ShowCursor(TRUE);
    LockWindowUpdate(NULL);

    video_device_create_dx9(c, 0);
    video_canvas_refresh_all(c);

    fullscreen_transition = 0;
    c->refreshrate = old_refreshrate;
}