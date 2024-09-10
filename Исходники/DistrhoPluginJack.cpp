static void initSignalHandler()
{
    SetConsoleCtrlHandler(winSignalHandler, TRUE);
}