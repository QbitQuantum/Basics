// Calls EnumerateDevices() function to display devices on the system
// and to obtain the total number of devices found.  If 1 or more devices
// are found, this function prompts the user to choose a device using
// a zero-based index.
void ChooseDevice(
    IPortableDevice** ppDevice)
{
    HRESULT                         hr              = S_OK;
    UINT                            uiCurrentDevice = 0;
    CHAR                            szSelection[81] = {0};
    DWORD                           cPnPDeviceIDs   = 0;
    PWSTR*                          pPnpDeviceIDs   = NULL;

    CComPtr<IPortableDeviceManager> pPortableDeviceManager;
    CComPtr<IPortableDeviceValues>  pClientInformation;

    if (ppDevice == NULL)
    {
        printf("! A NULL IPortableDevice interface pointer was received\n");
        return;
    }

    if (*ppDevice != NULL)
    {
        // To avoid operating on potiential bad pointers, reject any non-null
        // IPortableDevice interface pointers.  This will force the caller
        // to properly release the interface before obtaining a new one.
        printf("! A non-NULL IPortableDevice interface pointer was received, please release this interface before obtaining a new one.\n");
        return;
    }

    // Fill out information about your application, so the device knows
    // who they are speaking to.

    GetClientInformation(&pClientInformation);

    // Enumerate and display all devices.
    cPnPDeviceIDs = EnumerateAllDevices();

    if (cPnPDeviceIDs > 0)
    {
        // Prompt user to enter an index for the device they want to choose.
        printf("Enter the index of the device you wish to use.\n>");
        hr = StringCbGetsA(szSelection,sizeof(szSelection));
        if (SUCCEEDED(hr))
        {
            uiCurrentDevice = (UINT) atoi(szSelection);
            if (uiCurrentDevice >= cPnPDeviceIDs)
            {
                printf("An invalid device index was specified, defaulting to the first device in the list.\n");
                uiCurrentDevice = 0;
            }
        }
        else
        {
            printf("An invalid device index was specified, defaulting to the first device in the list.\n");
            uiCurrentDevice = 0;
        }

        // CoCreate the IPortableDeviceManager interface to enumerate
        // portable devices and to get information about them.
        hr = CoCreateInstance(CLSID_PortableDeviceManager,
                              NULL,
                              CLSCTX_INPROC_SERVER,
                              IID_PPV_ARGS(&pPortableDeviceManager));
        if (FAILED(hr))
        {
            printf("! Failed to CoCreateInstance CLSID_PortableDeviceManager, hr = 0x%lx\n",hr);
        }

        // Allocate an array to hold the PnPDeviceID strings returned from
        // the IPortableDeviceManager::GetDevices method
        if (SUCCEEDED(hr) && (cPnPDeviceIDs > 0))
        {
            pPnpDeviceIDs = new (std::nothrow)PWSTR[cPnPDeviceIDs];
            if (pPnpDeviceIDs != NULL)
            {
                DWORD dwIndex = 0;

                hr = pPortableDeviceManager->GetDevices(pPnpDeviceIDs, &cPnPDeviceIDs);
                if (SUCCEEDED(hr))
                {
					//<SnippetDeviceEnum5>
                    // CoCreate the IPortableDevice interface and call Open() with
                    // the chosen PnPDeviceID string.
                    hr = CoCreateInstance(CLSID_PortableDeviceFTM,
                                          NULL,
                                          CLSCTX_INPROC_SERVER,
                                          IID_PPV_ARGS(ppDevice));
                    if (SUCCEEDED(hr))
                    {
                        hr = (*ppDevice)->Open(pPnpDeviceIDs[uiCurrentDevice], pClientInformation);
                        if (FAILED(hr))
                        {
                            if (hr == E_ACCESSDENIED)
                            {
                                printf("Failed to Open the device for Read Write access, will open it for Read-only access instead\n");
                                pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_DESIRED_ACCESS, GENERIC_READ);
                                hr = (*ppDevice)->Open(pPnpDeviceIDs[uiCurrentDevice], pClientInformation);
                                if (FAILED(hr))
                                {
                                    printf("! Failed to Open the device, hr = 0x%lx\n",hr);
                                    // Release the IPortableDevice interface, because we cannot proceed
                                    // with an unopen device.
                                    (*ppDevice)->Release();
                                    *ppDevice = NULL;
                                }
                            }
                            else
                            {
                                printf("! Failed to Open the device, hr = 0x%lx\n",hr);
                                // Release the IPortableDevice interface, because we cannot proceed
                                // with an unopen device.
                                (*ppDevice)->Release();
                                *ppDevice = NULL;
                            }
                        }
                    }
                    else
                    {
                        printf("! Failed to CoCreateInstance CLSID_PortableDeviceFTM, hr = 0x%lx\n",hr);
                    }
					//</SnippetDeviceEnum5>
                }
                else
                {
                    printf("! Failed to get the device list from the system, hr = 0x%lx\n",hr);
                }

                // Free all returned PnPDeviceID strings by using CoTaskMemFree.
                // NOTE: CoTaskMemFree can handle NULL pointers, so no NULL
                //       check is needed.
				//<SnippetDeviceEnum4>
                for (dwIndex = 0; dwIndex < cPnPDeviceIDs; dwIndex++)
                {
                    CoTaskMemFree(pPnpDeviceIDs[dwIndex]);
                    pPnpDeviceIDs[dwIndex] = NULL;
                }

                // Delete the array of PWSTR pointers
                delete [] pPnpDeviceIDs;
                pPnpDeviceIDs = NULL;
				//</SnippetDeviceEnum4>
            }
            else
            {
                printf("! Failed to allocate memory for PWSTR array\n");
            }
        }

    }

    // If no devices were found on the system, just exit this function.
}