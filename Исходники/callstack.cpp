bool CallStack::loadAllModules()
{
#ifdef WIN32
    DWORD dwNeeded = 0;
    if (!EnumProcessModules(hProcess, hModule, sizeof(hModule), &dwNeeded)) return false;

    const int iCount = dwNeeded / sizeof(HMODULE);

    for (int i = 0; i < iCount; ++i)
    {
        MODULEINFO info;

        GetModuleInformation(hProcess, hModule[i], &info, sizeof(info));
        GetModuleFileNameEx(hProcess, hModule[i], szImageName, iMax);
        GetModuleBaseName(hProcess, hModule[i], szModuleName, iMax);

#ifdef X64
        SymLoadModule64(hProcess, hModule[i], szImageName, szModuleName, (DWORD64)info.lpBaseOfDll, info.SizeOfImage);
#else
        SymLoadModule(hProcess, hModule[i], szImageName, szModuleName, (DWORD)info.lpBaseOfDll, info.SizeOfImage);
#endif
    }
#endif
    return true;
}