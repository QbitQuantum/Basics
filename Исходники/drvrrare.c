HANDLE API DrvOpen(LPSTR szDriverName,
                   LPSTR szSectionName,
                   LONG lParam2)
{
    /*  The driver will receive the following message sequence:
     *
     *      if driver not loaded and can be found
     *          DRV_LOAD
     *          if DRV_LOAD returns non-zero
     *              DRV_ENABLE
     *      if driver loaded correctly
     *          DRV_OPEN
     */

    HANDLE hdrv;

    if (fUseWinAPI)
        hdrv = ((*lpOpenDriver)(szDriverName, szSectionName, lParam2));
    else
        hdrv = (HANDLE)InternalOpenDriver(szDriverName, szSectionName, lParam2, TRUE);

#ifdef DEBUG
    if (hdrv) {
        char ach[80];
        static SZCODE szFormat[] = "MMSYSTEM: Opened %ls (%ls)\r\n";

        GetModuleFileName(DrvGetModuleHandle(hdrv), ach, sizeof(ach));
        DPRINTF((szFormat, (LPSTR)szDriverName, (LPSTR)ach));
    }
#endif

    return hdrv;
}