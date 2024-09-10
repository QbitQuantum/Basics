int _tmain(int argc, _TCHAR* argv[])
{
    while(true) {
        m_bt = BluetoothFindFirstRadio(&m_bt_find_radio, &m_radio);

        int m_radio_id = 0;
        do {
            m_radio_id++;

            BluetoothGetRadioInfo(m_radio, &m_bt_info);

            wprintf(L"Radio %d:\r\n", m_radio_id);
            wprintf(L"\tName: %s\r\n", m_bt_info.szName);
            wprintf(L"\tAddress: %02x:%02x:%02x:%02x:%02x:%02x\r\n", m_bt_info.address.rgBytes[1], m_bt_info.address.rgBytes[0], m_bt_info.address.rgBytes[2], m_bt_info.address.rgBytes[3], m_bt_info.address.rgBytes[4], m_bt_info.address.rgBytes[5]);
            wprintf(L"\tClass: 0x%08x\r\n", m_bt_info.ulClassofDevice);
            wprintf(L"\tManufacturer: 0x%04x\r\n", m_bt_info.manufacturer);

            m_search_params.hRadio = m_radio;

            ::ZeroMemory(&m_device_info, sizeof(BLUETOOTH_DEVICE_INFO));
            m_device_info.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

            m_bt_dev = BluetoothFindFirstDevice(&m_search_params, &m_device_info);

            int m_device_id = 0;
            do {
                m_device_id++;

                wprintf(L"\tDevice %d:\r\n", m_device_id);
                wprintf(L"\t\tName: %s\r\n", m_device_info.szName);
                wprintf(L"\t\tAddress: %02x:%02x:%02x:%02x:%02x:%02x\r\n", m_device_info.Address.rgBytes[1], m_device_info.Address.rgBytes[0], m_device_info.Address.rgBytes[2], m_device_info.Address.rgBytes[3], m_device_info.Address.rgBytes[4], m_device_info.Address.rgBytes[5]);
                wprintf(L"\t\tClass: 0x%08x\r\n", m_device_info.ulClassofDevice);
                wprintf(L"\t\tConnected: %s\r\n", m_device_info.fConnected ? L"true" : L"false");
                wprintf(L"\t\tAuthenticated: %s\r\n", m_device_info.fAuthenticated ? L"true" : L"false");
                wprintf(L"\t\tRemembered: %s\r\n", m_device_info.fRemembered ? L"true" : L"false");

            } while(BluetoothFindNextDevice(m_bt_dev, &m_device_info));

            BluetoothFindDeviceClose(m_bt_dev);

        } while(BluetoothFindNextRadio(&m_bt_find_radio, &m_radio));

        BluetoothFindRadioClose(m_bt);

        Sleep(10000);
    }

    return 0;
}