//-----------------------------------------------------------------------------
// Thread callback
//-----------------------------------------------------------------------------
DWORD WINAPI HandlerAuxThreadProc(
    LPVOID lpParameter   // thread data
)
{
    
    IPCFuncCallHandler * pHandler = (IPCFuncCallHandler *) lpParameter;
    HANDLER_CALLBACK pfnCallback = pHandler->m_pfnCallback;
    
    DWORD dwErr = 0;
    DWORD dwWaitRet; 
    
    HANDLE lpHandles[] = {pHandler->m_hShutdownThread, pHandler->m_hStartEnum};
    DWORD dwHandleCount = 2;

    PAL_TRY
    {
    
        do {
            dwWaitRet = WaitForMultipleObjects(dwHandleCount, lpHandles, FALSE /*Wait Any*/, INFINITE);
            dwErr = GetLastError();
    
            // If we are in terminate mode then exit this helper thread.
            if (pHandler->m_fShutdownAuxThread)
                break;
            
            // Keep the 0th index for the terminate thread so that we never miss it
            // in case of multiple events. note that the ShutdownAuxThread flag above it purely 
            // to protect us against some bug in waitForMultipleObjects.
            if ((dwWaitRet-WAIT_OBJECT_0) == 0)
                break;

            // execute callback if wait succeeded
            if ((dwWaitRet-WAIT_OBJECT_0) == 1)
            {           
                (*pfnCallback)();
                            
                SetEvent(pHandler->m_hDoneEnum);
                dwErr = GetLastError();
            }
        } while (dwWaitRet != WAIT_FAILED);

    }
    PAL_FINALLY
    {
        if (!SetEvent (pHandler->m_hAuxThreadShutdown))
        {
            dwErr = GetLastError();
            _ASSERTE (!"HandlerAuxTHreadProc: SetEvent(m_hAuxThreadShutdown) failed");
        }
        FreeLibraryAndExitThread (pHandler->m_hCallbackModule, 0);
        // Above call doesn't return
    }
    PAL_ENDTRY

    return 0;
}