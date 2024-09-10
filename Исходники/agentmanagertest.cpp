void TestAgent::requestPinCode(DevicePtr device, const BluezQt::Request<QString> &request)
{
    m_device = device;
    m_pinRequested = true;

    request.accept(QString());

}