void CDebugger::Hook(DWORD dwProcessId) {
    if (!m_pFuzz->m_bHook) {
        return;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);

    // Load symbol
    m_pSymbols->RefreshSymbols(hProcess);
    SymLoadModuleEx(hProcess, NULL, m_pModulePath, NULL, m_dwBaseOfDll,  0,  NULL, 0);
    cout << "mod: " << m_pModulePath << "addr: " << m_dwBaseOfDll << endl;

    // Find api address
    PSYMBOL_INFO pSymInfo = m_pSymbols->SymbolFromName(m_pFuzz->m_pHookApi);
    if (pSymInfo) {
        cout << "[+] Address of " << pSymInfo->Name << ": " << pSymInfo->Address << endl;
    } else {
        cout << "[-] Address of " << m_pFuzz->m_pHookApi << " not found!" << endl;
        return;
    }

    unsigned int iHookAddr = (unsigned int)pSymInfo->Address;

    // Hook api address
    SIZE_T iWriteBytes;

    bool bSuccess = WriteProcessMemory(hProcess, (void*)iHookAddr, (void*)m_pFuzz->m_pHookCode, sizeof(m_pFuzz->m_pHookCode), &iWriteBytes);
    if (bSuccess) {
        cout << "[+] Hook success at" << iHookAddr << endl;
    } else {
        cout << "[-] Hook failed at" << iHookAddr << endl;
    }
}