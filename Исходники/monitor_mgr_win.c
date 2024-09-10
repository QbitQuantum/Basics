MonitorManager *monitor_mgr_create()
{
    MonitorManager *mgr = malloc(sizeof(MonitorManager*));
    mgr->monitor_count = 0;
    mgr->monitors = NULL;

    EnumDisplayMonitors(0, NULL, callback, (LPARAM)mgr);

    return mgr;
}