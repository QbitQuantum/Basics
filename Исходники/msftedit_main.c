/***********************************************************************
 * DllMain.
 */
BOOL WINAPI DllMain(HINSTANCE inst, DWORD reason, LPVOID reserved)
{
    static const WCHAR riched20W[] = {'r','i','c','h','e','d','2','0','.','d','l','l',0};
    static HMODULE richedit;

    switch(reason)
    {
    case DLL_WINE_PREATTACH:
        return FALSE; /* prefer native version */
    case DLL_PROCESS_ATTACH:
        /* explicitly load riched20 since it creates the window classes at dll attach time */
        richedit = LoadLibraryW( riched20W );
        DisableThreadLibraryCalls(inst);
        break;
    case DLL_PROCESS_DETACH:
        FreeLibrary( richedit );
        break;
    }
    return TRUE;
}