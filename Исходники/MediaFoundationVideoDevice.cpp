  //----------------------------------------------------------------------------
  long MediaFoundationVideoDevice::InitDevice()
  {
    HRESULT hr = S_OK;
    IMFAttributes *pAttributes = NULL;
    IMFActivate * vd_pActivate = NULL;
    CoInitialize(NULL);

    if (SUCCEEDED(hr))
    {
      hr = MFCreateAttributes(&pAttributes, 1);
    }
    if (SUCCEEDED(hr))
    {
      hr = pAttributes->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);
      if (!SUCCEEDED(hr))
      {
        LOG_ERROR("MediaFoundationVideoDevice::InitDevice failed: device  " << this->DeviceIndex << ": The attribute of the capture device cannot be retrieved");
      }
    }
    if (SUCCEEDED(hr))
    {
      hr = CheckDevice(pAttributes, &vd_pActivate);
      if (SUCCEEDED(hr) && vd_pActivate)
      {
        SafeRelease(&this->Source);
        hr = vd_pActivate->ActivateObject(__uuidof(IMFMediaSource), (void**)&this->Source);
        SafeRelease(&vd_pActivate);
      }
      else
      {
        LOG_ERROR("MediaFoundationVideoDevice::InitDevice failed: device  " << this->DeviceIndex << ": Cannot activate device");
      }
    }
    SafeRelease(&pAttributes);
    return hr;
  }