CDesktopIconManager::CDesktopIconManager()
: m_hProcess(NULL)
, m_hwnd(NULL)
, m_lpMem(NULL)
{
    // Find the icon container window
    m_hwnd = GetTopWindow(GetTopWindow(FindWindow(_T("Progman"), NULL)));
    if (m_hwnd == NULL) return;

    // Get shell process id
    DWORD dwPid;
    GetWindowThreadProcessId(m_hwnd, &dwPid);

    // Open shell process
    m_hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, dwPid);
    if (m_hProcess == NULL) {
        m_hwnd = NULL;
        return;
    }

    // Allocate one page in shell's address space
    m_lpMem = VirtualAllocEx(m_hProcess, NULL, 4096, MEM_COMMIT, PAGE_READWRITE);
    if (m_lpMem == NULL) {
        CloseHandle(m_hProcess);
        m_hProcess = NULL;
        m_hwnd = NULL;
    }
}