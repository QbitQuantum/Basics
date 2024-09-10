int __cdecl wmain (int argc, WCHAR* args[])
{
    wint_t iChar = 0 ;
    g_AppInfo = new CAppInfo(L"Memory Corruption Sample", L"1.0" );
    if(!g_AppInfo)
    {
        return 1;
    }

    wprintf(L"Press: \n");
    wprintf(L"    1    To display application information\n");
    wprintf(L"    2    To simulated memory corruption\n");
    wprintf(L"    3    To exit\n\n\n>");

    while((iChar=_getwche())!='3')
    {
        switch(iChar)
        {
            case '1':
               g_AppInfo->PrintAppInfo();
               break;

            case '2':
              SimulateMemoryCorruption();
              wprintf(L"\nMemory Corruption completed\n");
              break;

            default:
              wprintf(L"\nInvalid option\n");
        }
        wprintf(L"\n\n> ");
    }
    return 0;
}