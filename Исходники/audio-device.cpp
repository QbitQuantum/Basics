// Private method
// dwKeyName means:
// 0 DeviceDesc (main name)
// 1 DeviceInterface_FriendlyName (interface name)
// 2 Device_FriendlyName (main name + interface name)
void _GetDeviceName(IMMDevice *pDevice, LPWSTR pszBuffer, int bufferLen, DWORD dwKeyName)
{
    static const WCHAR szDefault[] = L"<Device not available>";

    HRESULT hr = E_FAIL;
    IPropertyStore *pProps = NULL;
    PROPVARIANT varName;

    // Initialize container for property value.
    PropVariantInit(&varName);

    // assert(pszBuffer != NULL);
    // assert(bufferLen > 0);
	// assert(dwKeyName == 0 || dwKeyName == 1 || dwKeyName == 2);

    if (pDevice != NULL)
    {
        hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);
        if (hr == S_OK)
        {
			switch (dwKeyName) {
				case 0:
                    hr = pProps->GetValue(PKEY_Device_DeviceDesc, &varName);
					break;
				case 1:
                    hr = pProps->GetValue(PKEY_DeviceInterface_FriendlyName, &varName);
					break;
				case 2:
                    hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);
					break;
			}
        }
    }

    if (hr == S_OK)
    {
        // Found the device name.
        wcsncpy_s(pszBuffer, bufferLen, varName.pwszVal, _TRUNCATE);
    }
    else
    {
        // Failed to find the device name.
        wcsncpy_s(pszBuffer, bufferLen, szDefault, _TRUNCATE);
    }

    PropVariantClear(&varName);
    SAFE_RELEASE(pProps);

    return;
}