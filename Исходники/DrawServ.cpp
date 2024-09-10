void CServiceModule::Run()
{
    HRESULT hr;

    _Module.dwThreadID = GetCurrentThreadId();

//  If you are running on NT 4.0 or higher you can use the following call
//  to make your service free threaded.
//  This means that calls come in on a random RPC thread
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

//  Otherwise, for single threaded use
//  hr = CoInitialize(NULL);

    ATLASSERT(SUCCEEDED(hr));

//  In NT 4.0 and higher where DCOM is supported you may wish to initialize
//  the security layer.  The following code will give you a DCOM service which
//  would allow ALL users access to objects
    CSecurityDescriptor sd;
    sd.InitializeFromThreadToken();

    hr = CoInitializeSecurity(NULL, -1, NULL, NULL,
                              RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_IDENTIFY, NULL, EOAC_NONE, NULL);
    ATLASSERT(SUCCEEDED(hr));

//  If you wish to have your object creatable remotely using DCOM use the following
    hr = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER, REGCLS_MULTIPLEUSE);
//  Otherwise, only local activation
//  hr = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE);
    ATLASSERT(SUCCEEDED(hr));

    LogEvent(_T("Service started"));
    SetServiceStatus(SERVICE_RUNNING);

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0))
        DispatchMessage(&msg);

    _Module.RevokeClassObjects();

    CoUninitialize();
}