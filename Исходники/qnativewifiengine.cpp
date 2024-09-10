void QNativeWifiEngine::connectToId(const QString &id)
{
    QMutexLocker locker(&mutex);

    if (!available()) {
        locker.unlock();
        emit connectionError(id, InterfaceLookupError);
        return;
    }

    WLAN_INTERFACE_INFO_LIST *interfaceList;
    DWORD result = local_WlanEnumInterfaces(handle, 0, &interfaceList);
    if (result != ERROR_SUCCESS) {
#ifdef BEARER_MANAGEMENT_DEBUG
        qDebug("%s: WlanEnumInterfaces failed with error %ld\n", __FUNCTION__, result);
#endif
        locker.unlock();
        emit connectionError(id, InterfaceLookupError);
        return;
    }

    QString profile;

    for (unsigned int i = 0; i < interfaceList->dwNumberOfItems; ++i) {
        const WLAN_INTERFACE_INFO &interface = interfaceList->InterfaceInfo[i];

        WLAN_AVAILABLE_NETWORK_LIST *networkList;
        result = local_WlanGetAvailableNetworkList(handle, &interface.InterfaceGuid,
                                                   3, 0, &networkList);
        if (result != ERROR_SUCCESS) {
#ifdef BEARER_MANAGEMENT_DEBUG
            qDebug("%s: WlanGetAvailableNetworkList failed with error %ld\n",
                   __FUNCTION__, result);
#endif
            continue;
        }

        for (unsigned int j = 0; j < networkList->dwNumberOfItems; ++j) {
            WLAN_AVAILABLE_NETWORK &network = networkList->Network[j];

            profile = QString::fromWCharArray(network.strProfileName);

            if (qHash(QLatin1String("WLAN:") + profile) == id.toUInt())
                break;
            else
                profile.clear();
        }

        local_WlanFreeMemory(networkList);

        if (!profile.isEmpty()) {
            WLAN_CONNECTION_PARAMETERS parameters;
            parameters.wlanConnectionMode = wlan_connection_mode_profile;
            parameters.strProfile = reinterpret_cast<LPCWSTR>(profile.utf16());
            parameters.pDot11Ssid = 0;
            parameters.pDesiredBssidList = 0;
            parameters.dot11BssType = dot11_BSS_type_any;
            parameters.dwFlags = 0;

            DWORD result = local_WlanConnect(handle, &interface.InterfaceGuid, &parameters, 0);
            if (result != ERROR_SUCCESS) {
#ifdef BEARER_MANAGEMENT_DEBUG
                qDebug("%s: WlanConnect failed with error %ld\n", __FUNCTION__, result);
#endif
                locker.unlock();
                emit connectionError(id, ConnectError);
                locker.relock();
                break;
            }

            break;
        }
    }

    local_WlanFreeMemory(interfaceList);

    if (profile.isEmpty()) {
        locker.unlock();
        emit connectionError(id, InterfaceLookupError);
    }
}