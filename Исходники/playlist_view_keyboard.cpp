bool playlist_view::process_keydown(UINT msg, LPARAM lp, WPARAM wp, bool playlist, bool keyb)
{
    static_api_ptr_t<keyboard_shortcut_manager> keyboard_api;

    if (msg == WM_SYSKEYDOWN)
    {
        if (keyb && uie::window::g_process_keydown_keyboard_shortcuts(wp))
        {
            return true;
        }
    }
    else if (msg == WM_KEYDOWN)
    {
        if (keyb && uie::window::g_process_keydown_keyboard_shortcuts(wp))
        {
            return true;
        }
        if (wp == VK_TAB)
        {
            uie::window::g_on_tab(GetFocus());
#if 0
            HWND wnd_focus = GetFocus();
            HWND wnd_temp = GetParent(wnd_focus);

            while (GetWindowLong(wnd_temp, GWL_EXSTYLE) & WS_EX_CONTROLPARENT)
            {
                wnd_temp = GetParent(wnd_temp);
            }

            HWND wnd_next = GetNextDlgTabItem(wnd_temp, wnd_focus, (GetAsyncKeyState(VK_SHIFT) & KF_UP) ? TRUE : FALSE);

            if (wnd_next && wnd_next != wnd_focus) SetFocus(wnd_next);
#endif

        }
    }
    return false;
}