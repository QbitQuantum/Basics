/* Based on SDL2's implementation. */
static bool guid_is_xinput_device(const GUID* product_guid)
{
    unsigned i, num_raw_devs = 0;
    PRAWINPUTDEVICELIST raw_devs = NULL;

    /* Check for well known XInput device GUIDs,
     * thereby removing the need for the IG_ check.
     * This lets us skip RAWINPUT for popular devices.
     *
     * Also, we need to do this for the Valve Streaming Gamepad
     * because it's virtualized and doesn't show up in the device list.  */

    for (i = 0; i < ARRAY_SIZE(common_xinput_guids); ++i)
    {
        if (memcmp(product_guid, &common_xinput_guids[i], sizeof(GUID)) == 0)
            return true;
    }

    /* Go through RAWINPUT (WinXP and later) to find HID devices. */
    if (!raw_devs)
    {
        if ((GetRawInputDeviceList(NULL, &num_raw_devs,
                                   sizeof(RAWINPUTDEVICELIST)) == (UINT)-1) || (!num_raw_devs))
            return false;

        raw_devs = (PRAWINPUTDEVICELIST)
                   malloc(sizeof(RAWINPUTDEVICELIST) * num_raw_devs);
        if (!raw_devs)
            return false;

        if (GetRawInputDeviceList(raw_devs, &num_raw_devs,
                                  sizeof(RAWINPUTDEVICELIST)) == (UINT)-1)
        {
            free(raw_devs);
            raw_devs = NULL;
            return false;
        }
    }

    for (i = 0; i < num_raw_devs; i++)
    {
        RID_DEVICE_INFO rdi;
        char devName[128]   = {0};
        UINT rdiSize        = sizeof(rdi);
        UINT nameSize       = sizeof(devName);

        rdi.cbSize = sizeof (rdi);

        if ((raw_devs[i].dwType == RIM_TYPEHID) &&
                (GetRawInputDeviceInfoA(raw_devs[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdiSize) != ((UINT)-1)) &&
                (MAKELONG(rdi.hid.dwVendorId, rdi.hid.dwProductId) == ((LONG)product_guid->Data1)) &&
                (GetRawInputDeviceInfoA(raw_devs[i].hDevice, RIDI_DEVICENAME, devName, &nameSize) != ((UINT)-1)) &&
                (strstr(devName, "IG_") != NULL) )
        {
            free(raw_devs);
            raw_devs = NULL;
            return true;
        }
    }

    free(raw_devs);
    raw_devs = NULL;
    return false;
}