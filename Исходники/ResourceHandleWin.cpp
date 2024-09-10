static void __stdcall transferJobStatusCallback(HINTERNET internetHandle,
                                                DWORD_PTR jobId,
                                                DWORD internetStatus,
                                                LPVOID statusInformation,
                                                DWORD statusInformationLength)
{
#ifdef RESOURCE_LOADER_DEBUG
    char buf[64];
    _snprintf(buf, sizeof(buf), "status-callback: status=%u, job=%p\n",
              internetStatus, jobId);
    OutputDebugStringA(buf);
#endif

    UINT msg;
    LPARAM lParam;

    switch (internetStatus) {
    case INTERNET_STATUS_HANDLE_CREATED:
        // tell the main thread about the newly created handle
        msg = handleCreatedMessage;
        lParam = (LPARAM) LPINTERNET_ASYNC_RESULT(statusInformation)->dwResult;
        break;
    case INTERNET_STATUS_REQUEST_COMPLETE:
#ifdef RESOURCE_LOADER_DEBUG
        _snprintf(buf, sizeof(buf), "request-complete: result=%p, error=%u\n",
            LPINTERNET_ASYNC_RESULT(statusInformation)->dwResult,
            LPINTERNET_ASYNC_RESULT(statusInformation)->dwError);
        OutputDebugStringA(buf);
#endif
        // tell the main thread that the request is done
        msg = requestCompleteMessage;
        lParam = 0;
        break;
    case INTERNET_STATUS_REDIRECT:
        // tell the main thread to observe this redirect (FIXME: we probably
        // need to block the redirect at this point so the application can
        // decide whether or not to follow the redirect)
        msg = requestRedirectedMessage;
        lParam = (LPARAM) new StringImpl((const UChar*) statusInformation,
                                         statusInformationLength);
        break;
    case INTERNET_STATUS_USER_INPUT_REQUIRED:
        // FIXME: prompt the user if necessary
        ResumeSuspendedDownload(internetHandle, 0);
    case INTERNET_STATUS_STATE_CHANGE:
        // may need to call ResumeSuspendedDownload here as well
    default:
        return;
    }

    PostMessage(transferJobWindowHandle, msg, (WPARAM) jobId, lParam);
}