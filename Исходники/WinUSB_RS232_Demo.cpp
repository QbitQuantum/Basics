BOOL WriteToBulkEndpoint(WINUSB_INTERFACE_HANDLE hDeviceHandle, UCHAR* pID, ULONG* pcbWritten, UCHAR *szBuffer, ULONG cbSize)
{
    if (hDeviceHandle==INVALID_HANDLE_VALUE || !pID || !pcbWritten) {
        return FALSE;
    }

    BOOL bResult = TRUE;

//    UCHAR szBuffer[] = "Hello World";
//    ULONG cbSize = strlen((char*)szBuffer);
    ULONG cbSent = 0;

    bResult = WinUsb_WritePipe(hDeviceHandle, *pID, szBuffer, cbSize, &cbSent, 0);
    if(!bResult) {
        goto done;
    }

 //==   printf("Wrote to pipe %d: %s \nActual data transferred: %d.\n", *pID, szBuffer, cbSent);
    *pcbWritten = cbSent;


done:
    return bResult;

} // End of WriteToBulkEndpoint()