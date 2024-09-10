//***************************************************************************
// DrvEnablePDEV
//***************************************************************************
DHPDEV DrvEnablePDEV(DEVMODEW *pdevmode,        // Driver data, Client FAXDEV
                     PWSTR     pwstrPrtName,    // Printer's name in CreateDC()
                     ULONG     cPatterns,       // Count of standard patterns
                     HSURF    *phsurfPatterns,  // Buffer for standard patterns
                     ULONG     cjGdiInfo,       // Size of buffer for GdiInfo
                     ULONG    *pulGdiInfo,      // Buffer for GDIINFO
                     ULONG     cjDevInfo,       // Number of bytes in devinfo
                     DEVINFO  *pdevinfo,        // Device info
                     HDEV      hdev,
                     PWSTR     pwstrDeviceName, // Device Name - "LaserJet II"
                     HANDLE    hDriver          // Printer handle for spooler access
)
{
    LPFAXDEV   lpCliFaxDev, lpSrvFaxDev = NULL;

    LOGDEBUG(("WOWFAX!DrvEnablePDEV, pdevmode: %X, pwstrPrtName: %S\n", pdevmode, pwstrPrtName));

    if (pdevmode) {
        // Point to the end of the DEVMODE where the FAXDEV is located.
        lpCliFaxDev = (LPFAXDEV) ((PBYTE)pdevmode + pdevmode->dmSize);

        // Allocate a server side FAXDEV to be passed back to GDI. Copy the
        // client side FAXDEV to the server side FAXDEV. Note all pointers in
        // the client FAXDEV reference client side memory and cannot be
        // dereferenced on the server side.
        lpSrvFaxDev = (LPFAXDEV)EngAllocMem(0, sizeof(FAXDEV), FAXDEV_ID);
        LOGDEBUG(("WOWFAX!DrvEnablePDEV, allocated lpSrvFaxDev: %X\n", lpSrvFaxDev));

        if (InitPDEV(lpCliFaxDev, lpSrvFaxDev,
                     cPatterns, phsurfPatterns,
                     cjGdiInfo, pulGdiInfo,
                     cjDevInfo, pdevinfo)) {

            lpSrvFaxDev->hDriver = hDriver;
            return (DHPDEV)lpSrvFaxDev;
        }
        else {
            LOGDEBUG(("WOWFAX!DrvEnablePDEV, failed\n"));
            if (lpSrvFaxDev) {
                EngFreeMem(lpSrvFaxDev);
                lpSrvFaxDev = NULL;
            }
        }
    }
    return (DHPDEV)lpSrvFaxDev;
}