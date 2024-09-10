int wmain(int argc, LPWSTR argv[])
{
    if (!StartServiceCtrlDispatcherW(ServiceTable))
    {
        DPRINT1("StartServiceCtrlDispatcherW() failed\n");
        return 1;
    }

    return 0;
}