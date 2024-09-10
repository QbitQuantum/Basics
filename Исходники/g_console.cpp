void __stdcall LoggerCore(PVOID pVoid)
{
    char Temp[1024];
    // ----
    AllocConsole();
    SetConsoleTitleA(CONSOLETITLE);
    // ----
    while(true)
    {
        Sleep(100);
        g_Console.AddMessageToConsole(Temp);
        g_Console.LoadConsoleCommands(Temp);
    }
}