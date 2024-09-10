BOOL
APIENTRY
EngUnmapFile(
    _In_ ULONG_PTR iFile)
{
    HANDLE hModule = (HANDLE)iFile;

    EngFreeModule(hModule);

    return TRUE;
}