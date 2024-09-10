    void OnChooseDevice(HWND hwnd)
    {
        ChooseDeviceParam param;

        IMFAttributes *pAttributes = NULL;

        HRESULT hr = MFCreateAttributes(&pAttributes, 1);
        if (FAILED(hr))
        {
            goto done;
        }

        // Ask for source type = video capture devices
        hr = pAttributes->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
                MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);
        if (FAILED(hr))
        {
            goto done;
        }

        // Enumerate devices.
        hr = MFEnumDeviceSources(pAttributes, &param.ppDevices, &param.count);
        if (FAILED(hr))
        {
            goto done;
        }

        // Ask the user to select one.
        INT_PTR result = DialogBoxParam(GetModuleHandle(NULL),
            MAKEINTRESOURCE(IDD_CHOOSE_DEVICE), hwnd,
            ChooseDeviceDlgProc, (LPARAM)&param);

        if ((result == IDOK) && (param.selection != (UINT32)-1))
        {
            UINT iDevice = param.selection;

            if (iDevice >= param.count)
            {
                hr = E_UNEXPECTED;
                goto done;
            }

            hr = g_pEngine->InitializeCaptureManager(hPreview, param.ppDevices[iDevice]);
            if (FAILED(hr))
            {
                goto done;
            }
            SafeRelease(&pSelectedDevice);
            pSelectedDevice = param.ppDevices[iDevice];
            pSelectedDevice->AddRef();
        }

    done:
        SafeRelease(&pAttributes);
        if (FAILED(hr))
        {
            ShowError(hwnd, IDS_ERR_SET_DEVICE, hr);
        }
        UpdateUI(hwnd);
    }