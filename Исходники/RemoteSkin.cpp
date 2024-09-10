extern "C" int WINAPI wWinMain(HINSTANCE hInstance, 
    HINSTANCE /*hPrevInstance*/, LPWSTR lpCmdLine, int /*nShowCmd*/)
{
    lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT

#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
    HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
    HRESULT hRes = CoInitialize(NULL);
#endif
    _ASSERTE(SUCCEEDED(hRes));
    _Module.Init(ObjectMap, hInstance, &LIBID_ATLLib);
    _Module.dwThreadID = GetCurrentThreadId();
   
    _Module.StartMonitor();
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
    hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
        REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED);
    _ASSERTE(SUCCEEDED(hRes));
    hRes = CoResumeClassObjects();
#else
    hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
       REGCLS_MULTIPLEUSE);
#endif
    _ASSERTE(SUCCEEDED(hRes));

    CMainDlg dlg;
    dlg.DoModal();

    _Module.RevokeClassObjects();
    Sleep(dwPause); //wait for any threads to finish

    _Module.Term();
    CoUninitialize();
    return 0;
}