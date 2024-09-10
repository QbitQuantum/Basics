static BOOL __stdcall
CryptSetKeyParam_done(BOOL retval,
                      HCRYPTKEY hKey,
                      DWORD dwParam,
                      BYTE *pbData,
                      DWORD dwFlags)
{
    DWORD err = GetLastError();
    int ret_addr = *((DWORD *) ((DWORD) &retval - 4));

    if (retval && !called_internally(ret_addr))
    {
        const char *data = NULL;
        int data_len = 0;
        DWORD block_len, len = 4;

        switch (dwParam)
        {
            case KP_IV:
                if (CryptGetKeyParam(hKey, KP_BLOCKLEN, (BYTE *) &block_len, &len, 0))
                {
                    data = (const char *) pbData;
                    data_len = block_len / 8;
                }
                break;
            case KP_PERMISSIONS:
            case KP_ALGID:
            case KP_PADDING:
            case KP_MODE:
            case KP_MODE_BITS:
                data = (const char *) pbData;
                data_len = 4;
                break;
            default:
                break;
        }

        message_logger_log(_T("CryptSetKeyParam"), (char *) &retval - 4, (DWORD) hKey,
            MESSAGE_TYPE_PACKET, MESSAGE_CTX_INFO, PACKET_DIRECTION_INVALID,
            NULL, NULL, data, data_len,
            _T("hKey=0x%p, dwParam=%s, dwFlags=0x%08x"),
            hKey, key_param_to_string(dwParam), dwFlags);
    }

    SetLastError(err);
    return retval;
}