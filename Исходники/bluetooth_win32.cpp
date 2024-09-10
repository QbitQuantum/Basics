// Scan local network for visible remote devices
static VALUE bt_devices_scan(VALUE self)
{
    WORD wVersionRequested = 0x202;
    HANDLE hRadio;
    BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(btfrp) };

    HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio( &btfrp, &hRadio );

    VALUE devices_array = rb_ary_new();
    if ( NULL != hFind )
    {
        do
        {
            BLUETOOTH_DEVICE_INFO_STRUCT deviceInfo;

            deviceInfo.dwSize = sizeof(deviceInfo);

            BLUETOOTH_DEVICE_SEARCH_PARAMS deviceSearchParams;

            memset(&deviceSearchParams, 0, sizeof(deviceSearchParams));

            deviceSearchParams.dwSize = sizeof(deviceSearchParams);

            deviceSearchParams.fReturnAuthenticated = true;
            deviceSearchParams.fReturnRemembered = false;
            deviceSearchParams.fReturnUnknown = true;
            deviceSearchParams.fReturnConnected = true;
            deviceSearchParams.fIssueInquiry = true;
            deviceSearchParams.cTimeoutMultiplier = 1;

            deviceSearchParams.hRadio = hRadio;

            HANDLE hDeviceFind = BluetoothFindFirstDevice(&deviceSearchParams, &deviceInfo);

            if (NULL != hDeviceFind)
            {
                do
                {
                    BYTE *rgBytes = deviceInfo.Address.rgBytes;
                    //BluetoothDisplayDeviceProperties(0, &deviceInfo);
                    char addr[19] = { 0 };
                    char name[248] = { 0 };
                    wcstombs(name, deviceInfo.szName, sizeof(name));

                    snprintf(addr, sizeof(addr), "%02x:%02x:%02x:%02x:%02x:%02x",
                             rgBytes[5],
                             rgBytes[4],
                             rgBytes[3],
                             rgBytes[2],
                             rgBytes[1],
                             rgBytes[0]);

                    VALUE bt_dev = bt_device_new(bt_device_class,
                                                 rb_str_new2(name),
                                                 rb_str_new2(addr));
                    rb_ary_push(devices_array, bt_dev);
                }
                while(BluetoothFindNextDevice(hDeviceFind, &deviceInfo));

                BluetoothFindDeviceClose(hDeviceFind);
            }

            GUID guidServices[10];

            DWORD numServices = sizeof(guidServices);

            DWORD result = BluetoothEnumerateInstalledServices(hRadio, &deviceInfo, &numServices, guidServices);

            CloseHandle( hRadio );
        } while( BluetoothFindNextRadio( hFind, &hRadio ) );

        BluetoothFindRadioClose( hFind );
    }

    return devices_array;

}