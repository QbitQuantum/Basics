void CAESinkWASAPI::EnumerateDevicesEx(AEDeviceInfoList &deviceInfoList, bool force)
{
  IMMDeviceEnumerator* pEnumerator = NULL;
  IMMDeviceCollection* pEnumDevices = NULL;
  IMMDevice*           pDefaultDevice = NULL;
  CAEDeviceInfo        deviceInfo;
  CAEChannelInfo       deviceChannels;
  LPWSTR               pwszID = NULL;
  std::wstring         wstrDDID;

  WAVEFORMATEXTENSIBLE wfxex = {0};
  HRESULT              hr;

  hr = CoCreateInstance(CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, IID_IMMDeviceEnumerator, (void**)&pEnumerator);
  EXIT_ON_FAILURE(hr, __FUNCTION__": Could not allocate WASAPI device enumerator. CoCreateInstance error code: %li", hr)

  UINT uiCount = 0;

  // get the default audio endpoint
  if(pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDefaultDevice) == S_OK)
  {
    if(pDefaultDevice->GetId(&pwszID) == S_OK)
    {
      wstrDDID = pwszID;
      CoTaskMemFree(pwszID);
    }
    SAFE_RELEASE(pDefaultDevice);
  }

  // enumerate over all audio endpoints
  hr = pEnumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &pEnumDevices);
  EXIT_ON_FAILURE(hr, __FUNCTION__": Retrieval of audio endpoint enumeration failed.")

  hr = pEnumDevices->GetCount(&uiCount);
  EXIT_ON_FAILURE(hr, __FUNCTION__": Retrieval of audio endpoint count failed.")

  for (UINT i = 0; i < uiCount; i++)
  {
    IMMDevice *pDevice = NULL;
    IPropertyStore *pProperty = NULL;
    PROPVARIANT varName;
    PropVariantInit(&varName);

    deviceInfo.m_channels.Reset();
    deviceInfo.m_dataFormats.clear();
    deviceInfo.m_sampleRates.clear();

    hr = pEnumDevices->Item(i, &pDevice);
    if (FAILED(hr))
    {
      CLog::Log(LOGERROR, __FUNCTION__": Retrieval of WASAPI endpoint failed.");
      goto failed;
    }

    hr = pDevice->OpenPropertyStore(STGM_READ, &pProperty);
    if (FAILED(hr))
    {
      CLog::Log(LOGERROR, __FUNCTION__": Retrieval of WASAPI endpoint properties failed.");
      SAFE_RELEASE(pDevice);
      goto failed;
    }

    hr = pProperty->GetValue(PKEY_Device_FriendlyName, &varName);
    if (FAILED(hr))
    {
      CLog::Log(LOGERROR, __FUNCTION__": Retrieval of WASAPI endpoint device name failed.");
      SAFE_RELEASE(pDevice);
      SAFE_RELEASE(pProperty);
      goto failed;
    }

    std::string strFriendlyName = localWideToUtf(varName.pwszVal);
    PropVariantClear(&varName);

    hr = pProperty->GetValue(PKEY_AudioEndpoint_GUID, &varName);
    if(FAILED(hr))
    {
      CLog::Log(LOGERROR, __FUNCTION__": Retrieval of WASAPI endpoint GUID failed.");
      SAFE_RELEASE(pDevice);
      SAFE_RELEASE(pProperty);
      goto failed;
    }

    std::string strDevName = localWideToUtf(varName.pwszVal);
    PropVariantClear(&varName);

    hr = pProperty->GetValue(PKEY_AudioEndpoint_FormFactor, &varName);
    if (FAILED(hr))
    {
      CLog::Log(LOGERROR, __FUNCTION__": Retrieval of WASAPI endpoint form factor failed.");
      SAFE_RELEASE(pDevice);
      SAFE_RELEASE(pProperty);
      goto failed;
    }
    std::string strWinDevType = winEndpoints[(EndpointFormFactor)varName.uiVal].winEndpointType;
    AEDeviceType aeDeviceType = winEndpoints[(EndpointFormFactor)varName.uiVal].aeDeviceType;

    PropVariantClear(&varName);

    hr = pProperty->GetValue(PKEY_AudioEndpoint_PhysicalSpeakers, &varName);
    if (FAILED(hr))
    {
      CLog::Log(LOGERROR, __FUNCTION__": Retrieval of WASAPI endpoint speaker layout failed.");
      SAFE_RELEASE(pDevice);
      SAFE_RELEASE(pProperty);
      goto failed;
    }
    unsigned int uiChannelMask = std::max(varName.uintVal, (unsigned int) KSAUDIO_SPEAKER_STEREO);

    deviceChannels.Reset();

    for (unsigned int c = 0; c < WASAPI_SPEAKER_COUNT; c++)
    {
      if (uiChannelMask & WASAPIChannelOrder[c])
        deviceChannels += AEChannelNames[c];
    }

    PropVariantClear(&varName);

    IAudioClient *pClient;
    hr = pDevice->Activate(IID_IAudioClient, CLSCTX_ALL, NULL, (void**)&pClient);
    if (SUCCEEDED(hr))
    {
      /* Test format DTS-HD */
      wfxex.Format.cbSize               = sizeof(WAVEFORMATEXTENSIBLE)-sizeof(WAVEFORMATEX);
      wfxex.Format.nSamplesPerSec       = 192000;
      wfxex.dwChannelMask               = KSAUDIO_SPEAKER_7POINT1_SURROUND;
      wfxex.Format.wFormatTag           = WAVE_FORMAT_EXTENSIBLE;
      wfxex.SubFormat                   = KSDATAFORMAT_SUBTYPE_IEC61937_DTS_HD;
      wfxex.Format.wBitsPerSample       = 16;
      wfxex.Samples.wValidBitsPerSample = 16;
      wfxex.Format.nChannels            = 8;
      wfxex.Format.nBlockAlign          = wfxex.Format.nChannels * (wfxex.Format.wBitsPerSample >> 3);
      wfxex.Format.nAvgBytesPerSec      = wfxex.Format.nSamplesPerSec * wfxex.Format.nBlockAlign;
      hr = pClient->IsFormatSupported(AUDCLNT_SHAREMODE_EXCLUSIVE, &wfxex.Format, NULL);
      if (SUCCEEDED(hr))
        deviceInfo.m_dataFormats.push_back(AEDataFormat(AE_FMT_DTSHD));

      /* Test format Dolby TrueHD */
      wfxex.SubFormat                   = KSDATAFORMAT_SUBTYPE_IEC61937_DOLBY_MLP;
      hr = pClient->IsFormatSupported(AUDCLNT_SHAREMODE_EXCLUSIVE, &wfxex.Format, NULL);
      if (SUCCEEDED(hr))
        deviceInfo.m_dataFormats.push_back(AEDataFormat(AE_FMT_TRUEHD));

      /* Test format Dolby EAC3 */
      wfxex.SubFormat                   = KSDATAFORMAT_SUBTYPE_IEC61937_DOLBY_DIGITAL_PLUS;
      wfxex.Format.nChannels            = 2;
      wfxex.Format.nBlockAlign          = wfxex.Format.nChannels * (wfxex.Format.wBitsPerSample >> 3);
      wfxex.Format.nAvgBytesPerSec      = wfxex.Format.nSamplesPerSec * wfxex.Format.nBlockAlign;
      hr = pClient->IsFormatSupported(AUDCLNT_SHAREMODE_EXCLUSIVE, &wfxex.Format, NULL);
      if (SUCCEEDED(hr))
        deviceInfo.m_dataFormats.push_back(AEDataFormat(AE_FMT_EAC3));

      /* Test format DTS */
      wfxex.Format.nSamplesPerSec       = 48000;
      wfxex.dwChannelMask               = KSAUDIO_SPEAKER_5POINT1;
      wfxex.SubFormat                   = KSDATAFORMAT_SUBTYPE_IEC61937_DTS;
      wfxex.Format.nBlockAlign          = wfxex.Format.nChannels * (wfxex.Format.wBitsPerSample >> 3);
      wfxex.Format.nAvgBytesPerSec      = wfxex.Format.nSamplesPerSec * wfxex.Format.nBlockAlign;
      hr = pClient->IsFormatSupported(AUDCLNT_SHAREMODE_EXCLUSIVE, &wfxex.Format, NULL);
      if (SUCCEEDED(hr))
        deviceInfo.m_dataFormats.push_back(AEDataFormat(AE_FMT_DTS));

      /* Test format Dolby AC3 */
      wfxex.SubFormat                   = KSDATAFORMAT_SUBTYPE_IEC61937_DOLBY_DIGITAL;
      hr = pClient->IsFormatSupported(AUDCLNT_SHAREMODE_EXCLUSIVE, &wfxex.Format, NULL);
      if (SUCCEEDED(hr))
        deviceInfo.m_dataFormats.push_back(AEDataFormat(AE_FMT_AC3));

      /* Test format AAC */
      wfxex.SubFormat                   = KSDATAFORMAT_SUBTYPE_IEC61937_AAC;
      hr = pClient->IsFormatSupported(AUDCLNT_SHAREMODE_EXCLUSIVE, &wfxex.Format, NULL);
      if (SUCCEEDED(hr))
        deviceInfo.m_dataFormats.push_back(AEDataFormat(AE_FMT_AAC));

      /* Test format for PCM format iteration */
      wfxex.Format.cbSize               = sizeof(WAVEFORMATEXTENSIBLE)-sizeof(WAVEFORMATEX);
      wfxex.dwChannelMask               = KSAUDIO_SPEAKER_STEREO;
      wfxex.Format.wFormatTag           = WAVE_FORMAT_EXTENSIBLE;
      wfxex.SubFormat                   = KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;

      for (int p = AE_FMT_FLOAT; p > AE_FMT_INVALID; p--)
      {
        if (p < AE_FMT_FLOAT)
          wfxex.SubFormat               = KSDATAFORMAT_SUBTYPE_PCM;
        wfxex.Format.wBitsPerSample     = CAEUtil::DataFormatToBits((AEDataFormat) p);
        wfxex.Format.nBlockAlign        = wfxex.Format.nChannels * (wfxex.Format.wBitsPerSample >> 3);
        wfxex.Format.nAvgBytesPerSec    = wfxex.Format.nSamplesPerSec * wfxex.Format.nBlockAlign;
        if (p <= AE_FMT_S24NE4 && p >= AE_FMT_S24BE4)
        {
          wfxex.Samples.wValidBitsPerSample = 24;
        }
        else
        {
          wfxex.Samples.wValidBitsPerSample = wfxex.Format.wBitsPerSample;
        }

        hr = pClient->IsFormatSupported(AUDCLNT_SHAREMODE_EXCLUSIVE, &wfxex.Format, NULL);
        if (SUCCEEDED(hr))
          deviceInfo.m_dataFormats.push_back((AEDataFormat) p);
      }

      /* Test format for sample rate iteration */
      wfxex.Format.cbSize               = sizeof(WAVEFORMATEXTENSIBLE)-sizeof(WAVEFORMATEX);
      wfxex.dwChannelMask               = KSAUDIO_SPEAKER_STEREO;
      wfxex.Format.wFormatTag           = WAVE_FORMAT_EXTENSIBLE;
      wfxex.SubFormat                   = KSDATAFORMAT_SUBTYPE_PCM;
      wfxex.Format.wBitsPerSample       = 16;
      wfxex.Samples.wValidBitsPerSample = 16;
      wfxex.Format.nChannels            = 2;
      wfxex.Format.nBlockAlign          = wfxex.Format.nChannels * (wfxex.Format.wBitsPerSample >> 3);
      wfxex.Format.nAvgBytesPerSec      = wfxex.Format.nSamplesPerSec * wfxex.Format.nBlockAlign;

      for (int j = 0; j < WASAPISampleRateCount; j++)
      {
        wfxex.Format.nSamplesPerSec     = WASAPISampleRates[j];
        wfxex.Format.nAvgBytesPerSec    = wfxex.Format.nSamplesPerSec * wfxex.Format.nBlockAlign;
        hr = pClient->IsFormatSupported(AUDCLNT_SHAREMODE_EXCLUSIVE, &wfxex.Format, NULL);
        if (SUCCEEDED(hr))
          deviceInfo.m_sampleRates.push_back(WASAPISampleRates[j]);
      }

      /* Test format for channels iteration */
      wfxex.Format.cbSize               = sizeof(WAVEFORMATEXTENSIBLE)-sizeof(WAVEFORMATEX);
      wfxex.dwChannelMask               = KSAUDIO_SPEAKER_STEREO;
      wfxex.Format.wFormatTag           = WAVE_FORMAT_EXTENSIBLE;
      wfxex.SubFormat                   = KSDATAFORMAT_SUBTYPE_PCM;
      wfxex.Format.nSamplesPerSec       = 48000;
      wfxex.Format.wBitsPerSample       = 16;
      wfxex.Samples.wValidBitsPerSample = 16;
      wfxex.Format.nChannels            = 2;
      wfxex.Format.nBlockAlign          = wfxex.Format.nChannels * (wfxex.Format.wBitsPerSample >> 3);
      wfxex.Format.nAvgBytesPerSec      = wfxex.Format.nSamplesPerSec * wfxex.Format.nBlockAlign;

      bool hasLpcm = false;

      // Try with KSAUDIO_SPEAKER_DIRECTOUT
      for (unsigned int k = WASAPI_SPEAKER_COUNT; k > 0; k--)
      {
        wfxex.dwChannelMask             = KSAUDIO_SPEAKER_DIRECTOUT;
        wfxex.Format.nChannels          = k;
        wfxex.Format.nBlockAlign        = wfxex.Format.nChannels * (wfxex.Format.wBitsPerSample >> 3);
        wfxex.Format.nAvgBytesPerSec    = wfxex.Format.nSamplesPerSec * wfxex.Format.nBlockAlign;
        hr = pClient->IsFormatSupported(AUDCLNT_SHAREMODE_EXCLUSIVE, &wfxex.Format, NULL);
        if (SUCCEEDED(hr))
        {
          if (k > 3) // Add only multichannel LPCM
          {
            deviceInfo.m_dataFormats.push_back(AE_FMT_LPCM);
            hasLpcm = true;
          }
          break;
        }
      }

      /* Try with reported channel mask */
      for (unsigned int k = WASAPI_SPEAKER_COUNT; k > 0; k--)
      {
        wfxex.dwChannelMask             = uiChannelMask;
        wfxex.Format.nChannels          = k;
        wfxex.Format.nBlockAlign        = wfxex.Format.nChannels * (wfxex.Format.wBitsPerSample >> 3);
        wfxex.Format.nAvgBytesPerSec    = wfxex.Format.nSamplesPerSec * wfxex.Format.nBlockAlign;
        hr = pClient->IsFormatSupported(AUDCLNT_SHAREMODE_EXCLUSIVE, &wfxex.Format, NULL);
        if (SUCCEEDED(hr))
        {
          if ( !hasLpcm && k > 3) // Add only multichannel LPCM
          {
            deviceInfo.m_dataFormats.push_back(AE_FMT_LPCM);
            hasLpcm = true;
          }
          break;
        }
      }

      /* Try with specific speakers configurations */
      for (unsigned int i = 0; i < ARRAYSIZE(layoutsList); i++)
      {
        unsigned int nmbOfCh;
        wfxex.dwChannelMask             = ChLayoutToChMask(layoutsList[i], &nmbOfCh);
        wfxex.Format.nChannels          = nmbOfCh;
        wfxex.Format.nBlockAlign        = wfxex.Format.nChannels * (wfxex.Format.wBitsPerSample >> 3);
        wfxex.Format.nAvgBytesPerSec    = wfxex.Format.nSamplesPerSec * wfxex.Format.nBlockAlign;
        hr = pClient->IsFormatSupported(AUDCLNT_SHAREMODE_EXCLUSIVE, &wfxex.Format, NULL);
        if (SUCCEEDED(hr))
        {
          if ( deviceChannels.Count() < nmbOfCh)
            deviceChannels = layoutsList[i];
          if ( !hasLpcm && nmbOfCh > 3) // Add only multichannel LPCM
          {
            deviceInfo.m_dataFormats.push_back(AE_FMT_LPCM);
            hasLpcm = true;
          }
        }
      }
      pClient->Release();
    }
    else
    {
      CLog::Log(LOGDEBUG, __FUNCTION__": Failed to activate device for passthrough capability testing.");
    }

    deviceInfo.m_deviceName       = strDevName;
    deviceInfo.m_displayName      = strWinDevType.append(strFriendlyName);
    deviceInfo.m_displayNameExtra = std::string("WASAPI: ").append(strFriendlyName);
    deviceInfo.m_deviceType       = aeDeviceType;
    deviceInfo.m_channels         = deviceChannels;

    /* Store the device info */
    deviceInfoList.push_back(deviceInfo);

    if(pDevice->GetId(&pwszID) == S_OK)
    {
      if(wstrDDID.compare(pwszID) == 0)
      {
        deviceInfo.m_deviceName = std::string("default");
        deviceInfo.m_displayName = std::string("default");
        deviceInfo.m_displayNameExtra = std::string("");
        deviceInfoList.push_back(deviceInfo);
      }
      CoTaskMemFree(pwszID);
    }

    SAFE_RELEASE(pDevice);
    SAFE_RELEASE(pProperty);
  }