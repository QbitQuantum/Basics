void setup(void)
{
    ewmh_init();
    screen = xcb_setup_roots_iterator(xcb_get_setup(dpy)).data;
    if (!screen)
        err("error: cannot aquire screen\n");

    screen_width = screen->width_in_pixels;
    screen_height = screen->height_in_pixels;
    root_depth = screen->root_depth;

    xcb_atom_t net_atoms[] = {ewmh->_NET_SUPPORTED,
                              ewmh->_NET_DESKTOP_NAMES,
                              ewmh->_NET_NUMBER_OF_DESKTOPS,
                              ewmh->_NET_CURRENT_DESKTOP,
                              ewmh->_NET_CLIENT_LIST,
                              ewmh->_NET_ACTIVE_WINDOW,
                              ewmh->_NET_WM_DESKTOP,
                              ewmh->_NET_WM_STATE,
                              ewmh->_NET_WM_STATE_FULLSCREEN,
                              ewmh->_NET_WM_WINDOW_TYPE,
                              ewmh->_NET_WM_WINDOW_TYPE_DOCK,
                              ewmh->_NET_WM_WINDOW_TYPE_NOTIFICATION,
                              ewmh->_NET_WM_WINDOW_TYPE_DIALOG,
                              ewmh->_NET_WM_WINDOW_TYPE_UTILITY,
                              ewmh->_NET_WM_WINDOW_TYPE_TOOLBAR};

    xcb_ewmh_set_supported(ewmh, default_screen, LENGTH(net_atoms), net_atoms);

    monitor_uid = desktop_uid = client_uid = 0;
    mon = last_mon = mon_head = mon_tail = NULL;

    bool xinerama_is_active = false;

    if (xcb_get_extension_data(dpy, &xcb_xinerama_id)->present) {
        xcb_xinerama_is_active_reply_t *xia = xcb_xinerama_is_active_reply(dpy, xcb_xinerama_is_active(dpy), NULL);
        if (xia != NULL) {
            xinerama_is_active = xia->state;
            free(xia);
        }
    }

    if (xinerama_is_active) {
        xcb_xinerama_query_screens_reply_t *xsq = xcb_xinerama_query_screens_reply(dpy, xcb_xinerama_query_screens(dpy), NULL);
        xcb_xinerama_screen_info_t *xsi = xcb_xinerama_query_screens_screen_info(xsq);
        int n = xcb_xinerama_query_screens_screen_info_length(xsq);
        PRINTF("number of monitors: %d\n", n);
        for (int i = 0; i < n; i++) {
            xcb_xinerama_screen_info_t info = xsi[i];
            xcb_rectangle_t rect = (xcb_rectangle_t) {info.x_org, info.y_org, info.width, info.height};
            add_monitor(&rect);
        }
        free(xsq);
    } else {
        warn("Xinerama is inactive");
        xcb_rectangle_t rect = (xcb_rectangle_t) {0, 0, screen_width, screen_height};
        add_monitor(&rect);
    }

    for (monitor_t *m = mon_head; m != NULL; m = m->next)
        add_desktop(m, NULL);

    ewmh_update_number_of_desktops();
    ewmh_update_desktop_names();
    rule_head = make_rule();
    frozen_pointer = make_pointer_state();
    get_pointer_position(&pointer_position);
    split_mode = MODE_AUTOMATIC;
}