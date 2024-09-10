static int
_ecore_wince_hardware_keys_register(HWND window)
{
    HINSTANCE           core_dll;
    UnregisterFunc1Proc unregister_fct;
    int                 i;

    core_dll = LoadLibrary(L"coredll.dll");
    if (!core_dll)
    {
        ERR("LoadLibrary() failed");
        return 0;
    }

    unregister_fct = (UnregisterFunc1Proc)GetProcAddress(core_dll, L"UnregisterFunc1");
    if (!unregister_fct)
    {
        ERR("GetProcAddress() failed");
        FreeLibrary(core_dll);
        return 0;
    }

    for (i = 0xc1; i <= 0xcf; i++)
    {
        unregister_fct(MOD_WIN, i);
        RegisterHotKey(window, i, MOD_WIN, i);
    }

    FreeLibrary(core_dll);

    return 1;
}