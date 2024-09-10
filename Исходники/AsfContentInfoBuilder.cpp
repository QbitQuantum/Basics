AsfContentInfoBuilder::AsfContentInfoBuilder()
{
  IPropertyStore* fileLevelEncodingConfiguration = nullptr;
  HRESULT hr;

  _mfAsfContentInfo = nullptr;
  _mfAsfProfile = nullptr;
  _mfMetadataProvider = nullptr;
  _mfMetadata = nullptr;

  do
  {
    if (!SUCCEEDED(hr = MFCreateASFContentInfo(&_mfAsfContentInfo)))
      break;

    if (!SUCCEEDED(hr = MFCreateASFProfile(&_mfAsfProfile)))
      break;

    if (!SUCCEEDED(hr = _mfAsfContentInfo->QueryInterface(IID_IMFMetadataProvider, (void**)&_mfMetadataProvider)))
      break;

    if (!SUCCEEDED(hr = _mfMetadataProvider->GetMFMetadata(NULL, 0, 0, &_mfMetadata)))
      break;

    // Set MFPKEY_ASFMEDIASINK_AUTOADJUST_BITRATE to true on the file-level encoding configuration
    // property store.  Does this actually do anything?  Is it needed?

    if (!SUCCEEDED(hr = _mfAsfContentInfo->GetEncodingConfigurationPropertyStore(0, &fileLevelEncodingConfiguration)))
      break;

    PROPVARIANT pv;
    InitPropVariantFromBoolean(TRUE, &pv);

    if (!SUCCEEDED(hr = fileLevelEncodingConfiguration->SetValue(MFPKEY_ASFMEDIASINK_AUTOADJUST_BITRATE, pv)))
      break;

    PropVariantClear(&pv);

  } while (0);

  if (fileLevelEncodingConfiguration) fileLevelEncodingConfiguration->Release();

  if (FAILED(hr))
  {
    if (_mfMetadata) _mfMetadata->Release();
    if (_mfMetadataProvider) _mfMetadataProvider->Release();
    if (_mfAsfProfile) _mfAsfProfile->Release();
    if (_mfAsfContentInfo) _mfAsfContentInfo->Release();

    throw std::exception("Unable to create MediaSinkContentInfo object");
  }
}