int WriteC3CMemory(uint32_t lpAddress, void *buf, int len)
{
    if (hwnd) {
        DWORD pid;
        GetWindowThreadProcessId(hwnd, &pid);
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
        SIZE_T wlen;
        WriteProcessMemory(hProc, (void *) lpAddress, buf, len, &wlen);
        CloseHandle(hProc);
        if (len == wlen) {
            return TRUE;
        } else {
            fprintf(stderr, "Memory write error\n");
            return FALSE;
        }
    } else {
        return FALSE;
    }
}