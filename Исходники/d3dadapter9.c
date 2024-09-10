static HRESULT WINAPI
d3dadapter9_GetAdapterIdentifier( struct d3dadapter9 *This,
                                  UINT Adapter,
                                  DWORD Flags,
                                  D3DADAPTER_IDENTIFIER9 *pIdentifier )
{
    HRESULT hr;
    HKEY regkey;

    if (Adapter >= d3dadapter9_GetAdapterCount(This)) { return D3DERR_INVALIDCALL; }

    hr = ADAPTER_PROC(GetAdapterIdentifier, Flags, pIdentifier);
    if (SUCCEEDED(hr)) {
        /* Override the driver provided DeviceName with what Wine provided */
        ZeroMemory(pIdentifier->DeviceName, sizeof(pIdentifier->DeviceName));
        if (!WideCharToMultiByte(CP_ACP, 0, ADAPTER_GROUP.devname, -1,
                                 pIdentifier->DeviceName,
                                 sizeof(pIdentifier->DeviceName),
                                 NULL, NULL)) {
            /* Wine does it */
            return D3DERR_INVALIDCALL;
        }
        TRACE("DeviceName overriden: %s\n", pIdentifier->DeviceName);

        /* Override PCI IDs when wined3d registry keys are set */
        if (!RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Wine\\Direct3D", &regkey)) {
            DWORD type, data;
            DWORD size = sizeof(DWORD);

            if (!RegQueryValueExA(regkey, "VideoPciDeviceID", 0, &type, (BYTE *)&data, &size) && (type == REG_DWORD) && (size == sizeof(DWORD)))
                pIdentifier->DeviceId = data;
            if(size != sizeof(DWORD)) {
                ERR("VideoPciDeviceID is not a DWORD\n");
                size = sizeof(DWORD);
            }
            if (!RegQueryValueExA(regkey, "VideoPciVendorID", 0, &type, (BYTE *)&data, &size) && (type == REG_DWORD) && (size == sizeof(DWORD)))
                pIdentifier->VendorId = data;
            if(size != sizeof(DWORD))
                ERR("VideoPciVendorID is not a DWORD\n");
            RegCloseKey(regkey);

            TRACE("DeviceId:VendorId overridden: %04X:%04X\n", pIdentifier->DeviceId, pIdentifier->VendorId);
        }
    }
    return hr;
}