bool BtPCModul ::InstalDriver(NXTclass * nxtclass)
{
    BLUETOOTH_DEVICE_INFO m_device_info = {sizeof(BLUETOOTH_DEVICE_INFO),str2ba(nxtclass->BTaddr),};
    int iguid[4]=NXT_GUID;
    GUID * guid=new GUID;
    memcpy(&(guid->Data1),(int*)iguid,16);
    HRESULT re=BluetoothSetServiceState (0,&m_device_info,guid,BLUETOOTH_SERVICE_ENABLE);
    if (re==E_INVALIDARG)
    {
        printf("Driver already installed\n");
        return (nxtclass->portIsReady());
    }
    if (re==ERROR_SUCCESS)
    {
        printf("Driver successfully installed\n");
        return true;
    }
    printf("Driver instal failed\n");
    return false;
}