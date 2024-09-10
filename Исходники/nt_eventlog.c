static DWORD WINAPI service_stderr_thread(LPVOID hPipe)
{
    HANDLE hPipeRead = (HANDLE) hPipe;
    HANDLE hEventSource;
    char errbuf[256];
    char *errmsg = errbuf;
    const char *errarg[9];
    DWORD errres;
    ap_regkey_t *regkey;
    apr_status_t rv;
    apr_pool_t *p;

    apr_pool_create_ex(&p, NULL, NULL, NULL);

    errarg[0] = "The Apache service named";
    errarg[1] = display_name;
    errarg[2] = "reported the following error:\r\n>>>";
    errarg[3] = errbuf;
    errarg[4] = NULL;
    errarg[5] = NULL;
    errarg[6] = NULL;
    errarg[7] = NULL;
    errarg[8] = NULL;

    /* What are we going to do in here, bail on the user?  not. */
    if ((rv = ap_regkey_open(&regkey, AP_REGKEY_LOCAL_MACHINE,
                             "SYSTEM\\CurrentControlSet\\Services\\"
                             "EventLog\\Application\\Apache Service",
                             APR_READ | APR_WRITE | APR_CREATE, p))
            == APR_SUCCESS)
    {
        DWORD dwData = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE |
                       EVENTLOG_INFORMATION_TYPE;

        /* The stock message file */
        ap_regkey_value_set(regkey, "EventMessageFile",
                            "%SystemRoot%\\System32\\netmsg.dll",
                            AP_REGKEY_EXPAND, p);

        ap_regkey_value_raw_set(regkey, "TypesSupported", &dwData,
                                sizeof(dwData), REG_DWORD, p);
        ap_regkey_close(regkey);
    }

    hEventSource = RegisterEventSourceW(NULL, L"Apache Service");

    SetEvent(stderr_ready);

    while (ReadFile(hPipeRead, errmsg, 1, &errres, NULL) && (errres == 1))
    {
        if ((errmsg > errbuf) || !apr_isspace(*errmsg))
        {
            ++errmsg;
            if ((*(errmsg - 1) == '\n')
                    || (errmsg >= errbuf + sizeof(errbuf) - 1))
            {
                while ((errmsg > errbuf) && apr_isspace(*(errmsg - 1))) {
                    --errmsg;
                }
                *errmsg = '\0';

                /* Generic message: '%1 %2 %3 %4 %5 %6 %7 %8 %9'
                 * The event code in netmsg.dll is 3299
                 */
                ReportEvent(hEventSource, EVENTLOG_ERROR_TYPE, 0,
                            3299, NULL, 9, 0, errarg, NULL);
                errmsg = errbuf;
            }
        }
    }

    if ((errres = GetLastError()) != ERROR_BROKEN_PIPE) {
        apr_snprintf(errbuf, sizeof(errbuf),
                     "Win32 error %lu reading stderr pipe stream\r\n",
                     GetLastError());

        ReportEvent(hEventSource, EVENTLOG_ERROR_TYPE, 0,
                    3299, NULL, 9, 0, errarg, NULL);
    }

    CloseHandle(hPipeRead);
    DeregisterEventSource(hEventSource);
    CloseHandle(stderr_thread);
    stderr_thread = NULL;
    apr_pool_destroy(p);
    return 0;
}