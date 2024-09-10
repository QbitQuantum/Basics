DWORD WindowsFirewallNotifyThreadStartRoutine(_In_ LPVOID lpThreadParameter)
{
    ASSERT(lpThreadParameter);

    UINT32         status      = NO_ERROR;
    THREAD_DATA*   pThreadData = (THREAD_DATA*)lpThreadParameter;
    SERVICE_NOTIFY svcNotify   = {0};

    HlprEventSet(pThreadData->threadStartEvent);

    svcNotify.dwVersion         = SERVICE_NOTIFY_STATUS_CHANGE;
    svcNotify.pfnNotifyCallback = WindowsFirewallNotification;
    svcNotify.pContext          = pWFNotifyThread;

    status = HlprServiceNotificationStateChangeRegister(L"MPSSvc",
             &svcNotify,
             SERVICE_NOTIFY_RUNNING,
             &scmHandle,
             &mpsSvcHandle);
    HLPR_BAIL_ON_FAILURE(status);

    status = WaitForSingleObjectEx(mpsSvcHandle,
                                   INFINITE,
                                   TRUE);
    if(status != WAIT_IO_COMPLETION)
    {
        if(status == WAIT_FAILED)
            status = GetLastError();

        HlprLogError(L"WindowsFirewallNotifyThreadStartRoutine : WaitForSingleObjectEx() [status: %#x]",
                     status);
    }

HLPR_BAIL_LABEL:

    HLPR_CLOSE_SERVICE_HANDLE(mpsSvcHandle);

    HLPR_CLOSE_SERVICE_HANDLE(scmHandle);

    return status;
}