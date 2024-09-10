STDMETHODIMP CBmpCtxMenuExt::GetCommandString (
                               UINT uCmd, UINT uFlags, UINT* puReserved,
                               LPSTR pszName, UINT cchMax )
{
static LPCTSTR szHelpString = _T("Click the thumbnail to view the entire picture.");

    USES_CONVERSION;

    // Check idCmd, it must be 0 since we have only one menu item.
    if ( 0 != uCmd )
        return E_INVALIDARG;

    // If Explorer is asking for a help string, copy our string into the
    // supplied buffer.
    if ( uFlags & GCS_HELPTEXT )
        {
        if ( uFlags & GCS_UNICODE )
            {
            // We need to cast pszName to a Unicode string, and then use the
            // Unicode string copy API.
            lstrcpynW ( (LPWSTR) pszName, T2CW(szHelpString), cchMax );
            }
        else
            {
            // Use the ANSI string copy API to return the help string.
            lstrcpynA ( pszName, T2CA(szHelpString), cchMax );
            }
        }

    return S_OK;
}