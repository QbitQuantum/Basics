//
//   FUNCTION: CDrmShlExt::GetCommandString(UINT, UINT, LPUINT, 
//             LPSTR, UINT)
//
//   PURPOSE: If a user highlights one of the items added by a context menu 
//            handler, the handler's IContextMenu::GetCommandString method is 
//            called to request a Help text string that will be displayed on 
//            the Windows Explorer status bar. This method can also be called 
//            to request the verb string that is assigned to a command. 
//            Either ANSI or Unicode verb strings can be requested.
//
IFACEMETHODIMP CDrmShlExt::GetCommandString(
    UINT_PTR idCommand, UINT uFlags, LPUINT lpReserved, LPSTR pszName, 
    UINT uMaxNameLen)
{
    HRESULT hr = E_INVALIDARG;

    // For the command "&Decrypt" (IDM_DECRYPT)
    if (idCommand == IDM_DECRYPT)
    {
        switch (uFlags)
        {
        case GCS_HELPTEXTA:
            hr = StringCchCopyNA(pszName, 
                lstrlenA(pszName) / sizeof(pszName[0]), 
                "Rights Network File Decrypter", 
                uMaxNameLen);
            break;

        case GCS_HELPTEXTW:
            hr = StringCchCopyNW((LPWSTR)pszName, 
                lstrlenW((LPWSTR)pszName) / sizeof(pszName[0]), 
                L"Rights Network File Decrypter", 
                uMaxNameLen);
            break;

        case GCS_VERBA:
            hr = StringCchCopyNA(pszName, 
                lstrlenA(pszName) / sizeof(pszName[0]), 
                VERB_DECRYPTA, uMaxNameLen);
            break;

        case GCS_VERBW:
            hr = StringCchCopyNW((LPWSTR)pszName, 
                lstrlenW((LPWSTR)pszName) / sizeof(pszName[0]), 
                VERB_DECRYPTW, uMaxNameLen);
            break;

        default:
            hr = S_OK;
        }
    }

    // If the command (idCommand) is not supported by this context menu 
    // extension handler, return E_INVALIDARG.

    return hr;
}