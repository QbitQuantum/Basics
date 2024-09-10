void FreeMemory(HANDLE hProcess, void * buffer)
{
    if (hProcess && buffer)
    {
        VirtualFreeEx(hProcess, buffer, 0, MEM_RELEASE);
    }
}