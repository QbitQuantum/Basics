NET_API_STATUS
WINAPI
NetWkstaTransportEnum(
    LPWSTR servername,
    DWORD level,
    LPBYTE *bufptr,
    DWORD prefmaxlen,
    LPDWORD entriesread,
    LPDWORD totalentries,
    LPDWORD resumehandle)
{
    WKSTA_TRANSPORT_ENUM_STRUCT TransportEnumInfo;
    WKSTA_TRANSPORT_INFO_0_CONTAINER Container0;
    NET_API_STATUS status;

    TRACE("NetWkstaTransportEnum(%s, %d, %p, %d, %p, %p, %p)\n", debugstr_w(servername),
          level, bufptr, prefmaxlen, entriesread, totalentries, resumehandle);

    TransportEnumInfo.Level = level;
    switch (level)
    {
        case 0:
            TransportEnumInfo.WkstaTransportInfo.Level0 = &Container0;
            Container0.EntriesRead = 0;
            Container0.Buffer = NULL;
            break;

        default:
            return ERROR_INVALID_PARAMETER;
    }

    RpcTryExcept
    {
        status = NetrWkstaTransportEnum(servername,
                                        &TransportEnumInfo,
                                        prefmaxlen,
                                        totalentries,
                                        resumehandle);
        if (status == NERR_Success || status == ERROR_MORE_DATA)
        {
            switch (level)
            {
                case 0:
                    *bufptr = (LPBYTE)TransportEnumInfo.WkstaTransportInfo.Level0->Buffer;
                    *entriesread = TransportEnumInfo.WkstaTransportInfo.Level0->EntriesRead;
                    break;
            }
        }
    }
    RpcExcept(EXCEPTION_EXECUTE_HANDLER)
    {
        status = I_RpcMapWin32Status(RpcExceptionCode());
    }
    RpcEndExcept;

    return status;
}