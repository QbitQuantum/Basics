DirectShowAudioEndpointControl::DirectShowAudioEndpointControl(
        DirectShowPlayerService *service, QObject *parent)
    : QAudioOutputSelectorControl(parent)
    , m_service(service)
    , m_bindContext(0)
    , m_deviceEnumerator(0)
{
    if (CreateBindCtx(0, &m_bindContext) == S_OK) {
        m_deviceEnumerator = com_new<ICreateDevEnum>(CLSID_SystemDeviceEnum, IID_ICreateDevEnum);

        updateEndpoints();

        setActiveOutput(m_defaultEndpoint);
    }
}