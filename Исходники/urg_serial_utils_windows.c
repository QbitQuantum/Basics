int urg_serial_find_port(void)
{
    // デバイスマネージャの一覧から COM デバイスを探す

    //4D36E978-E325-11CE-BFC1-08002BE10318
    GUID GUID_DEVINTERFACE_COM_DEVICE = {
        0x4D36E978L, 0xE325, 0x11CE,
        {0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18 }
    };

    HDEVINFO hdi;
    SP_DEVINFO_DATA sDevInfo;
    int i;

    found_ports_size = 0;
    hdi = SetupDiGetClassDevs(&GUID_DEVINTERFACE_COM_DEVICE, 0, 0,
                              DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
    if (hdi == INVALID_HANDLE_VALUE) {
        return 0;
    }

    sDevInfo.cbSize = sizeof(SP_DEVINFO_DATA);
    for (i = 0; SetupDiEnumDeviceInfo(hdi, i, &sDevInfo); ++i){

        enum {
            BufferSize = 256,
            ComNameLengthMax = 7,
        };
        char buffer[BufferSize + 1];
        DWORD dwRegType;
        DWORD dwSize;
        int is_urg_port;
        char *p;
        int n;
        int j;

        // フレンドリーネームを取得して COM 番号を取り出す
        SetupDiGetDeviceRegistryPropertyA(hdi, &sDevInfo, SPDRP_FRIENDLYNAME,
                                          &dwRegType, (BYTE*)buffer, BufferSize,
                                          &dwSize);
        n = (int)strlen(buffer);
        if (n < ComNameLengthMax) {
            // COM 名が短過ぎた場合、処理しない
            // 問題がある場合は、修正する
            continue;
        }

        // (COMx) の最後の括弧の位置に '\0' を代入する
        p = strrchr(buffer, ')');
        if (p) {
            *p = '\0';
        }

        // COM と番号までの文字列を抜き出す
        p = strstr(&buffer[n - ComNameLengthMax], "COM");
        if (! p) {
            continue;
        }

        snprintf(found_ports[found_ports_size], DEVICE_NAME_SIZE, "%s", p);

        // デバイス名を取得し、URG ポートかの判定に用いる
        SetupDiGetDeviceRegistryPropertyA(hdi, &sDevInfo, SPDRP_DEVICEDESC,
                                          &dwRegType, (BYTE*)buffer, BufferSize,
                                          &dwSize);
        is_urg_port = 0;
        n = sizeof(search_driver_names) / sizeof(search_driver_names[0]);
        for (j = 0; j < n; ++j) {
            if (! strcmp(search_driver_names[j], buffer)) {
                is_urg_port = 1;
                break;
            }
        }
        is_urg_ports[found_ports_size] = is_urg_port;
        ++found_ports_size;
    }
    SetupDiDestroyDeviceInfoList(hdi);

    // is_urg_port の要素が先頭に来るようにソートする
    sort_ports();

    return found_ports_size;
}