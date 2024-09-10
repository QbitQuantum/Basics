QString CCrashStack::GetModuleByRetAddr(PBYTE Ret_Addr, PBYTE & Module_Addr)
{
    MODULEENTRY32	M = {sizeof(M)};
    HANDLE	hSnapshot;

    wchar_t Module_Name[MAX_PATH] = {0};

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);

    if ((hSnapshot != INVALID_HANDLE_VALUE) &&
            Module32First(hSnapshot, &M))
    {
            do
            {
                    if (DWORD(Ret_Addr - M.modBaseAddr) < M.modBaseSize)
                    {
                            lstrcpyn(Module_Name, M.szExePath, MAX_PATH);
                            Module_Addr = M.modBaseAddr;
                            break;
                    }
            } while (Module32Next(hSnapshot, &M));
    }

    CloseHandle(hSnapshot);

    QString sRet = QString::fromWCharArray(Module_Name);
    return sRet;
}