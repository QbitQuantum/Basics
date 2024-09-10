NET_API_STATUS
WINAPI
NetRemoteTOD(
    LPCWSTR UncServerName,
    LPBYTE *BufferPtr)
{
    NET_API_STATUS status;

    TRACE("NetRemoteTOD(%s, %p)\n", debugstr_w(UncServerName),
          BufferPtr);

    *BufferPtr = NULL;

    RpcTryExcept
    {
        status = NetrRemoteTOD((SRVSVC_HANDLE)UncServerName,
                               (LPTIME_OF_DAY_INFO *)BufferPtr);
    }
    RpcExcept(EXCEPTION_EXECUTE_HANDLER)
    {
        status = I_RpcMapWin32Status(RpcExceptionCode());
    }
    RpcEndExcept;

    return status;
}