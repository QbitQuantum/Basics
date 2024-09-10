/*********************************************************************
 * display_cert_manager (internal)
 *
 * call cryptui to display a specific certificate manager dialog
 *
 */
static BOOL display_cert_manager(HWND parent, DWORD flags)
{
    CRYPTUI_CERT_MGR_STRUCT dlg;

    TRACE("(%p, 0x%x)\n", parent, flags);

    ZeroMemory(&dlg, sizeof(CRYPTUI_CERT_MGR_STRUCT));
    dlg.dwSize = sizeof(CRYPTUI_CERT_MGR_STRUCT);
    dlg.hwndParent = parent;
    dlg.dwFlags = flags;

    return CryptUIDlgCertMgr(&dlg);
}