inline s32 Factory::AddDevice(DeviceParam & pParam)
{
    s32 nId = GetDeviceID();
    FactoryDeviceChangeData change;
    Device *pDevice = NULL;
    DeviceParam pParam2;

    Lock();
    pParam.m_Conf.data.conf.nId = nId;
    if (pParam.m_Conf.data.conf.nType == VSC_DEVICE_CAM)
    {
        m_DeviceMap[nId] = new Device(*m_pVdb, *m_pVHdfsdb, pParam);
        pDevice = m_DeviceMap[nId];
    } else
    {
        m_DeviceMap[nId] = NULL;
        UnLock();
        return -1;
    }
    m_DeviceParamMap[nId] = pParam;
    m_DeviceOnlineMap[nId] = 0;
    m_Conf.AddDevice(pParam.m_Conf, nId);

    UnLock();
    change.id = nId;
    change.type = FACTORY_DEVICE_ADD;
    CallDeviceChange(change);
#if 0
    /* Try to online the device and lock */
    Lock();
    pDevice->GetDeviceParam(pParam2);
    UnLock();

    pParam2.m_wipOnline = pParam2.CheckOnline();
    if (pParam2.m_OnlineUrl == FALSE)
    {
        pParam2.m_wipOnlineUrl = pParam2.UpdateUrl();
    }

    /* Try to make the device online */
    Lock();
    DeviceStatus bCheck = pDevice->CheckDevice(pParam2.m_strUrl,
                          pParam2.m_strUrlSubStream, pParam2.m_bHasSubStream,
                          pParam2.m_wipOnline, pParam2.m_wipOnlineUrl);

    FactoryDeviceChangeData change2;
    change2.id = nId;

    if (bCheck == DEV_OFF2ON)
    {
        change.type = FACTORY_DEVICE_ONLINE;
        m_DeviceOnlineMap[nId] = 1;
        UnLock();
        CallDeviceChange(change);
        Lock();
    }
    UnLock();
#endif

    return nId;
}