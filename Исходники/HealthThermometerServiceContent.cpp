HealthThermometerServiceContent::~HealthThermometerServiceContent()
{
    //
    // Remove the value change event
    //
    CComCritSecLock<CComAutoCriticalSection> Lock(m_ClientCS);
    if (NULL != m_ValueChangeEventReg)
    {
        BluetoothGATTUnregisterEvent(m_ValueChangeEventReg, BLUETOOTH_GATT_FLAG_NONE);
        m_ValueChangeEventReg = NULL;
    }
}