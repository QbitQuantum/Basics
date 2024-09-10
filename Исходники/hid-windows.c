/*
 * Use a series of API calls to find a HID with
 * a specified Vendor IF and Product ID.
 */
HID_API_EXPORT HID_API_CALL
hid_device *hid_open (
    unsigned short vendor_id,
    unsigned short product_id,
    const wchar_t *serial_number)
{
    GUID                        hidguid;
    HANDLE                      hidclass;
    SP_DEVICE_INTERFACE_DATA    iface;
    HANDLE                      dev;
    int                         i;

    HidD_GetHidGuid (&hidguid);

    hidclass = SetupDiGetClassDevs (&hidguid, NULL, NULL,
        DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

    iface.cbSize = sizeof(iface);

    i = 0;
    dev = NULL;
    while (SetupDiEnumDeviceInterfaces (hidclass, 0, &hidguid,
                                        i, &iface))
    {
        ULONG unused, nbytes = 0;
        PSP_DEVICE_INTERFACE_DETAIL_DATA detail;
        HIDD_ATTRIBUTES devinfo;

        SetupDiGetDeviceInterfaceDetail (hidclass, &iface,
            NULL, 0, &nbytes, NULL);

        detail = (PSP_DEVICE_INTERFACE_DETAIL_DATA) malloc (nbytes);
        detail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        SetupDiGetDeviceInterfaceDetail (hidclass, &iface,
            detail, nbytes, &unused, NULL);

        dev = CreateFile (detail->DevicePath,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            (LPSECURITY_ATTRIBUTES) NULL,
            OPEN_EXISTING, 0, NULL);
        free (detail);

        devinfo.Size = sizeof(devinfo);
        HidD_GetAttributes (dev, &devinfo);

        if (devinfo.VendorID == vendor_id && devinfo.ProductID == product_id)
        {
            // Both the Vendor ID and Product ID match.
            break;
        }

        // The Vendor ID doesn't match.
        // Free the memory used by the detailData structure (no longer needed).
        CloseHandle (dev);
        dev = NULL;

        // If we haven't found the device yet, and haven't tried every
        // available device, try the next one.
        i++;
    }

    // Free the memory reserved for hidclass by SetupDiClassDevs.
    SetupDiDestroyDeviceInfoList (hidclass);
    return (hid_device*) dev;
}