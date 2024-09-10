int _tmain (int argc, LPTSTR argv [])
{
    SERVICE_TABLE_ENTRYW ServiceTable[] =
    {
        {ServiceName, ServiceMain},
        {NULL,        NULL }
    };

    if (InitLogging())
    {
        if (!StartServiceCtrlDispatcherW(ServiceTable))
            LogEvent(L"failed to start the service control dispatcher", GetLastError(), 101, LOG_ALL);

        UninitLogging();
    }

    return 0;
}