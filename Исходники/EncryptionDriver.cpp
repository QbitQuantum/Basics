DWORD
CEncryptionDriver::WaitForNotification(_Out_ /*PUCA_NOTIFICATION*/ PVOID *Notification,
                                       _Out_ LPDWORD lpdwBufferSize)
{
#if 0
    UCA_FLT_QUERY_MESSAGE QueryMessage;
    UCA_FLT_GET_MESSAGE RequestMessage;
    UCA_NOTIFICATION_INFO NotificationInfo;
    DWORD BytesReturned;
    HRESULT hResult;
    DWORD dwError;

    TRACE_ENTER(TraceHandle);

    if (!Notification || !lpdwBufferSize) return ERROR_INVALID_PARAMETER;

    *Notification = NULL;
    *lpdwBufferSize = 0;

    /* Request the next message info */
    QueryMessage.Header.Message = FLT_GET_NEXT_MESSAGE;

    /* This call blocks, so set the cancel IO event */
    QueryMessage.Header.hCancelIo = m_hCancelIo;

    /* Send the message to the driver */
    hResult = FilterSendMessage(m_hPort,
                                &QueryMessage,
                                sizeof(UCA_FLT_QUERY_MESSAGE),
                                &NotificationInfo,
                                sizeof(UCA_NOTIFICATION_INFO),
                                &BytesReturned);
    if (hResult != S_OK)
    {
        TRACE_ERROR(TraceHandle, "Failed to send a query message to the driver : %X", hResult);
        return SCODE_CODE(hResult);
    }

    TRACE_INFO(TraceHandle, "Handle is %X", NotificationInfo.NotificationHandle);
    TRACE_INFO(TraceHandle, "Allocating %lu bytes", NotificationInfo.NotificationSize);

    /* Allocate memory to hold the data */
    *Notification = (PUCA_NOTIFICATION)HeapAlloc(GetProcessHeap(),
                                                 0,
                                                 NotificationInfo.NotificationSize);
    if (*Notification == NULL) return ERROR_NOT_ENOUGH_MEMORY;

    /* Set the header to actually get the message */
    RequestMessage.Header.Message = FLT_GET_MESSAGE;
    RequestMessage.Header.hCancelIo = NULL;

    /* Set the handle to the data we want */
    RequestMessage.NotificationHandle = NotificationInfo.NotificationHandle;

    /* Send the message to the driver */
    hResult = FilterSendMessage(m_hPort,
                                &RequestMessage,
                                sizeof(UCA_FLT_GET_MESSAGE),
                                *Notification,
                                NotificationInfo.NotificationSize,
                                &BytesReturned);
    if (hResult == S_OK)
    {
        /* Store the buffer size */
        *lpdwBufferSize = NotificationInfo.NotificationSize;
        dwError = ERROR_SUCCESS;
    }
    else
    {
        /* Cleanup */
        TRACE_ERROR(TraceHandle, "Failed to send a get message to the driver : %X", hResult);
        dwError = SCODE_CODE(hResult);
        HeapFree(GetProcessHeap(), 0, *Notification);
        *Notification = NULL;
    }

    TRACE_EXIT(TraceHandle);
#endif
    return 0;//dwError;
}