/***********************************************************************
 *		OpenPersonalTrustDBDialog (WINTRUST.@)
 *
 * Opens the certificate manager dialog, showing only the stores that
 * contain trusted software publishers.
 *
 * PARAMS
 *  hwnd [I] handle of parent window
 *
 * RETURNS
 *  TRUE if the dialog could be opened, FALSE if not.
 */
BOOL WINAPI OpenPersonalTrustDBDialog(HWND hwnd)
{
    CRYPTUI_CERT_MGR_STRUCT uiCertMgr;

    uiCertMgr.dwSize = sizeof(uiCertMgr);
    uiCertMgr.hwndParent = hwnd;
    uiCertMgr.dwFlags = CRYPTUI_CERT_MGR_PUBLISHER_TAB;
    uiCertMgr.pwszTitle = NULL;
    uiCertMgr.pszInitUsageOID = NULL;
    return CryptUIDlgCertMgr(&uiCertMgr);
}