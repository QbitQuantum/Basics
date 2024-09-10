HRESULT AkVCam::PluginInterface::QueryInterface(REFIID uuid, LPVOID *interface)
{
    if (!interface)
        return E_POINTER;

    AkLoggerLog("AkVCam::PluginInterface::QueryInterface");

    if (uuidEqual(uuid, kCMIOHardwarePlugInInterfaceID)
        || uuidEqual(uuid, IUnknownUUID)) {
        AkLoggerLog("Found plugin interface.");
        this->d->AddRef(this->d);
        *interface = this->d;

        return S_OK;
    }

    return E_NOINTERFACE;
}