static DWORD WINAPI QuitThread (void *pv)
{
    FreeLibraryAndExitThread((HMODULE)pv, 0);
#if _MSC_VER < 1400
    return 0; // never returns
#endif
}