// For the CoreClr, this is the real DLL entrypoint. We make ourselves the first entrypoint as
// we need to capture coreclr's hInstance before the C runtine initializes. This function
// will capture hInstance, let the C runtime initialize and then invoke the "classic"
// DllMain that initializes everything else.
extern "C" BOOL WINAPI CoreDllMain(HANDLE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    STATIC_CONTRACT_NOTHROW;

    BOOL result;
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
#ifndef FEATURE_PAL        
            // Make sure the /GS security cookie is initialized before we call anything else.
            // BinScope detects the call to __security_init_cookie in its "Has Non-GS-friendly
            // Initialization" check and makes it pass.
            __security_init_cookie();
#endif // FEATURE_PAL        

            // It's critical that we invoke InitUtilCode() before the CRT initializes. 
            // We have a lot of global ctors that will break if we let the CRT initialize without
            // this step having been done.

            CoreClrCallbacks cccallbacks;
            cccallbacks.m_hmodCoreCLR               = (HINSTANCE)hInstance;
            cccallbacks.m_pfnIEE                    = IEE;
            cccallbacks.m_pfnGetCORSystemDirectory  = GetCORSystemDirectoryInternal;
            cccallbacks.m_pfnGetCLRFunction         = GetCLRFunction;
            InitUtilcode(cccallbacks);

            if (!(result = _CRT_INIT(hInstance, dwReason, lpReserved)))
            {
                // CRT_INIT may fail to initialize the CRT heap. Make sure we don't continue 
                // down a path that would trigger an AV and tear down the host process
                break;
            }
            result = DllMain(hInstance, dwReason, lpReserved);
            break;
        
        case DLL_THREAD_ATTACH:
            _CRT_INIT(hInstance, dwReason, lpReserved);
            result = DllMain(hInstance, dwReason, lpReserved);
            break;

        case DLL_PROCESS_DETACH: // intentional fallthru
        case DLL_THREAD_DETACH:
            result = DllMain(hInstance, dwReason, lpReserved);
            _CRT_INIT(hInstance, dwReason, lpReserved);
            break;

        default:
            result = FALSE;  // it'd be an OS bug if we got here - not much we can do.
            break;   
    }
    return result;
}