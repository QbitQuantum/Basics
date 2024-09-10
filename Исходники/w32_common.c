/**
 * \brief Update screen information.
 *
 * This function should be called in libvo's "control" callback
 * with parameter VOCTRL_UPDATE_SCREENINFO.
 * Note that this also enables the new API where geometry and aspect
 * calculations are done in video_out.c:config_video_out
 *
 * Global libvo variables changed:
 * xinerama_x
 * xinerama_y
 * vo_screenwidth
 * vo_screenheight
 */
void w32_update_xinerama_info(struct vo *vo)
{
    struct vo_w32_state *w32 = vo->w32;
    struct mp_vo_opts *opts = vo->opts;
    int screen = opts->fs ? opts->fsscreen_id : opts->screen_id;
    vo->xinerama_x = vo->xinerama_y = 0;
    if (opts->fs && screen == -2) {
        int tmp;
        vo->xinerama_x = GetSystemMetrics(SM_XVIRTUALSCREEN);
        vo->xinerama_y = GetSystemMetrics(SM_YVIRTUALSCREEN);
        tmp = GetSystemMetrics(SM_CXVIRTUALSCREEN);
        if (tmp) vo->opts->screenwidth = tmp;
        tmp = GetSystemMetrics(SM_CYVIRTUALSCREEN);
        if (tmp) vo->opts->screenheight = tmp;
    } else if (screen == -1) {
        MONITORINFO mi;
        HMONITOR m = MonitorFromWindow(w32->window, MONITOR_DEFAULTTOPRIMARY);
        mi.cbSize = sizeof(mi);
        GetMonitorInfoW(m, &mi);
        vo->xinerama_x = mi.rcMonitor.left;
        vo->xinerama_y = mi.rcMonitor.top;
        vo->opts->screenwidth = mi.rcMonitor.right - mi.rcMonitor.left;
        vo->opts->screenheight = mi.rcMonitor.bottom - mi.rcMonitor.top;
    } else if (screen >= 0) {
        w32->mon_cnt = 0;
        w32->mon_id = screen;
        EnumDisplayMonitors(NULL, NULL, mon_enum, (LONG_PTR)vo);
    }
    aspect_save_screenres(vo, vo->opts->screenwidth,
                          vo->opts->screenheight);
}