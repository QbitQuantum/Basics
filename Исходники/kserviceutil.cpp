BOOL KCreateService(const wchar_t* pszServiceName,
                    const wchar_t* pszImagePath,
                    const wchar_t* pszSvcOrderGroup,
                    const wchar_t* pszDisplayName,
                    const wchar_t* pszDescription,
                    DWORD dwStartType,
                    DWORD* pdwError,
                    const wchar_t* pDepend,
                    DWORD nServicesType)
{
    if (NULL == pszServiceName)
        return FALSE;

    BOOL		bResult		= FALSE;
    BOOL		bRetCode	= FALSE;
    DWORD		dwErr		= 0;
    SC_HANDLE	hScm		= NULL;
    SC_HANDLE	hService	= NULL;
    SC_LOCK		sclLock		= NULL;
    int			nTimes		= 0;

    SERVICE_STATUS ssStatus = { 0 };

    hScm = ::OpenSCManagerW(NULL, NULL, SC_MANAGER_CONNECT | SC_MANAGER_LOCK | SC_MANAGER_CREATE_SERVICE);

    if (NULL == hScm)
    {
        dwErr = ::GetLastError();
        goto Exit0;
    }

    do
    {
        sclLock = LockServiceDatabase(hScm);
        if (sclLock)
            break;

        ++nTimes;
        Sleep(_SERVICE_GET_LOCK_SLEEP_TIME);

    } while(nTimes < _MAX_SERVICE_TRY_GET_LOCK_TIMES);

    hService = ::OpenServiceW(hScm, pszServiceName, SERVICE_CHANGE_CONFIG | SERVICE_STOP | SERVICE_USER_DEFINED_CONTROL);

    if (NULL == hService)
    {
        hService = ::CreateService(
                       hScm,					// SCManager database
                       pszServiceName,			// name of service
                       pszDisplayName,			// name to display
                       SERVICE_QUERY_STATUS | SERVICE_CHANGE_CONFIG,// desired access
                       nServicesType,// service type
                       SERVICE_AUTO_START,         // start type
                       SERVICE_ERROR_NORMAL,       // error control type
                       pszImagePath,				// service's binary
                       pszSvcOrderGroup,			// load ordering group
                       NULL,						// no tag identifier
                       pDepend,						// dependencies
                       NULL,                       // LocalSystem account
                       NULL);                      // no password

        if (hService)
            bResult = TRUE;
    }
    else
    {
        // 如果打开了, 则修改为我们想要的服务
        bResult = ChangeServiceConfig(
                      hService,                 // handle of service
                      SERVICE_WIN32_OWN_PROCESS, // change service type
                      dwStartType,         // change service start type
                      SERVICE_ERROR_NORMAL,//SERVICE_NO_CHANGE       // change error control
                      pszImagePath,				// change binary path
                      pszSvcOrderGroup,			// change load order group
                      NULL,                       // tag ID: no change
                      NULL,                       // dependencies: no change
                      NULL,                       // service start account: no change
                      NULL,                       // password: no change
                      pszDisplayName);			// change display name
    }

    if (pszDescription)
    {
        SERVICE_DESCRIPTION sd = {0};
        sd.lpDescription = (LPWSTR)pszDescription;
        ChangeServiceConfig2(
            hService,
            SERVICE_CONFIG_DESCRIPTION,
            &sd
        );
    }

    if (bResult)
        bRetCode = TRUE;
    else
        dwErr = ::GetLastError();

Exit0:
    if (pdwError)
        *pdwError = dwErr;

    if(sclLock)
        ::UnlockServiceDatabase(sclLock);


    if (hService)
        ::CloseServiceHandle(hService);

    if (hScm)
        ::CloseServiceHandle(hScm);

    return bRetCode;
}