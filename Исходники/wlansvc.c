int
wmain(int argc, WCHAR *argv[])
{
    SERVICE_TABLE_ENTRYW ServiceTable[2] =
    {
        {ServiceName, ServiceMain},
        {NULL, NULL}
    };

    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    DPRINT("wlansvc: main() started\n");

    StartServiceCtrlDispatcherW(ServiceTable);

    DPRINT("wlansvc: main() done\n");

    ExitThread(0);

    return 0;
}