static HRESULT register_service(BOOL do_register)
{
    static const WCHAR name[] = { 'B','I','T','S', 0 };
    static const WCHAR path[] = { 's','v','c','h','o','s','t','.','e','x','e',
                                  ' ','-','k',' ','n','e','t','s','v','c','s', 0 };
    SC_HANDLE scm, service;

    scm = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (!scm)
        return SELFREG_E_CLASS;

    if (do_register)
        service = CreateServiceW(scm, name, name, SERVICE_ALL_ACCESS,
                                 SERVICE_WIN32_OWN_PROCESS,
                                 SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
                                 path, NULL, NULL, NULL, NULL, NULL);
    else
        service = OpenServiceW(scm, name, DELETE);


    CloseServiceHandle(scm);
    if (service)
    {
        if (!do_register) DeleteService(service);
        CloseServiceHandle(service);
    }
    return S_OK;
}