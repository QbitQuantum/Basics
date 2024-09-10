LPBLOB
WSAAPI
getxyDataEnt(IN OUT PCHAR *Results,
             IN DWORD Length,
             IN LPSTR Name,
             IN LPCGUID Type,
             IN LPSTR *NewName)
{
    PWSAQUERYSETA WsaQuery = (PWSAQUERYSETA)*Results;
    INT ErrorCode;
    HANDLE RnRHandle;
    LPBLOB Blob = NULL;
    PVOID NewResults;

    /* Assume empty return name */
    if (NewName) *NewName = NULL;

    /* Set up the Winsock Service Query */
    RtlZeroMemory(WsaQuery, sizeof(*WsaQuery));
    WsaQuery->dwSize = sizeof(*WsaQuery);
    WsaQuery->lpszServiceInstanceName = Name;
    WsaQuery->lpServiceClassId = (LPGUID)Type;
    WsaQuery->dwNameSpace = NS_ALL;
    WsaQuery->dwNumberOfProtocols = 2;
    WsaQuery->lpafpProtocols = &afp[0];

    /* Send the Query Request to find a Service */
    ErrorCode = WSALookupServiceBeginA(WsaQuery,
                                       LUP_RETURN_BLOB | LUP_RETURN_NAME,
                                       &RnRHandle);

    if(ErrorCode == ERROR_SUCCESS) 
    {
        while (TRUE)
        {
            /* Service was found, send the real query */
            ErrorCode = WSALookupServiceNextA(RnRHandle,
                                              0,
                                              &Length,
                                              WsaQuery);

            /* Return the information requested */
            if(ErrorCode == ERROR_SUCCESS) 
            {
                /* Get the Blob and check if we have one */
                Blob = WsaQuery->lpBlob;
                if(Blob) 
                {
                    /* Did they want the name back? */
                    if(NewName) *NewName = WsaQuery->lpszServiceInstanceName;
                } 
                else 
                {
                    /* Check if this was a Hostname lookup */
                    if (Type == &HostnameGuid)
                    {
                        /* Return the name anyways */
                        if(NewName) *NewName = WsaQuery->lpszServiceInstanceName;
                    }
                    else
                    {
                        /* We don't have a blob, sorry */
                        ErrorCode = WSANO_DATA;
                    }
                }
            } 
            else 
            {
                /* WSALookupServiceEnd will set its own error, so save ours */
                ErrorCode = GetLastError();

                /* Check if we failed because of missing buffer space */
                if ((ErrorCode == WSAEFAULT) && (Length > RNR_BUFFER_SIZE))
                {
                    /* Allocate a new buffer */
                    NewResults = HeapAlloc(WsSockHeap, 0, Length);
                    if (NewResults)
                    {
                        /* Tell the caller his new buffer */
                        *Results = NewResults;

                        /* Update the WSA Query's location */
                        WsaQuery = (PWSAQUERYSETA)NewResults;

                        /* Loop again */
                        continue;
                    }
                    else
                    {
                        /* No memory to allocate the new buffer */
                        ErrorCode = WSA_NOT_ENOUGH_MEMORY;
                    }
                }
            }
        
            /* Finish the Query Request */
            WSALookupServiceEnd(RnRHandle);

            /* Now set the Last Error */
            if(ErrorCode != ERROR_SUCCESS) SetLastError(ErrorCode);

            /* Leave the loop */
            break;
        }
    }

    /* Return the blob */
    return Blob;
}