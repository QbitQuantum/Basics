static HRESULT handle_http_error(HttpProtocol *This, DWORD error)
{
    IServiceProvider *serv_prov;
    IWindowForBindingUI *wfb_ui;
    IHttpSecurity *http_security;
    BOOL security_problem;
    DWORD dlg_flags;
    HWND hwnd;
    DWORD res;
    HRESULT hres;

    TRACE("(%p %u)\n", This, error);

    switch(error) {
    case ERROR_INTERNET_SEC_CERT_DATE_INVALID:
    case ERROR_INTERNET_SEC_CERT_CN_INVALID:
    case ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR:
    case ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR:
    case ERROR_INTERNET_INVALID_CA:
    case ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED:
    case ERROR_INTERNET_SEC_INVALID_CERT:
    case ERROR_INTERNET_SEC_CERT_ERRORS:
    case ERROR_INTERNET_SEC_CERT_REV_FAILED:
    case ERROR_INTERNET_SEC_CERT_NO_REV:
    case ERROR_INTERNET_SEC_CERT_REVOKED:
    case ERROR_HTTP_REDIRECT_NEEDS_CONFIRMATION:
        security_problem = TRUE;
        break;
    default:
        security_problem = FALSE;
    }

    hres = IInternetProtocolSink_QueryInterface(This->base.protocol_sink, &IID_IServiceProvider,
                                                (void**)&serv_prov);
    if(FAILED(hres)) {
        ERR("Failed to get IServiceProvider.\n");
        return E_ABORT;
    }

    if(security_problem) {
        hres = IServiceProvider_QueryService(serv_prov, &IID_IHttpSecurity, &IID_IHttpSecurity,
                                             (void**)&http_security);
        if(SUCCEEDED(hres)) {
            hres = IHttpSecurity_OnSecurityProblem(http_security, error);
            IHttpSecurity_Release(http_security);

            TRACE("OnSecurityProblem returned %08x\n", hres);

            if(hres != S_FALSE)
            {
                BOOL res = FALSE;

                IServiceProvider_Release(serv_prov);

                if(hres == S_OK) {
                    if(error == ERROR_INTERNET_SEC_CERT_DATE_INVALID)
                        res = set_security_flag(This, SECURITY_FLAG_IGNORE_CERT_DATE_INVALID);
                    else if(error == ERROR_INTERNET_SEC_CERT_CN_INVALID)
                        res = set_security_flag(This, SECURITY_FLAG_IGNORE_CERT_CN_INVALID);
                    else if(error == ERROR_INTERNET_INVALID_CA)
                        res = set_security_flag(This, SECURITY_FLAG_IGNORE_UNKNOWN_CA);

                    if(res)
                        return RPC_E_RETRY;

                    FIXME("Don't know how to ignore error %d\n", error);
                    return E_ABORT;
                }

                if(hres == E_ABORT)
                    return E_ABORT;
                if(hres == RPC_E_RETRY)
                    return RPC_E_RETRY;

                return internet_error_to_hres(error);
            }
        }
    }

    switch(error) {
    case ERROR_INTERNET_SEC_CERT_REV_FAILED:
        if(hres != S_FALSE) {
            /* Silently ignore the error. We will get more detailed error from wininet anyway. */
            set_security_flag(This, SECURITY_FLAG_IGNORE_REVOCATION);
            hres = RPC_E_RETRY;
            break;
        }
        /* fallthrough */
    default:
        hres = IServiceProvider_QueryService(serv_prov, &IID_IWindowForBindingUI, &IID_IWindowForBindingUI, (void**)&wfb_ui);
        if(SUCCEEDED(hres)) {
            const IID *iid_reason;

            if(security_problem)
                iid_reason = &IID_IHttpSecurity;
            else if(error == ERROR_INTERNET_INCORRECT_PASSWORD)
                iid_reason = &IID_IAuthenticate;
            else
                iid_reason = &IID_IWindowForBindingUI;

            hres = IWindowForBindingUI_GetWindow(wfb_ui, iid_reason, &hwnd);
            IWindowForBindingUI_Release(wfb_ui);
        }

        if(FAILED(hres)) hwnd = NULL;

        dlg_flags = FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS | FLAGS_ERROR_UI_FLAGS_GENERATE_DATA;
        if(This->base.bindf & BINDF_NO_UI)
            dlg_flags |= FLAGS_ERROR_UI_FLAGS_NO_UI;

        res = InternetErrorDlg(hwnd, This->base.request, error, dlg_flags, NULL);
        hres = res == ERROR_INTERNET_FORCE_RETRY || res == ERROR_SUCCESS ? RPC_E_RETRY : internet_error_to_hres(error);
    }

    IServiceProvider_Release(serv_prov);
    return hres;
}