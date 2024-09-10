WORD
MNetSessionGetInfo(
    LPTSTR pszServer,
    LPTSTR pszClientName,
    DWORD nLevel,
    LPBYTE * ppbBuffer)
{
    DWORD   nRes;  // return from Netapi

    nRes = NetSessionGetInfo(pszServer, pszClientName, L"", nLevel,
        ppbBuffer);

    if (nRes == NERR_Success)
    {
        LPTSTR pszDesc;
        switch (nLevel)
        {
        case 0:
        default:
            pszDesc = pszDesc_session_info_0;
            break;
        case 1:
            pszDesc = pszDesc_session_info_1;
            break;
        case 2:
            pszDesc = pszDesc_session_info_2;
            break;
        case 10:
            pszDesc = pszDesc_session_info_10;
            break;
        }
    }

    return LOWORD(nRes);
}