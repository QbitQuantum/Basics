REDHAWK_PALEXPORT void __cdecl PalPrintf(_In_z_ _Printf_format_string_ const char * szFormat, ...)
{
#if defined(_DEBUG) 
    char buffer[8*1024];

    va_list args;
    va_start(args, szFormat);
    int cch = _vsprintf_s_l(buffer, COUNTOF(buffer), szFormat, NULL, args);

    // we have to use WriteConsole directly because the "app" CRT doesn't allow us to print to the console
    DWORD cchWritten;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, (DWORD)cch, &cchWritten, NULL);
#endif
}