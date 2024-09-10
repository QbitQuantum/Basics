bool emuShutdown(const CComBSTR& deviceIdentifier)
{
    CComPtr<IDeviceEmulatorManagerVMID> pDevice = NULL;

    BOOL bFound = FindDevice(deviceIdentifier, &pDevice);
    if (bFound && pDevice){
        HRESULT hr = pDevice->Shutdown(FALSE);
        if (!SUCCEEDED(hr)) {
            wprintf(L"Error: Operation Shutdown failed. Hr=0x%x\n", hr);
            return false;
        }
        return true;
    }
    return false;
}