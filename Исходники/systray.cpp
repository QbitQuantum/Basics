/*************************************************************************
 * Shell_NotifyIcon             [SHELL32.296]
 * Shell_NotifyIconA            [SHELL32.297]
 */
BOOL WINAPI Shell_NotifyIconA(DWORD dwMessage, PNOTIFYICONDATAA pnid)
{
    NOTIFYICONDATAW nidW;
    DWORD cbSize, dwValidFlags;

    /* Initialize and capture the basic data fields */
    ZeroMemory(&nidW, sizeof(nidW));
    nidW.cbSize = sizeof(nidW); // Use a default size for the moment
    nidW.hWnd   = pnid->hWnd;
    nidW.uID    = pnid->uID;
    nidW.uFlags = pnid->uFlags;
    nidW.uCallbackMessage = pnid->uCallbackMessage;
    nidW.hIcon  = pnid->hIcon;

    /* Validate the structure size and the flags */
    cbSize = pnid->cbSize;
    dwValidFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    if (cbSize == sizeof(NOTIFYICONDATAA))
    {
        nidW.cbSize = sizeof(nidW);
        dwValidFlags |= NIF_STATE | NIF_INFO | NIF_GUID /* | NIF_REALTIME | NIF_SHOWTIP */;
    }
    else if (cbSize == NOTIFYICONDATAA_V3_SIZE)
    {
        nidW.cbSize = NOTIFYICONDATAW_V3_SIZE;
        dwValidFlags |= NIF_STATE | NIF_INFO | NIF_GUID;
    }
    else if (cbSize == NOTIFYICONDATAA_V2_SIZE)
    {
        nidW.cbSize = NOTIFYICONDATAW_V2_SIZE;
        dwValidFlags |= NIF_STATE | NIF_INFO;
    }
    else // if cbSize == NOTIFYICONDATAA_V1_SIZE or something else
    {
        if (cbSize != NOTIFYICONDATAA_V1_SIZE)
        {
            WARN("Invalid cbSize (%d) - using only Win95 fields (size=%d)\n",
                cbSize, NOTIFYICONDATAA_V1_SIZE);
            cbSize = NOTIFYICONDATAA_V1_SIZE;
        }
        nidW.cbSize = NOTIFYICONDATAW_V1_SIZE;
    }
    nidW.uFlags &= dwValidFlags;

    /* Capture the other data fields */

    if (nidW.uFlags & NIF_TIP)
    {
        /*
         * Depending on the size of the NOTIFYICONDATA structure
         * we should convert part of, or all the szTip string.
         */
        if (cbSize <= NOTIFYICONDATAA_V1_SIZE)
        {
#define NIDV1_TIP_SIZE_A  (NOTIFYICONDATAA_V1_SIZE - FIELD_OFFSET(NOTIFYICONDATAA, szTip))/sizeof(CHAR)
            MultiByteToWideChar(CP_ACP, 0, pnid->szTip, NIDV1_TIP_SIZE_A,
                                nidW.szTip, _countof(nidW.szTip));
            /* Truncate the string */
            nidW.szTip[NIDV1_TIP_SIZE_A - 1] = 0;
#undef NIDV1_TIP_SIZE_A
        }
        else
        {
            MultiByteToWideChar(CP_ACP, 0, pnid->szTip, -1,
                                nidW.szTip, _countof(nidW.szTip));
        }
    }

    if (cbSize >= NOTIFYICONDATAA_V2_SIZE)
    {
        nidW.dwState     = pnid->dwState;
        nidW.dwStateMask = pnid->dwStateMask;
        nidW.uTimeout    = pnid->uTimeout;
        nidW.dwInfoFlags = pnid->dwInfoFlags;

        if (nidW.uFlags & NIF_INFO)
        {
            MultiByteToWideChar(CP_ACP, 0, pnid->szInfo, -1,
                                nidW.szInfo, _countof(nidW.szInfo));
            MultiByteToWideChar(CP_ACP, 0, pnid->szInfoTitle, -1,
                                nidW.szInfoTitle, _countof(nidW.szInfoTitle));
        }
    }

    if ((cbSize >= NOTIFYICONDATAA_V3_SIZE) && (nidW.uFlags & NIF_GUID))
        nidW.guidItem = pnid->guidItem;

    if (cbSize >= sizeof(NOTIFYICONDATAA))
        nidW.hBalloonIcon = pnid->hBalloonIcon;

    /* Call the unicode function */
    return Shell_NotifyIconW(dwMessage, &nidW);
}