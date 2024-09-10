QList<SerialPortId> enumerateSerialPorts(int)
{
    DWORD index=0;
    SP_DEVINFO_DATA info;
    GUID guid = GUID_DEVCLASS_PORTS;
    HDEVINFO infoset = SetupDiGetClassDevs(&guid, 0, 0, DIGCF_PRESENT);
    QString valueName(16384, 0);
    QList<SerialPortId> list;

    for (index=0;;index++) {
        ZeroMemory(&info, sizeof(SP_DEVINFO_DATA));
        info.cbSize = sizeof(SP_DEVINFO_DATA);
        if (!SetupDiEnumDeviceInfo(infoset, index, &info))
            break;
        QString friendlyName;
        QString portName;
        DWORD size=0;
        SetupDiGetDeviceRegistryProperty(infoset, &info, SPDRP_FRIENDLYNAME, 0, 0, 0, &size);
        QByteArray ba(size, 0);
        if(SetupDiGetDeviceRegistryProperty(infoset, &info, SPDRP_FRIENDLYNAME, 0, (BYTE*)(ba.data()), size, 0)) {
            friendlyName = QString((const QChar*)(ba.constData()), ba.size() / 2 - 1);
        }
        HKEY key = SetupDiOpenDevRegKey(infoset, &info, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
        if(key != INVALID_HANDLE_VALUE) {
            //RegGetValue not supported on XP, SHRegGetValue not supported by mingw, so use the old method of enumerating all the values
            for (DWORD dwi=0;;dwi++) {
                DWORD vsize = valueName.size();
                if (ERROR_SUCCESS == RegEnumValue(key, dwi, (WCHAR*)(valueName.data()), &vsize, 0, 0, 0, &size)) {
                    if (valueName.startsWith("PortName")) {
                       QByteArray ba(size, 0);
                       vsize = valueName.size();
                       if(ERROR_SUCCESS == RegEnumValue(key, dwi, (WCHAR*)(valueName.data()), &vsize, 0, 0, (BYTE*)(ba.data()), &size)) {
                           portName = QString((const QChar*)(ba.constData()), ba.size() / 2 - 1);
                       }
                   }
                } else {
                    break;
                }
            }
            RegCloseKey(key);
        }
        SerialPortId id;
        id.portName = portName;
        id.friendlyName = friendlyName;
        list.append(id);
    }
    SetupDiDestroyDeviceInfoList(infoset);
    return list;
}