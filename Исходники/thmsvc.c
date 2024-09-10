static VOID CALLBACK
ServiceMain(DWORD argc, LPWSTR *argv)
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    TRACE("ServiceMain() called\n");

    ServiceStatusHandle = RegisterServiceCtrlHandlerExW(ServiceName,
                                                        ServiceControlHandler,
                                                        NULL);

    TRACE("Calling SetServiceStatus()\n");
    UpdateServiceStatus(SERVICE_RUNNING);
    TRACE("SetServiceStatus() called\n");

    ThemeHooksInstall();

    TRACE("ServiceMain() done\n");
}