static ALCenum DSoundOpenCapture(ALCdevice *device, const ALCchar *deviceName)
{
    DSoundCaptureData *data = NULL;
    WAVEFORMATEXTENSIBLE InputType;
    DSCBUFFERDESC DSCBDescription;
    LPGUID guid = NULL;
    HRESULT hr, hrcom;
    ALuint samples;

    if(!CaptureDeviceList)
    {
        /* Initialize COM to prevent name truncation */
        hrcom = CoInitialize(NULL);
        hr = DirectSoundCaptureEnumerateA(DSoundEnumCaptureDevices, NULL);
        if(FAILED(hr))
            ERR("Error enumerating DirectSound devices (%#x)!\n", (unsigned int)hr);
        if(SUCCEEDED(hrcom))
            CoUninitialize();
    }

    if(!deviceName && NumCaptureDevices > 0)
    {
        deviceName = CaptureDeviceList[0].name;
        guid = &CaptureDeviceList[0].guid;
    }
    else
    {
        ALuint i;

        for(i = 0;i < NumCaptureDevices;i++)
        {
            if(strcmp(deviceName, CaptureDeviceList[i].name) == 0)
            {
                guid = &CaptureDeviceList[i].guid;
                break;
            }
        }
        if(i == NumCaptureDevices)
            return ALC_INVALID_VALUE;
    }

    switch(device->FmtType)
    {
        case DevFmtByte:
        case DevFmtUShort:
        case DevFmtUInt:
            WARN("%s capture samples not supported\n", DevFmtTypeString(device->FmtType));
            return ALC_INVALID_ENUM;

        case DevFmtUByte:
        case DevFmtShort:
        case DevFmtInt:
        case DevFmtFloat:
            break;
    }

    //Initialise requested device
    data = calloc(1, sizeof(DSoundCaptureData));
    if(!data)
        return ALC_OUT_OF_MEMORY;

    hr = DS_OK;

    //DirectSoundCapture Init code
    if(SUCCEEDED(hr))
        hr = DirectSoundCaptureCreate(guid, &data->DSC, NULL);
    if(SUCCEEDED(hr))
    {
        memset(&InputType, 0, sizeof(InputType));

        switch(device->FmtChans)
        {
            case DevFmtMono:
                InputType.dwChannelMask = SPEAKER_FRONT_CENTER;
                break;
            case DevFmtStereo:
                InputType.dwChannelMask = SPEAKER_FRONT_LEFT |
                                          SPEAKER_FRONT_RIGHT;
                break;
            case DevFmtQuad:
                InputType.dwChannelMask = SPEAKER_FRONT_LEFT |
                                          SPEAKER_FRONT_RIGHT |
                                          SPEAKER_BACK_LEFT |
                                          SPEAKER_BACK_RIGHT;
                break;
            case DevFmtX51:
                InputType.dwChannelMask = SPEAKER_FRONT_LEFT |
                                          SPEAKER_FRONT_RIGHT |
                                          SPEAKER_FRONT_CENTER |
                                          SPEAKER_LOW_FREQUENCY |
                                          SPEAKER_BACK_LEFT |
                                          SPEAKER_BACK_RIGHT;
                break;
            case DevFmtX51Side:
                InputType.dwChannelMask = SPEAKER_FRONT_LEFT |
                                          SPEAKER_FRONT_RIGHT |
                                          SPEAKER_FRONT_CENTER |
                                          SPEAKER_LOW_FREQUENCY |
                                          SPEAKER_SIDE_LEFT |
                                          SPEAKER_SIDE_RIGHT;
                break;
            case DevFmtX61:
                InputType.dwChannelMask = SPEAKER_FRONT_LEFT |
                                          SPEAKER_FRONT_RIGHT |
                                          SPEAKER_FRONT_CENTER |
                                          SPEAKER_LOW_FREQUENCY |
                                          SPEAKER_BACK_CENTER |
                                          SPEAKER_SIDE_LEFT |
                                          SPEAKER_SIDE_RIGHT;
                break;
            case DevFmtX71:
                InputType.dwChannelMask = SPEAKER_FRONT_LEFT |
                                          SPEAKER_FRONT_RIGHT |
                                          SPEAKER_FRONT_CENTER |
                                          SPEAKER_LOW_FREQUENCY |
                                          SPEAKER_BACK_LEFT |
                                          SPEAKER_BACK_RIGHT |
                                          SPEAKER_SIDE_LEFT |
                                          SPEAKER_SIDE_RIGHT;
                break;
        }

        InputType.Format.wFormatTag = WAVE_FORMAT_PCM;
        InputType.Format.nChannels = ChannelsFromDevFmt(device->FmtChans);
        InputType.Format.wBitsPerSample = BytesFromDevFmt(device->FmtType) * 8;
        InputType.Format.nBlockAlign = InputType.Format.nChannels*InputType.Format.wBitsPerSample/8;
        InputType.Format.nSamplesPerSec = device->Frequency;
        InputType.Format.nAvgBytesPerSec = InputType.Format.nSamplesPerSec*InputType.Format.nBlockAlign;
        InputType.Format.cbSize = 0;

        if(InputType.Format.nChannels > 2 || device->FmtType == DevFmtFloat)
        {
            InputType.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
            InputType.Format.cbSize = sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX);
            InputType.Samples.wValidBitsPerSample = InputType.Format.wBitsPerSample;
            if(device->FmtType == DevFmtFloat)
                InputType.SubFormat = KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;
            else
                InputType.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
        }

        samples = device->UpdateSize * device->NumUpdates;
        samples = maxu(samples, 100 * device->Frequency / 1000);

        memset(&DSCBDescription, 0, sizeof(DSCBUFFERDESC));
        DSCBDescription.dwSize = sizeof(DSCBUFFERDESC);
        DSCBDescription.dwFlags = 0;
        DSCBDescription.dwBufferBytes = samples * InputType.Format.nBlockAlign;
        DSCBDescription.lpwfxFormat = &InputType.Format;

        hr = IDirectSoundCapture_CreateCaptureBuffer(data->DSC, &DSCBDescription, &data->DSCbuffer, NULL);
    }
    if(SUCCEEDED(hr))
    {
         data->Ring = CreateRingBuffer(InputType.Format.nBlockAlign, device->UpdateSize * device->NumUpdates);
         if(data->Ring == NULL)
             hr = DSERR_OUTOFMEMORY;
    }

    if(FAILED(hr))
    {
        ERR("Device init failed: 0x%08lx\n", hr);

        DestroyRingBuffer(data->Ring);
        data->Ring = NULL;
        if(data->DSCbuffer != NULL)
            IDirectSoundCaptureBuffer_Release(data->DSCbuffer);
        data->DSCbuffer = NULL;
        if(data->DSC)
            IDirectSoundCapture_Release(data->DSC);
        data->DSC = NULL;

        free(data);
        return ALC_INVALID_VALUE;
    }

    data->BufferBytes = DSCBDescription.dwBufferBytes;
    SetDefaultWFXChannelOrder(device);

    device->DeviceName = strdup(deviceName);
    device->ExtraData = data;

    return ALC_NO_ERROR;
}