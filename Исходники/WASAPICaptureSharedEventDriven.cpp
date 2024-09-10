//
//  Based on the input switches, pick the specified device to use.
//
bool PickDevice(IMMDevice **DeviceToUse, bool *IsDefaultDevice, ERole *DefaultDeviceRole)
{
    HRESULT hr;
    bool retValue = true;
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    IMMDeviceCollection *deviceCollection = NULL;

    *IsDefaultDevice = false;   // Assume we're not using the default device.

    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&deviceEnumerator));
    if (FAILED(hr))
    {
        printf("Unable to instantiate device enumerator: %x\n", hr);
        retValue = false;
        goto Exit;
    }

    IMMDevice *device = NULL;

    //
    //  First off, if none of the console switches was specified, use the console device.
    //
    if (!UseConsoleDevice && !UseCommunicationsDevice && !UseMultimediaDevice && OutputEndpoint == NULL)
    {
        //
        //  The user didn't specify an output device, prompt the user for a device and use that.
        //
        hr = deviceEnumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &deviceCollection);
        if (FAILED(hr))
        {
            printf("Unable to retrieve device collection: %x\n", hr);
            retValue = false;
            goto Exit;
        }

        printf("Select an output device:\n");
        printf("    0:  Default Console Device\n");
        printf("    1:  Default Communications Device\n");
        printf("    2:  Default Multimedia Device\n");
        UINT deviceCount;
        hr = deviceCollection->GetCount(&deviceCount);
        if (FAILED(hr))
        {
            printf("Unable to get device collection length: %x\n", hr);
            retValue = false;
            goto Exit;
        }
        for (UINT i = 0 ; i < deviceCount ; i += 1)
        {
            LPWSTR deviceName;

            deviceName = GetDeviceName(deviceCollection, i);
            if (deviceName == NULL)
            {
                retValue = false;
                goto Exit;
            }
            printf("    %d:  %S\n", i + 3, deviceName);
            free(deviceName);
        }
        wchar_t choice[10];
        _getws_s(choice);   // Note: Using the safe CRT version of _getws.

        long deviceIndex;
        wchar_t *endPointer;

        deviceIndex = wcstoul(choice, &endPointer, 0);
        if (deviceIndex == 0 && endPointer == choice)
        {
            printf("unrecognized device index: %S\n", choice);
            retValue = false;
            goto Exit;
        }
        switch (deviceIndex)
        {
        case 0:
            UseConsoleDevice = 1;
            break;
        case 1:
            UseCommunicationsDevice = 1;
            break;
        case 2:
            UseMultimediaDevice = 1;
            break;
        default:
            hr = deviceCollection->Item(deviceIndex - 3, &device);
            if (FAILED(hr))
            {
                printf("Unable to retrieve device %d: %x\n", deviceIndex - 3, hr);
                retValue = false;
                goto Exit;
            }
            break;
        }
    } 
    else if (OutputEndpoint != NULL)
    {
        hr = deviceEnumerator->GetDevice(OutputEndpoint, &device);
        if (FAILED(hr))
        {
            printf("Unable to get endpoint for endpoint %S: %x\n", OutputEndpoint, hr);
            retValue = false;
            goto Exit;
        }
    }

    if (device == NULL)
    {
        ERole deviceRole = eConsole;    // Assume we're using the console role.
        if (UseConsoleDevice)
        {
            deviceRole = eConsole;
        }
        else if (UseCommunicationsDevice)
        {
            deviceRole = eCommunications;
        }
        else if (UseMultimediaDevice)
        {
            deviceRole = eMultimedia;
        }
        hr = deviceEnumerator->GetDefaultAudioEndpoint(eCapture, deviceRole, &device);
        if (FAILED(hr))
        {
            printf("Unable to get default device for role %d: %x\n", deviceRole, hr);
            retValue = false;
            goto Exit;
        }
        *IsDefaultDevice = true;
        *DefaultDeviceRole = deviceRole;
    }

    *DeviceToUse = device;
    retValue = true;
Exit:
    SafeRelease(&deviceCollection);
    SafeRelease(&deviceEnumerator);

    return retValue;
}