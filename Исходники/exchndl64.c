BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            OnStartup();
            break;

        case DLL_PROCESS_DETACH:
            OnExit();
            break;
    }

    return TRUE;
}