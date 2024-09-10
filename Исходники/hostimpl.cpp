BOOL STDMETHODCALLTYPE UtilExecutionEngine::ClrVirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect) 
{
    return VirtualProtect(lpAddress, dwSize, flNewProtect, lpflOldProtect);
}