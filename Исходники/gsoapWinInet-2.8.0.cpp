static BOOL
wininet_resolve_send_error(
    HINTERNET   a_hHttpRequest,
    DWORD       a_dwErrorCode )
{
    DWORD dwResult = InternetErrorDlg(
        GetDesktopWindow(),
        a_hHttpRequest,
        a_dwErrorCode,
        FLAGS_ERROR_UI_FILTER_FOR_ERRORS |
        FLAGS_ERROR_UI_FLAGS_GENERATE_DATA |
        FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS,
        NULL );
    BOOL bRetVal = (a_dwErrorCode == ERROR_INTERNET_INCORRECT_PASSWORD) ?
        (dwResult == ERROR_INTERNET_FORCE_RETRY) :
        (dwResult == ERROR_SUCCESS);
    /* If appropriate for your application, it is possible to ignore
       errors in future once they have been handled or ignored once.
       For example, to ignore invalid SSL certificate dates on this
       connection once the client has indicated to ignore them this
       time, uncomment this code.
    */
    /*
    if (bRetVal)
    {
        switch (a_dwErrorCode)
        {
        case ERROR_INTERNET_SEC_CERT_CN_INVALID:
            wininet_flag_set_option(a_hHttpRequest,
                INTERNET_OPTION_SECURITY_FLAGS,
                SECURITY_FLAG_IGNORE_CERT_CN_INVALID );
            break;
        }
    }
    */
    return bRetVal;

}