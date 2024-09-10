static void
hippo_platform_impl_get_screen_info(HippoPlatform     *platform,
                                    HippoRectangle    *monitor_rect_p,
                                    HippoRectangle    *tray_icon_rect_p,
                                    HippoOrientation  *tray_icon_orientation_p)
{
    APPBARDATA abd;
    abd.cbSize = sizeof(abd);
    if (!SHAppBarMessage(ABM_GETTASKBARPOS, &abd)) {
        g_warning("Failed to get task bar extents");
        return;
    }

    HippoOrientation orientation;
    switch (abd.uEdge) {
        case ABE_BOTTOM:
        case ABE_TOP:
            orientation = HIPPO_ORIENTATION_HORIZONTAL;
            break;
        case ABE_LEFT:
        case ABE_RIGHT:
            orientation = HIPPO_ORIENTATION_VERTICAL;
            break;
        default:
            g_warning("unknown tray icon orientation");
            break;
    }

    if (tray_icon_orientation_p)
        *tray_icon_orientation_p = orientation;

    RECT iconTrayRect;

    if (!find_icon_tray_rect(&iconTrayRect, orientation)) {
        // If this starts happening  regularly, we can refine
        // this code to make a better guess at that point.
        iconTrayRect = abd.rc;
    }

    if (tray_icon_rect_p) {
        tray_icon_rect_p->x = iconTrayRect.left;
        tray_icon_rect_p->width = iconTrayRect.right - iconTrayRect.left;
        tray_icon_rect_p->y = iconTrayRect.top;
        tray_icon_rect_p->height = iconTrayRect.bottom - iconTrayRect.top;
    }

    if (monitor_rect_p) {
        HMONITOR monitor = MonitorFromRect(&iconTrayRect, MONITOR_DEFAULTTONEAREST);
        MONITORINFO monitorInfo;
        monitorInfo.cbSize = sizeof(monitorInfo);
        if (GetMonitorInfo(monitor, &monitorInfo)) {
            monitor_rect_p->x = monitorInfo.rcWork.left;
            monitor_rect_p->y = monitorInfo.rcWork.top;
            monitor_rect_p->width = monitorInfo.rcWork.right - monitorInfo.rcWork.left;
            monitor_rect_p->height = monitorInfo.rcWork.bottom - monitorInfo.rcWork.top;
        } else {
            g_warning("GetMonitorInfo failed"); // Shouldn't happen, don't both with a fallback
        }
    }
}