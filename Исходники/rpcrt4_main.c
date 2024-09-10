/******************************************************************************
 * DceErrorInqTextA   (rpcrt4.@)
 */
RPC_STATUS RPC_ENTRY DceErrorInqTextA (RPC_STATUS e, RPC_CSTR buffer)
{
    RPC_STATUS status;
    WCHAR bufferW [MAX_RPC_ERROR_TEXT];
    if ((status = DceErrorInqTextW (e, bufferW)) == RPC_S_OK)
    {
        if (!WideCharToMultiByte(CP_ACP, 0, bufferW, -1, (LPSTR)buffer, MAX_RPC_ERROR_TEXT,
                NULL, NULL))
        {
            ERR ("Failed to translate error\n");
            status = RPC_S_INVALID_ARG;
        }
    }
    return status;
}