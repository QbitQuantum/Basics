/* DLL entry point */
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    BOOL ret=TRUE;

    switch(fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        set_tls_i(TlsAlloc());
        ret = (get_tls_i()!=TLS_OUT_OF_INDEXES);
        break;

    case DLL_PROCESS_DETACH:
        if (get_tls_i()!=TLS_OUT_OF_INDEXES) TlsFree(get_tls_i());
        break;
    }

    return ret;
}