static bool win_grab_mouse(ALLEGRO_DISPLAY *display)
{
    ALLEGRO_SYSTEM_WIN *system = (void *)al_get_system_driver();
    ALLEGRO_DISPLAY_WIN *win_disp = (void *)display;
    RECT rect;

    GetWindowRect(win_disp->window, &rect);
    if (ClipCursor(&rect) != 0) {
        system->mouse_grab_display = display;
        return true;
    }

    return false;
}