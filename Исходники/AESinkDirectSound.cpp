std::string CAESinkDirectSound::GetDefaultDevice()
{
  IMMDeviceEnumerator* pEnumerator = NULL;
  IMMDevice*           pDevice = NULL;
  IPropertyStore*      pProperty = NULL;
  HRESULT              hr;
  PROPVARIANT          varName;
  std::string          strDevName = "default";

  hr = CoCreateInstance(CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, IID_IMMDeviceEnumerator, (void**)&pEnumerator);
  if (FAILED(hr))
  {
    CLog::Log(LOGERROR, __FUNCTION__": Could not allocate WASAPI device enumerator. CoCreateInstance error code: %s", WASAPIErrToStr(hr));
    goto failed;
  }

  hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
  if (FAILED(hr))
  {
    CLog::Log(LOGERROR, __FUNCTION__": Retrieval of audio endpoint enumeration failed.");
    goto failed;
  }

  hr = pDevice->OpenPropertyStore(STGM_READ, &pProperty);
  if (FAILED(hr))
  {
    CLog::Log(LOGERROR, __FUNCTION__": Retrieval of DirectSound endpoint properties failed.");
    goto failed;
  }

  PropVariantInit(&varName);
  hr = pProperty->GetValue(PKEY_AudioEndpoint_FormFactor, &varName);
  if (FAILED(hr))
  {
    CLog::Log(LOGERROR, __FUNCTION__": Retrieval of DirectSound endpoint form factor failed.");
    goto failed;
  }
  AEDeviceType aeDeviceType = winEndpoints[(EndpointFormFactor)varName.uiVal].aeDeviceType;
  PropVariantClear(&varName);

  hr = pProperty->GetValue(PKEY_AudioEndpoint_GUID, &varName);
  if (FAILED(hr))
  {
    CLog::Log(LOGERROR, __FUNCTION__": Retrieval of DirectSound endpoint GUID failed.");    
    goto failed;
  }

  strDevName = localWideToUtf(varName.pwszVal);
  PropVariantClear(&varName);

failed:

  SAFE_RELEASE(pProperty);
  SAFE_RELEASE(pDevice);
  SAFE_RELEASE(pEnumerator);

  return strDevName;
}