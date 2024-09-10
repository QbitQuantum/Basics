/* Print some "press enter" message, wait for that, exit. */
static void doExit(int code)
{
    /* set console codepage to OEM in case the process changed it to something else */
    SetConsoleOutputCP(GetOEMCP());
    puts(sleepMsg);
    _getch();
    exit(code);
}