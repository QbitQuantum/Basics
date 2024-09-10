BOOL CALLBACK FindDeviceCallbackEx(__in_opt GUID* lpGUID, __in LPSTR szName, __in LPSTR szDevice, __in LPVOID lParam, HMONITOR hMonitor)
{
    FindDeviceData *p = (FindDeviceData*)lParam;

    if(lstrcmpiA(p->szDevice, szDevice) == 0)
    {
        if(lpGUID)
        {
            p->GUID = *lpGUID;
            p->lpGUID = &p->GUID;
        }
        else
        {
            p->lpGUID = NULL;
        }
        p->fFound = TRUE;
        return FALSE;
    }
    return TRUE;
}