RTDECL(int) RTHandleGetStandard(RTHANDLESTD enmStdHandle, PRTHANDLE ph)
{
    /*
     * Validate and convert input.
     */
    AssertPtrReturn(ph, VERR_INVALID_POINTER);
    DWORD dwStdHandle;
    switch (enmStdHandle)
    {
        case RTHANDLESTD_INPUT:  dwStdHandle = STD_INPUT_HANDLE; break;
        case RTHANDLESTD_OUTPUT: dwStdHandle = STD_OUTPUT_HANDLE; break;
        case RTHANDLESTD_ERROR:  dwStdHandle = STD_ERROR_HANDLE; break;
        default:
            AssertFailedReturn(VERR_INVALID_PARAMETER);
    }

    /*
     * Is the requested descriptor valid and which IPRT handle type does it
     * best map on to?
     */
    HANDLE hNative = GetStdHandle(dwStdHandle);
    if (hNative == INVALID_HANDLE_VALUE)
        return RTErrConvertFromWin32(GetLastError());

    DWORD dwInfo;
    if (!GetHandleInformation(hNative, &dwInfo))
        return RTErrConvertFromWin32(GetLastError());
    bool const fInherit = RT_BOOL(dwInfo & HANDLE_FLAG_INHERIT);

    RTHANDLE h;
    DWORD    dwType = GetFileType(hNative);
    switch (dwType & ~FILE_TYPE_REMOTE)
    {
        default:
        case FILE_TYPE_UNKNOWN:
        case FILE_TYPE_CHAR:
        case FILE_TYPE_DISK:
            h.enmType = RTHANDLETYPE_FILE;
            break;

        case FILE_TYPE_PIPE:
        {
            DWORD cMaxInstances;
            DWORD fInfo;
            if (!GetNamedPipeInfo(hNative, &fInfo, NULL, NULL, &cMaxInstances))
                h.enmType = RTHANDLETYPE_SOCKET;
            else
                h.enmType = RTHANDLETYPE_PIPE;
            break;
        }
    }

    /*
     * Create the IPRT handle.
     */
    int rc;
    switch (h.enmType)
    {
        case RTHANDLETYPE_FILE:
            rc = RTFileFromNative(&h.u.hFile, (RTHCUINTPTR)hNative);
            break;

        case RTHANDLETYPE_PIPE:
            rc = RTPipeFromNative(&h.u.hPipe, (RTHCUINTPTR)hNative,
                                    (enmStdHandle == RTHANDLESTD_INPUT ? RTPIPE_N_READ : RTPIPE_N_WRITE)
                                  | (fInherit ? RTPIPE_N_INHERIT : 0));
            break;

        case RTHANDLETYPE_SOCKET:
            rc = rtSocketCreateForNative(&h.u.hSocket, (RTHCUINTPTR)hNative);
            break;

        default: /* shut up gcc */
            return VERR_INTERNAL_ERROR;
    }

    if (RT_SUCCESS(rc))
        *ph = h;

    return rc;
}