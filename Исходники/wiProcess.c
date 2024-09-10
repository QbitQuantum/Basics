// ================================================================================================
// FUNCTION  : wiProcess_Close()
// ------------------------------------------------------------------------------------------------
// ================================================================================================
wiStatus wiProcess_Close(void)
{
    if (!ModuleIsInitialized) return STATUS(WI_ERROR_MODULE_NOT_INITIALIZED);

    #ifdef WISE_BUILD_MULTITHREADED

        #if defined WISE_USE_PTHREADS

            // nothing to do

        #elif defined WIN32 
        {
            LPVOID lpvData = TlsGetValue(dwTlsIndex); 
            LocalFree((HLOCAL)lpvData);
            TlsFree(dwTlsIndex);
        }
        #endif
    #endif

    ModuleIsInitialized = WI_FALSE;
    return WI_SUCCESS;
}