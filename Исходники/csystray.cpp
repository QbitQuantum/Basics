HRESULT CSysTray::SysTrayThreadProc()
{
    WCHAR strFileName[MAX_PATH];
    GetModuleFileNameW(g_hInstance, strFileName, MAX_PATH);
    HMODULE hLib = LoadLibraryW(strFileName);

    CoInitializeEx(NULL, COINIT_DISABLE_OLE1DDE | COINIT_APARTMENTTHREADED);

    Create(NULL);

    HRESULT ret = SysTrayMessageLoop();

    CoUninitialize();

    FreeLibraryAndExitThread(hLib, ret);
}