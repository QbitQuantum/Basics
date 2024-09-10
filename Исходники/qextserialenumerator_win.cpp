void QextSerialEnumerator::enumerateDevicesWin(const GUID & guid, QList<QextPortInfo> *infoList)
{
    HDEVINFO devInfo;

    if ((devInfo = SetupDiGetClassDevs(&guid, NULL, NULL, DIGCF_PRESENT)) != INVALID_HANDLE_VALUE) {
        SP_DEVINFO_DATA devInfoData;
        devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        for (int i = 0; SetupDiEnumDeviceInfo(devInfo, i, &devInfoData); i++) {
            QextPortInfo info;
            info.productID = info.vendorID = 0;
            getDeviceDetailsWin(&info, devInfo, &devInfoData);
            infoList->append(info);
        }
        SetupDiDestroyDeviceInfoList(devInfo);
    }
}