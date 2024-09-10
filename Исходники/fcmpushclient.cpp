//----------------------------------------------------------------------------------------------------------------------
void FcmPushClient::setDeviceId(const String& deviceId)
{
    CMethodResult result;
    setProperty("deviceId", deviceId, result);

    LOG(TRACE) + "creating client register";
    rho::sync::RhoconnectClientManager::clientRegisterCreate(deviceId.c_str());

    getDeviceId(m_deviceIdResult);
    m_deviceIdResult = CMethodResult();

}