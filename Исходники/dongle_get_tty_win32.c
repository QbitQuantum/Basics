/* Find an attached dongle device and return the COM port name via the output
 * parameter tty. tty is a user-supplied buffer of size len. Return the COM
 * port number, if anyone cares. On error, return -1. */
int Mobot_dongleGetTTY (char *tty, size_t len) {
    /* Get all USB devices that provide a serial or parallel port interface. */
    HDEVINFO devices = SetupDiGetClassDevs(
            &GUID_DEVCLASS_PORTS,
            "USB",
            NULL,
            DIGCF_PRESENT);

    if (INVALID_HANDLE_VALUE == devices) {
        win32_error(_T("SetupDiGetClassDevs"), GetLastError());
        exit(1);
    }

    /* Now iterate over each device in the COM port interface class. */
    SP_DEVINFO_DATA dev;
    dev.cbSize = sizeof(SP_DEVINFO_DATA);
    DWORD i = 0;
    BOOL b = SetupDiEnumDeviceInfo(devices, i, &dev);
    int ret = -1;
    while (b) {
        if (isDongle(devices, &dev)) {
            ret = getCOMPort(devices, &dev, tty, len);
            if (-1 == ret) {
                fprintf(stderr, "Found dongle, but could not get COM port\n");
                exit(1);
            }
            /* Found the dongle. */
            break;
        }

        /* And get the next device. */
        dev.cbSize = sizeof(SP_DEVINFO_DATA);
        b = SetupDiEnumDeviceInfo(devices, ++i, &dev);
    }
    DWORD err = GetLastError();
    if (ERROR_SUCCESS != err && ERROR_NO_MORE_ITEMS != err) {
        win32_error(_T("SetupDiEnumDeviceInfo"), GetLastError());
        exit(1);
    }

    /* Done with our COM port devices. */
    if (!SetupDiDestroyDeviceInfoList(devices)) {
        win32_error(_T("SetupDiDestroyDeviceInfoList"), GetLastError());
        exit(1);
    }

    return ret;
}