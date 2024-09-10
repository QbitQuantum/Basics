/* Initialize the service table for a list (REG_MULTI_SZ) of services */
static BOOL StartGroupServices(LPWSTR services)
{
    LPWSTR service_name = NULL;
    SERVICE_TABLE_ENTRYW *service_table = NULL;
    DWORD service_count;
    BOOL ret;

    /* Count the services to load */
    service_count = 0;
    service_name = services;
    while (*service_name != '\0')
    {
        ++service_count;
        service_name = service_name + lstrlenW(service_name);
        ++service_name;
    }
    WINE_TRACE("Service group contains %d services\n", service_count);

    /* Populate the service table */
    service_table = HeapAlloc(GetProcessHeap(), 0,
            (service_count + 1) * sizeof(SERVICE_TABLE_ENTRYW));
    service_count = 0;
    service_name = services;
    while (*service_name != '\0')
    {
        if (!AddServiceElem(service_name, &service_table[service_count]))
        {
            HeapFree(GetProcessHeap(), 0, service_table);
            return FALSE;
        }
        ++service_count;
        service_name = service_name + lstrlenW(service_name);
        ++service_name;
    }
    service_table[service_count].lpServiceName = NULL;
    service_table[service_count].lpServiceProc = NULL;

    /* Start the services */
    if (!(ret = StartServiceCtrlDispatcherW(service_table)))
        WINE_ERR("StartServiceCtrlDispatcherW failed to start %s: %u\n",
                wine_dbgstr_w(services), GetLastError());

    HeapFree(GetProcessHeap(), 0, service_table);
    return ret;
}