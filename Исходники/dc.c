/*
 * @implemented
 */
HDC
WINAPI
CreateDCA (
    LPCSTR lpszDriver,
    LPCSTR lpszDevice,
    LPCSTR lpszOutput,
    CONST DEVMODEA * lpdvmInit)
{
    ANSI_STRING DriverA, DeviceA, OutputA;
    UNICODE_STRING DriverU, DeviceU, OutputU;
    LPDEVMODEW dvmInitW = NULL;
    HDC hdc;

    /*
     * If needed, convert to Unicode
     * any string parameter.
     */

    if (lpszDriver != NULL)
    {
        RtlInitAnsiString(&DriverA, (LPSTR)lpszDriver);
        RtlAnsiStringToUnicodeString(&DriverU, &DriverA, TRUE);
    }
    else
    {
        DriverU.Buffer = NULL;
    }

    if (lpszDevice != NULL)
    {
        RtlInitAnsiString(&DeviceA, (LPSTR)lpszDevice);
        RtlAnsiStringToUnicodeString(&DeviceU, &DeviceA, TRUE);
    }
    else
    {
        DeviceU.Buffer = NULL;
    }

    if (lpszOutput != NULL)
    {
        RtlInitAnsiString(&OutputA, (LPSTR)lpszOutput);
        RtlAnsiStringToUnicodeString(&OutputU, &OutputA, TRUE);
    }
    else
    {
        OutputU.Buffer = NULL;
    }

    if (lpdvmInit != NULL)
        dvmInitW = GdiConvertToDevmodeW((LPDEVMODEA)lpdvmInit);

    hdc = IntCreateDICW(DriverU.Buffer,
                        DeviceU.Buffer,
                        OutputU.Buffer,
                        lpdvmInit ? dvmInitW : NULL,
                        0);
    HEAP_free(dvmInitW);

    /* Free Unicode parameters. */
    RtlFreeUnicodeString(&DriverU);
    RtlFreeUnicodeString(&DeviceU);
    RtlFreeUnicodeString(&OutputU);

    /* Return the DC handle. */
    return hdc;
}