HRESULT CWIACapabilityManager::AddCapability(const GUID    guidCapability,
                                             UINT          uiNameResourceID,
                                             UINT          uiDescriptionResourceID,
                                             ULONG         ulFlags,
                                             _In_ LPWSTR   wszIcon)
{
    HRESULT hr = S_OK;

    WIA_DEV_CAP_DRV *pWIADeviceCapability = NULL;
    hr = AllocateCapability(&pWIADeviceCapability);
    if((SUCCEEDED(hr)&& (pWIADeviceCapability)))
    {
        pWIADeviceCapability->ulFlags = ulFlags;
        *pWIADeviceCapability->guid   = guidCapability;

        CBasicStringWide cswCapabilityString;

        //
        // Load capability name from resource
        //

        if(cswCapabilityString.LoadString(uiNameResourceID,m_hInstance))
        {
            hr = StringCbCopyW(pWIADeviceCapability->wszName,
                               MAX_CAPABILITY_STRING_SIZE_BYTES,
                               cswCapabilityString.String());
            if(FAILED(hr))
            {
                WIAS_ERROR((g_hInst, "Failed to copy source string (%ws) to destination string, hr = 0x%lx",cswCapabilityString.String(),hr));
            }
        }
        else
        {
            hr = E_FAIL;
            WIAS_ERROR((g_hInst, "Failed to load the device capability name string from DLL resource, hr = 0x%lx",hr));
        }

        //
        // Load capability description from resource
        //

        if(cswCapabilityString.LoadString(uiDescriptionResourceID,m_hInstance))
        {
            hr = StringCbCopyW(pWIADeviceCapability->wszDescription,
                               MAX_CAPABILITY_STRING_SIZE_BYTES,
                               cswCapabilityString.String());
            if(FAILED(hr))
            {
                WIAS_ERROR((g_hInst, "Failed to copy source string (%ws) to destination string, hr = 0x%lx",cswCapabilityString.String(),hr));
            }
        }
        else
        {
            hr = E_FAIL;
            WIAS_ERROR((g_hInst, "Failed to load the device capability description string from DLL resource, hr = 0x%lx",hr));
        }

        //
        // Copy icon location string
        //

        cswCapabilityString = wszIcon;

        if(cswCapabilityString.Length())
        {
            hr = StringCbCopyW(pWIADeviceCapability->wszIcon,
                               MAX_CAPABILITY_STRING_SIZE_BYTES,
                               cswCapabilityString.String());
            if(FAILED(hr))
            {
                WIAS_ERROR((g_hInst, "Failed to copy source string (%ws) to destination string, hr = 0x%lx",cswCapabilityString.String(),hr));
            }
        }
        else
        {
            hr = E_FAIL;
            WIAS_ERROR((g_hInst, "Failed to load the device capability icon location string from DLL resource, hr = 0x%lx",hr));
        }

        if(SUCCEEDED(hr))
        {
            if((pWIADeviceCapability->ulFlags == WIA_NOTIFICATION_EVENT) ||
               (pWIADeviceCapability->ulFlags == WIA_ACTION_EVENT))
            {
                //
                // The capability being added is an event, so always add it to the beginning of the array
                //

                m_CapabilityArray.Insert(*pWIADeviceCapability,0);
            }
            else
            {
                //
                // The capability being added is a command, so always add it to the end of the array
                //

                m_CapabilityArray.Append(*pWIADeviceCapability);
            }
        }

        if(pWIADeviceCapability)
        {
            CoTaskMemFree(pWIADeviceCapability);
            pWIADeviceCapability = NULL;
        }
    }
    return hr;
}