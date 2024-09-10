	//static
	void QextSerialEnumerator::setupAPIScan(QList<QextPortInfo> & infoList)
	{
		HDEVINFO devInfo = INVALID_HANDLE_VALUE;

        DWORD dwGuids = 0;
        SetupDiClassGuidsFromName(TEXT("Ports"), NULL, 0, &dwGuids);
        if (dwGuids == 0)
        {
            qCritical("SetupDiClassGuidsFromName failed. Error code: %ld", GetLastError());
            return;
        }
        GUID *pGuids = new GUID[dwGuids];
        if (!SetupDiClassGuidsFromName(TEXT("Ports"), pGuids, dwGuids, &dwGuids))
        {
            qCritical("SetupDiClassGuidsFromName second call failed. Error code: %ld", GetLastError());
            return;
        }

        devInfo = SetupDiGetClassDevs(pGuids, NULL, NULL, DIGCF_PRESENT);
        if(devInfo == INVALID_HANDLE_VALUE)
        {
            qCritical("SetupDiGetClassDevs failed. Error code: %ld", GetLastError());
            return;
		}

		//enumerate the devices
		bool ok = true;
		SP_DEVICE_INTERFACE_DATA ifcData;
		ifcData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		SP_DEVICE_INTERFACE_DETAIL_DATA * detData = NULL;
        SP_DEVINFO_DATA devData = {sizeof(SP_DEVINFO_DATA)};

        for (DWORD i = 0; ok; i++)
        {
            ok = SetupDiEnumDeviceInfo(devInfo, i, &devData);
            if (ok)
            {
                // Got a device. Get the details.
                QextPortInfo info;
                info.friendName = getDeviceProperty(devInfo, & devData, SPDRP_FRIENDLYNAME);
                info.physName = getDeviceProperty(devInfo, & devData, SPDRP_PHYSICAL_DEVICE_OBJECT_NAME);
                info.enumName = getDeviceProperty(devInfo, & devData, SPDRP_ENUMERATOR_NAME);
                //anyway, to get the port name we must still open registry directly :( ???
                //Eh...
                HKEY devKey = SetupDiOpenDevRegKey(devInfo, & devData, DICS_FLAG_GLOBAL, 0,
                                                                                        DIREG_DEV, KEY_READ);
                info.portName = getRegKeyValue(devKey, TEXT("PortName"));
                RegCloseKey(devKey);
                if(info.portName.startsWith("COM"))
                {
                    infoList.append(info);
                }
            }
            else
            {
                if (GetLastError() != ERROR_NO_MORE_ITEMS)
                {
                    delete [] detData;
                    qCritical("SetupDiEnumDeviceInfo failed. Error code: %ld", GetLastError());
                    return;
                }
            }
        }
        delete [] detData;
        delete[] pGuids;
    }