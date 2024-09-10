/* 
    pContext [in]: Pointer to a string containing the registry path to the active key 
    for the stream interface driver

    lpvBusContext [in]: Potentially process-mapped pointer passed as the fourth parameter to ActivateDeviceEx. 
    If this driver was loaded through legacy mechanisms, then lpvBusContext is zero.    
*/
extern "C" DWORD BKL_Init(
  LPCTSTR pContext, 
  LPCVOID lpvBusContext
)
{   
    DWORD dwStatus, dwSize, dwType;
    HKEY hkDevice = NULL;
    BKL_MDD_INFO *pBKLinfo = NULL;

    UNREFERENCED_PARAMETER(lpvBusContext);
   
    if (IsDVIMode())
        return 0;
    
    DEBUGMSG(ZONE_BACKLIGHT, (TEXT("+BKL_Init() context %s.\r\n"), pContext));


    g_pBacklight = GetBacklightObject();
    if (g_pBacklight == NULL)
    {
        goto error;
    }

    // Allocate enough storage for this instance of our backlight
    pBKLinfo = (BKL_MDD_INFO *)LocalAlloc(LPTR, sizeof(BKL_MDD_INFO));
    if (pBKLinfo == NULL)
    {
        DEBUGMSG(ZONE_ERROR, (L"ERROR: BKL_Init: "
            L"Failed allocate BKL_MDD_INFO device structure\r\n" ));
        goto error;
    }

    // get device name from registry
    dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, pContext, 0, 0, &hkDevice);
    if(dwStatus != ERROR_SUCCESS) 
    {
        DEBUGMSG(ZONE_ERROR, (TEXT("BLK_Init: OpenDeviceKey failed with %u\r\n"), dwStatus));
        goto error;
    }
    dwSize = sizeof(pBKLinfo->szName);
    dwStatus = RegQueryValueEx(hkDevice, DEVLOAD_DEVNAME_VALNAME, NULL, &dwType, (LPBYTE)pBKLinfo->szName, &dwSize);
    if(dwStatus != ERROR_SUCCESS)
    {
        DEBUGMSG(ZONE_ERROR, (TEXT("BLK_Init: RegQueryValueEx failed with %u\r\n"), dwStatus));
        goto error;

    }
    RegCloseKey(hkDevice);
    hkDevice = NULL;

    // create exit event to be set by deinit:
    pBKLinfo->hExitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if(NULL == pBKLinfo->hExitEvent)
    {
        DEBUGMSG(ZONE_ERROR, (TEXT("BLK_Init: OpenDeviceKey failed with %u\r\n"), dwStatus));
        goto error;
    }

    pBKLinfo->hCoreDll = LoadLibrary(TEXT("coredll.dll"));
    if (NULL != pBKLinfo->hCoreDll) 
    {
        pBKLinfo->pfnGetSystemPowerStatusEx2 = (PFN_GetSystemPowerStatusEx2)
            GetProcAddress(pBKLinfo->hCoreDll, TEXT("GetSystemPowerStatusEx2"));
        if (!pBKLinfo->pfnGetSystemPowerStatusEx2) 
        {
            DEBUGMSG(ZONE_WARN,  (TEXT("GetProcAddress failed for GetSystemPowerStatusEx2. Assuming always on AC power.\r\n")));
        }
    }

//MYS     pBKLinfo->dwPddContext = BacklightInit(pContext, lpvBusContext, &(pBKLinfo->dwCurState));
    if (g_pBacklight->Initialize(pContext) == FALSE)
        {
        DEBUGMSG(ZONE_ERROR, (L"ERROR: BKL_Init: "
            L"Failed to initialize backlight object\r\n"
            ));
        goto error;
        }
    
    // if there are no user settings for this, we act as if they are selected:
    pBKLinfo->fBatteryTapOn = TRUE;
    pBKLinfo->fExternalTapOn = TRUE;

    // in case there is no setting for this:
    pBKLinfo->dwBattTimeout = 0;
    pBKLinfo->dwACTimeout = 0;

    pBKLinfo->dwCurState = D0;
    g_pBacklight->SetPowerState(pBKLinfo->dwCurState);
 
    //create thread to wait for reg / power source changes:
    pBKLinfo->hBklThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)fnBackLightThread, pBKLinfo, 0, NULL);
    if(NULL == pBKLinfo->hBklThread)
    {
        DEBUGMSG(ZONE_ERROR, (TEXT("BLK_Init: OpenDeviceKey failed with %u\r\n"), dwStatus));
        goto error;
    }

    DEBUGMSG(ZONE_BACKLIGHT, (TEXT("-BKL_Init().\r\n")));

    return (DWORD) pBKLinfo;

error:
    if(hkDevice)
    {
        RegCloseKey(hkDevice);
    }

    FreeContext(pBKLinfo);    

    return 0;

}