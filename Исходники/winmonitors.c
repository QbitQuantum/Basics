Bool QueryMonitor(int index, struct GetMonitorInfoData *data)
{
    /* prepare data */
    if (data == NULL)
        return FALSE;
    memset(data, 0, sizeof(*data));
    data->requestedMonitor = index;

    /* query information */
    return EnumDisplayMonitors(NULL, NULL, getMonitorInfo, (LPARAM) data);
}