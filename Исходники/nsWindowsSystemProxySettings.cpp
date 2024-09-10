static nsresult ReadInternetOption(uint32_t aOption, uint32_t& aFlags,
                                   nsAString& aValue)
{
    DWORD connFlags = 0;
    WCHAR connName[RAS_MaxEntryName + 1];
    MOZ_SEH_TRY {
        InternetGetConnectedStateExW(&connFlags, connName,
                                     mozilla::ArrayLength(connName), 0);
    } MOZ_SEH_EXCEPT(EXCEPTION_EXECUTE_HANDLER) {
        return NS_ERROR_FAILURE;
    }

    INTERNET_PER_CONN_OPTIONW options[2];
    options[0].dwOption = INTERNET_PER_CONN_FLAGS_UI;
    options[1].dwOption = aOption;

    INTERNET_PER_CONN_OPTION_LISTW list;
    list.dwSize = sizeof(INTERNET_PER_CONN_OPTION_LISTW);
    list.pszConnection = connFlags & INTERNET_CONNECTION_MODEM ?
                         connName : NULL;
    list.dwOptionCount = mozilla::ArrayLength(options);
    list.dwOptionError = 0;
    list.pOptions = options;

    unsigned long size = sizeof(INTERNET_PER_CONN_OPTION_LISTW);
    if (!InternetQueryOptionW(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION,
                              &list, &size)) {
        if (GetLastError() != ERROR_INVALID_PARAMETER) {
            return NS_ERROR_FAILURE;
        }
        options[0].dwOption = INTERNET_PER_CONN_FLAGS;
        size = sizeof(INTERNET_PER_CONN_OPTION_LISTW);
        MOZ_SEH_TRY {
            if (!InternetQueryOptionW(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION,
                                      &list, &size)) {
                return NS_ERROR_FAILURE;
            }
        } MOZ_SEH_EXCEPT(EXCEPTION_EXECUTE_HANDLER) {
            return NS_ERROR_FAILURE;
        }
    }

    aFlags = options[0].Value.dwValue;
    aValue.Assign(options[1].Value.pszValue);
    GlobalFree(options[1].Value.pszValue);

    return NS_OK;
}